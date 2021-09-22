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
	toolActive = true;
	docking = true;
	hierarchy = true;
	inspector = true;

	return true;
}

update_status ModuleGUI::Update(float dt)
{
	// Initialize the new frame for both opengl and SDL
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	// Core of ImGui
	Docking();
	ExampleWindow();
	HierarchyTab();
	AssetsTab();
	InspectorTab();

	// End of frame
	

	
	ImGui::Render();
	ImGuiIO& io = ImGui::GetIO();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}

	return UPDATE_CONTINUE;
}

void ModuleGUI::ExampleWindow()
{
	static float f = 0.0f;
	static int counter = 0;

	                        // Create a window called "Hello, world!" and append into it.

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

void ModuleGUI::Docking()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoBackground;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	if (ImGui::Begin("DockSpace", &docking, window_flags)) {
		// DockSpace
		ImGui::PopStyleVar(3);
		if (docking)
		{
			ImGuiID dockspace_id = ImGui::GetID("DockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
			MenuWindow();
		}
		ImGui::End();
	}
}

void ModuleGUI::MenuWindow()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Scene", "Ctrl+N")) {};
			if (ImGui::MenuItem("Open Scene", "Ctrl+O")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save As", "Ctrl+Shift+S")) {};
			if (ImGui::MenuItem("Close", "Ctrl+W")) { toolActive = false; }
			if (ImGui::MenuItem("Exit")) { state == UPDATE_STOP; }
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Assets"))
		{
			if (ImGui::BeginMenu("Create"))
			{
				if (ImGui::MenuItem("Sphere")) {};
				if (ImGui::MenuItem("Square")) {};
				if (ImGui::MenuItem("Cone")) {};
				if (ImGui::MenuItem("Empty GameObject")) 
				{

				};
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Import New Asset")) {};
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

}

void ModuleGUI::HierarchyTab()
{
	if (hierarchy)
	{
		if (ImGui::Begin("Hierarchy", &hierarchy))
		{
			// Place for gameobjects
		}
		ImGui::End();
	}
}

void ModuleGUI::AssetsTab()
{
	if (assets)
	{
		if (ImGui::Begin("Assets", &assets)) 
		{
			// Place for all the imported assets
		};
		ImGui::End();
	}
}

void ModuleGUI::InspectorTab()
{
	if (inspector)
	{
		if (ImGui::Begin("Inspector", &inspector)) 
		{
			// Place for the game objects characteristics
		};
	}
	ImGui::End();
}

bool ModuleGUI::CleanUp()
{
	return false;
}