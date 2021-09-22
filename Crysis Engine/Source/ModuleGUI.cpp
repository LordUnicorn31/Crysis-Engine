#include "Application.h"
#include "Globals.h"
#include "GL/glew.h"
#include "Application.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleGUI.h"
#include "Primitive.h"
#include "ModuleSceneIntro.h"
#include "imgui.h"
#include "examples\imgui_impl_sdl.h"
#include "examples\imgui_impl_opengl3.h"

ModuleGUI::ModuleGUI(Application* app, bool start) : Module(app, start)
{
	
}

ModuleGUI::~ModuleGUI()
{

}

bool ModuleGUI::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;
	io.ConfigDockingWithShift = false;

	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	//ImGui::StyleColorsLight();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init("#version 460");

	showDemoWindow = true;
	anotherWindow = false;

	return true;
}

update_status ModuleGUI::Update(float dt)
{
	// Initialize the new frame for both opengl and SDL
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	// Core of ImGui
	ExampleWindow();

	// End of frame
	ImGui::End();

	ImGui::EndFrame();
	ImGui::UpdatePlatformWindows();
	ImGui::Render();
	ImGuiIO& io = ImGui::GetIO();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

void ModuleGUI::ExampleWindow()
{
	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	ImGui::Checkbox("Demo Window", &showDemoWindow);      // Edit bools storing our window open/close state
	ImGui::Checkbox("Another Window", &anotherWindow);

	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

}

bool ModuleGUI::CleanUp()
{
	return false;
}