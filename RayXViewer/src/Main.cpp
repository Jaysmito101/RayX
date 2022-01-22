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

#include "RayX.hpp"

#define DEFAULT_HEIGHT 200

static Application* sRayXViewerApplication;

namespace RayX
{

void LoadDefaultStyle() {
    ImGuiStyle* style = &ImGui::GetStyle();

    style->WindowPadding = ImVec2(15, 15);
    style->WindowRounding = 5.0f;
    style->FramePadding = ImVec2(5, 5);
    style->FrameRounding = 4.0f;
    style->ItemSpacing = ImVec2(12, 8);
    style->ItemInnerSpacing = ImVec2(8, 6);
    style->IndentSpacing = 25.0f;
    style->ScrollbarSize = 15.0f;
    style->ScrollbarRounding = 9.0f;
    style->GrabMinSize = 5.0f;
    style->GrabRounding = 3.0f;
    style->WindowBorderSize = 0;
    style->ChildBorderSize = 0;
    style->PopupBorderSize = 0;
    style->FrameBorderSize = 0;
    style->TabBorderSize = 0;

    style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);

    ImVec4* colors = ImGui::GetStyle().Colors;

    colors[ImGuiCol_Tab] = ImVec4(0.146f, 0.113f, 0.146f, 0.86f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.364f, 0.205f, 0.366f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(51.0f / 255, 31.0f / 255, 49.0f / 255, 0.97f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(51.0f / 255, 31.0f / 255, 49.0f / 255, 0.57f);
    colors[ImGuiCol_Header] = ImVec4(0.61f, 0.61f, 0.62f, 0.22f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.61f, 0.62f, 0.62f, 0.51f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.61f, 0.62f, 0.62f, 0.83f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(43.0f/255, 17.0f/255, 43.0f/255, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.202f, 0.116f, 0.196f, 0.57f);
}

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

static void RenderAddHitableItemControl(RayX::World& world)
{
	std::shared_ptr<RayX::Hitable> item;
	ImGui::Separator();
	if(ImGui::Button("Add Sphere"))
		item = std::make_shared<Sphere>(Point3(0), 1, std::make_shared<Lambertian>(Color(0.9)));
	ImGui::SameLine();
	if(ImGui::Button("Add Plane"))
		item = std::make_shared<Plane>(Point3(1, 0, 0), 0, std::make_shared<Lambertian>(Color(0.9)));
	if(item)
		world.Add(item);
	ImGui::Separator();
}

static void RenderHitableItemControl(std::shared_ptr<RayX::Hitable> item, int id)
{
	bool tmp = false;
	std::shared_ptr<Material> mat;
	if(RayX::InstanceOf<RayX::Sphere>(item.get()))	
	{
		std::shared_ptr<RayX::Sphere> itemS = std::dynamic_pointer_cast<RayX::Sphere>(item);
		mat = itemS->mMaterial;
		ImGui::Text("Sphere");
		ImGui::DragScalarN(("Position##Sphere Item : " + std::to_string(id)).c_str(), ImGuiDataType_Double, &itemS->mCenter, 3, 0.01f);
		ImGui::DragScalar(("Radius##Sphere Item : " + std::to_string(id)).c_str(), ImGuiDataType_Double, &itemS->mRadius, 0.01f);
	}
	else if(RayX::InstanceOf<RayX::Plane>(item.get()))	
	{
		std::shared_ptr<RayX::Plane> itemS = std::dynamic_pointer_cast<RayX::Plane>(item);
		mat = itemS->mMaterial;
		ImGui::Text("Plane");
		ImGui::DragScalarN(("Normal##Plane Item : " + std::to_string(id)).c_str(), ImGuiDataType_Double, &itemS->mNormal, 3, 0.01f);
		ImGui::DragScalarN(("Point On Plane##Plane Item : " + std::to_string(id)).c_str(), ImGuiDataType_Double, &itemS->mPoint, 3, 0.01f);
		if(ImGui::Button(("Normalalize Normal##Plane Item : " + std::to_string(id)).c_str()))
		{
			RayX::Normalize(itemS->mNormal);
		}
	}

	if(mat)
	{
		ImGui::NewLine();
		if(ImGui::CollapsingHeader(("Material##Item : " + std::to_string(id)).c_str()))
		{

		if(RayX::InstanceOf<RayX::Lambertian>(mat))
		{
			std::shared_ptr<RayX::Lambertian> matS = std::dynamic_pointer_cast<RayX::Lambertian>(mat);
			ImGui::Text("Lambertian");
			ImGui::DragScalarN(("Color##Material of Item  : " + std::to_string(id)).c_str(), ImGuiDataType_Double, &matS->albedo, 3, 0.01f);
		}
		else if(RayX::InstanceOf<RayX::Metal>(mat))
		{
			std::shared_ptr<RayX::Metal> matS = std::dynamic_pointer_cast<RayX::Metal>(mat);
			ImGui::Text("Metal");
			ImGui::DragScalarN(("Color##Material of Item  : " + std::to_string(id)).c_str(), ImGuiDataType_Double, &matS->albedo, 3, 0.01f);
			ImGui::DragScalarN(("Fuzz##Material of Item  : " + std::to_string(id)).c_str(), ImGuiDataType_Double, &matS->mFuzz, 1, 0.01f);
		}
		else if(RayX::InstanceOf<RayX::Dielectric>(mat))
		{
			std::shared_ptr<RayX::Dielectric> matS = std::dynamic_pointer_cast<RayX::Dielectric>(mat);
			ImGui::Text("Dielectric");
			ImGui::DragScalarN(("Refractive Index##Material of Item  : " + std::to_string(id)).c_str(), ImGuiDataType_Double, &matS->mIr, 1, 0.01f);
		}

		if(ImGui::Button(("To Lambertian##" + std::to_string(id)).c_str()))
			item->mMaterial = std::make_shared<Lambertian>(Color(1));
		if(ImGui::Button(("To Dielectric##" + std::to_string(id)).c_str()))
			item->mMaterial = std::make_shared<Dielectric>(1.5);
		if(ImGui::Button(("To Metal##" + std::to_string(id)).c_str()))
			item->mMaterial = std::make_shared<Metal>(Color(1), 0.1);
		}
	}

}

static void RenderWorldControls(RayX::World& world)
{
	for(int i = 0 ; i < world.mHitables.size() ; i++)
	{
		if(ImGui::CollapsingHeader(("Item : " + std::to_string(i)).c_str()))
		{
			RenderHitableItemControl(world.mHitables[i], i);
			ImGui::NewLine();
			if(ImGui::Button(("Delete Item##WORLD" + std::to_string(i)).c_str()))
			{
				world.mHitables.erase(world.mHitables.begin() + i);
				break;
			}
		}
		ImGui::Separator();
	}
	RenderAddHitableItemControl(world);
}

static void SetupWorld(RayX::World& world)
{
    auto mat1 = std::make_shared<Lambertian>(Color(0.8, 0.8, 0));
    auto mat2 = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
    auto mat3 = std::make_shared<Dielectric>(1.5);
    auto mat4 = std::make_shared<Metal>(Color(0.2, 0.8, 0.4), 0.3);
	
    world.Clear();
    world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100, mat1));
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

		SetupWorld(mPathTracer->mWorld);

		LoadDefaultStyle();

		height = DEFAULT_HEIGHT;
		width = DEFAULT_HEIGHT * 1.77;
		mZoom = 1.0f;
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
					mPathTracer->mCamera.mAspectRatio = width / height;
				}
				mPathTracer->mCamera.Update();
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
			ImGui::Text("Camera Settings");
			ImGui::DragScalar("VFOV", ImGuiDataType_Double, &mPathTracer->mCamera.mVfov, 0.1f);
			ImGui::DragScalarN("Look From", ImGuiDataType_Double, &mPathTracer->mCamera.mLookFrom, 3, 0.01f);
			ImGui::DragScalarN("Look At", ImGuiDataType_Double, &mPathTracer->mCamera.mLookAt, 3, 0.01f);
			ImGui::DragScalarN("Up", ImGuiDataType_Double, &mPathTracer->mCamera.mVUp, 3, 0.01f);
			ImGui::NewLine();
			ImGui::Text("World Settings");
			RenderWorldControls(mPathTracer->mWorld);
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

		ImGui::NewLine();
		ImGui::NewLine();

                ImGui::Text("Viewer Settings");

		ImGui::DragFloat("Viewer Zoom", &mZoom, 0.01, 0.01);		

		ImGui::End();

		// The Main Rendered Image

		ImGui::Begin("Rendered Image");
			
		ImGui::Image((ImTextureID)mOGLTexture->GetRendererID(), ImVec2(mRenderedImage->mImageWidth*mZoom, mRenderedImage->mImageHeight*mZoom));

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
	float mZoom;
};

} // namespace RayX

Application* CreateApplication()
{
	sRayXViewerApplication = new RayX::RayXViewerApplication();
	return sRayXViewerApplication;
}