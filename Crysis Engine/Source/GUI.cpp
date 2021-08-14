#include "Globals.h"
#include "GL/glew.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "imgui.h"
#include "GUI.h"
#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_sdl.h"

GUI::GUI(Application* app, bool start_enabled) : Module(app, start_enabled){};

void GUI::WindowDock()
{
	winFlags = ImGuiWindowFlags_MenuBar;
	viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
}

