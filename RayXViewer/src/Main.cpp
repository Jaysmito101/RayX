#define _CRT_SECURE_NO_WARNINGS
#include <Window.h>
#include <Application.h>
#include <EntryPoint.h>
#include <Texture2D.h>

#include <imgui.h>
#include <glfw/glfw3.h>
#include <stb/stb_image_write.h>

#include <string>
#include <ctime>
#include <cstring>
#include <mutex>
#include <memory>
#include <atomic>
#include <iostream>

#include "PathTracer.hpp"
#include "Vec3.hpp"

#define DEFAULT_HEIGHT 400

static Application* sRayXViewerApplication;

namespace RayX
{


static void OnBeforeImGuiRender() {

	static bool dockspaceOpen = true;
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.1f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
	ImGui::PopStyleVar();
	if (opt_fullscreen) {
		ImGui::PopStyleVar(2);
	}
	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	float minWinSizeX = style.WindowMinSize.x;
	style.WindowMinSize.x = 370.0f;
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	style.WindowMinSize.x = minWinSizeX;

	//ShowMenu();
}

static void OnImGuiRenderEnd() {
	ImGui::End();
}

static void OnWindowClose(int , int) {
    sRayXViewerApplication->Close();
}

class RayXViewerApplication : public Application
{
public:

	virtual void OnPreload() override
    {
		srand((unsigned int)time(NULL));
		SetTitle("RayX Viewer - Jaysmito Mukherjee");
        SetWindowConfigPath("./windows.config");
	}
    
	virtual void OnStart(std::string loadFile) override
	{
        GetWindow()->SetShouldCloseCallback(OnWindowClose);
        mPathTracer = std::make_shared<PathTracer>(DEFAULT_HEIGHT * 1.772f, DEFAULT_HEIGHT);
        mRenderedImage = std::make_shared<Image>();
		mOGLTexture = std::make_shared<Texture2D>(DEFAULT_HEIGHT * 1.772f, DEFAULT_HEIGHT);

		height = DEFAULT_HEIGHT;
		width = DEFAULT_HEIGHT * 1.77;

		mCanOGLTexUpdate = false;
	}

	virtual void OnUpdate(float deltatime) override
	{
		if (mCanOGLTexUpdate)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			mOGLTexture->SetData(mRenderedImage->mImageData, mRenderedImage->mImageWidth * mRenderedImage->mImageHeight * 3);
			std::cout << "Updated OpenGL Image\n";
			mCanOGLTexUpdate = false;
		}
		RenderImGui();
	}

	virtual void OnImGuiRender() override
	{
		OnBeforeImGuiRender();
		
		ImGui::Begin("Settings");

        if(!mPathTracer->mIsRendering)    
        {
            ImGui::Text("Image Settings");
            ImGui::DragInt("Image Width", &width, 1.0f, 1.0f);
			ImGui::DragInt("Image Height", &height, 1.0f, 1.0f);
			ImGui::DragInt("Samples Per Pixel", &mPathTracer->mSamplesPerPixel, 1.0f, 1.0f);
			ImGui::DragInt("Max Light Bounces", &mPathTracer->mMaxBounces, 1.0f, 1.0f);
			ImGui::NewLine();
			if(ImGui::Button("Render"))
			{
			    std::cout << "Started Rendering ..." << std::endl;
				if (mRenderedImage->mImageWidth != width || mRenderedImage->mImageHeight != height)
				{
					mRenderedImage->Resize(width, height);
					mOGLTexture = std::make_shared<Texture2D>(width, height);
					mPathTracer->mImageHeight = height;
					mPathTracer->mImageWidth = width;
				}
				std::thread([&] {
					mPathTracer->Render(mRenderedImage, [&](float progress){
						mCanOGLTexUpdate = true;
						while (!mCanOGLTexUpdate);
					});
				}
				).detach();
			}

			if (mRenderedImage->mImageData)
			{
				if (ImGui::Button("Clear"))
				{
					memset(mRenderedImage->mImageData, 0, mRenderedImage->mImageHeight * mRenderedImage->mImageWidth * 3);
					mOGLTexture->SetData(mRenderedImage->mImageData, mRenderedImage->mImageHeight * mRenderedImage->mImageWidth * 3);
				}
			}

			ImGui::NewLine();
			ImGui::NewLine();
			if (mRenderedImage->mImageData)
			{
				if (ImGui::Button("Export"))
				{
					std::string filename = "rendered_image" + std::to_string(rand() % 99 + 100) + ".png";
					std::cout << "Exported " << filename << std::endl;
					stbi_write_png(filename.data(), mRenderedImage->mImageWidth, mRenderedImage->mImageHeight, 3, mRenderedImage->mImageData, 0);
				}
			}
        }
        else
        {
            ImGui::Text("Rendering");
            ImGui::ProgressBar(mPathTracer->mRenderProgress);

			ImGui::NewLine();

			if (!mPathTracer->mCancelRendering)
			{
				if (ImGui::Button("Cancel"))
					mPathTracer->mCancelRendering = true;
			}
			else
			{
				ImGui::Text("Cancelling Render ...");
			}
        }


		ImGui::End();

		// The Main Rendered Image

		ImGui::Begin("Rendered Image");
			
		ImGui::Image((ImTextureID)mOGLTexture->GetRendererID(), ImVec2(mRenderedImage->mImageWidth, mRenderedImage->mImageHeight));

		ImGui::End();
	
		OnImGuiRenderEnd();
	}


	void OnEnd()
	{
	}

    private:
    std::shared_ptr<RayX::PathTracer> mPathTracer;
    std::shared_ptr<RayX::Image> mRenderedImage;
	std::shared_ptr<Texture2D> mOGLTexture;

	std::atomic<bool> mCanOGLTexUpdate;

	int width, height;
};

} // namespace RayX

Application* CreateApplication()
{
	sRayXViewerApplication = new RayX::RayXViewerApplication();
	return sRayXViewerApplication;
}