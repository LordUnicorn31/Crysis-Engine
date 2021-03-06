#include "Globals.h"
#include "GL/glew.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "imgui.h"
#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_sdl.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	
	

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)


	//glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	//glClear(GL_COLOR_BUFFER_BIT);

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)

	if (App->input->GetKey(SDL_SCANCODE_F))
	{
		/*App->camera->CalculateViewMatrix();

		App->camera->X = vec3(1.0f, 0.0f, 0.0f);
		App->camera->Y = vec3(0.0f, 1.0f, 0.0f);
		App->camera->Z = vec3(0.0f, 0.0f, 1.0f);

		App->camera->Position = vec3(0.0f, 0.0f, 5.0f);
		App->camera->Reference = vec3(0.0f, 0.0f, 0.0f);*/
		App->camera->Look({ 1.0, 1.0, 6.0 }, 0, false);
	}
	
	

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

GameObject* ModuleSceneIntro::CreateObject(GameObject* gameObject)
{
	LOG("Empty game object created!");
	return gameObject;
}

