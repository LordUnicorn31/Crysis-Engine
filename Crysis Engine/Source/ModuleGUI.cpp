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
#include "GameObject.h"

ModuleGUI::ModuleGUI(Application* app, bool start) : Module(app, start)
{
	
}

ModuleGUI::~ModuleGUI()
{

}

bool ModuleGUI::Init()
{
	exit = false;
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
	//ImGui::StyleColorsComedia();

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
	console = true;
	assets = true;
	about = false;
	gameObject = false;
	performance = true;

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
	ConsoleTab();
	InspectorTab();
	AboutWindow();

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
	if (ImGui::Begin("Performance", &performance))
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();
	}
	

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
			if (ImGui::MenuItem("Exit")) { exit = true; }
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
					App->scene_intro->CreateObject(new GameObject("Empty"));
					gameObject = !gameObject;
				};
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Import New Asset")) {};
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About"))
			{
				//We turn the "About" bool to true so it can create the AboutWindow. If not the window will just create and instantly get closed after pressing the MenuItem.
				about = !about;
			}
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
			if (gameObject)
			{
				ImGui::Text("Empty");
			}

			ImGui::End();
		}
	}
}

void ModuleGUI::AssetsTab()
{
	if (assets)
	{
		if (ImGui::Begin("Assets", &assets)) 
		{
			// Place for all the imported assets
			if(ImGui::Button("Refresh Directory")) {};
		}
		ImGui::End();
	}
}

void ModuleGUI::ConsoleTab()
{
	if (console && assets)
	{
		if (ImGui::Begin("Console", &assets))
		{
			for (int i = 0; i < consoleLog.size(); ++i)
			{
				ImGui::TextUnformatted(consoleLog[i]);
			}

		}
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
			ImGui::End();
		};
	}
	
}

void ModuleGUI::AboutWindow()
{
	if (about)
	{
		if (ImGui::Begin("About", &about))
		{
			ImGui::Text("Crysis Engine v0.3\n");
			ImGui::Text("Created by Jordi Espriu & Victor Nisa\n");
			ImGui::Separator();
			ImGui::Text("3rd Party Libraries used:\n");
			ImGui::BulletText("SDL 2.06\n");
			ImGui::BulletText("SDL Mixer 2.0.0\n");
			ImGui::BulletText("Glew 2.0.0\n");
			ImGui::BulletText("ImGui\n");
			ImGui::BulletText("MathGeoLib\n");
			ImGui::BulletText("OpenGL 3.1.1\n");
			ImGui::BulletText("Assimp 3.1.1\n");
			ImGui::Separator();
			ImGui::Text("License:\n");
			ImGui::Text("Copyright(c) 2020 Crysis Engine\n"
					"Permission is hereby granted, free of charge, to any person obtaining a copy\n"
					"of this software and associated documentation files(the ""Software""), to deal\n"
					"in the Software without restriction, including without limitation the rights\n"
					"to use, copy, modify, merge, publish, distribute, sublicense, and /or sell\n"
					"copies of the Software, and to permit persons to whom the Software is\n"
					"furnished to do so, subject to the following conditions :\n"
					"The above copyright noticeand this permission notice shall be included in all\n"
					"copies or substantial portions of the Software.\n"
					"THE SOFTWARE IS PROVIDED ""AS IS"", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
					"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
					"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE\n"
					"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
					"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
					"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
				"SOFTWARE.");
		}
		ImGui::End();
	}
	
}



void ModuleGUI::AddLog(const char* log)
{
	char* nString = strdup(log);
	consoleLog.push_back(nString);
}

void ModuleGUI::ClearLog()
{
	for (uint i = 0; i < consoleLog.size(); ++i)
	{
		free(consoleLog[i]);
	}

	consoleLog.clear();
}

bool ModuleGUI::CleanUp()
{
	return false;
}