#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "UserInterface.h"
#include "string"

void UserInterface::init(OGLRenderData& renderData)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(renderData._window, true);
	ImGui_ImplOpenGL3_Init("#version 460 core");
}

void UserInterface::createFrame(OGLRenderData& renderData)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGuiWindowFlags imguiWindowFlags = 0;
	ImGui::SetNextWindowBgAlpha(0.8f);
	ImGui::Begin("Control", nullptr, imguiWindowFlags);

	static float newFps = 0.0f;
	if(renderData._frameTime > 0.0f)
	{
		newFps = 1.0f / renderData._frameTime;
	}
	_framesPerSecond = (averagingAlpha * _framesPerSecond) + (1.0f - averagingAlpha) * newFps;
	ImGui::Text("FPS:");
	ImGui::SameLine();
	ImGui::Text("%s", std::to_string(_framesPerSecond).c_str());

	ImGui::Text("UI Generation Time:");
	ImGui::SameLine();
	ImGui::Text("%s", std::to_string(renderData._uiGenerateTime).c_str());
	ImGui::SameLine();
	ImGui::Text("ms");

	ImGui::Text("Triangles");
	ImGui::SameLine();
	ImGui::Text(std::to_string(renderData._triangleCount).c_str());

	std::string windowDims = std::to_string(renderData._width) + "x" + std::to_string(renderData._height);
	ImGui::Text("Window Dimensions:");
	ImGui::SameLine();
	ImGui::Text(windowDims.c_str());

	std::string imgWindowPos = std::to_string(static_cast<int>(ImGui::GetWindowPos().x)) + "/" + std::to_string(static_cast<int>(ImGui::GetWindowPos().y));

	ImGui::Text("Imgui Window Position:");
	ImGui::SameLine();
	ImGui::Text(imgWindowPos.c_str());

	ImGui::End();
}

void UserInterface::render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UserInterface::cleanup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
