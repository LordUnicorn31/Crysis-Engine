#include "Application.h"
#include "ModuleMesh.h"
#include "ModuleImporter.h"


ModuleMesh::ModuleMesh(Application* app, bool start) : Module(app, start){}

ModuleMesh::~ModuleMesh(){}

bool ModuleMesh::Init()
{

	return true;
}

bool ModuleMesh::Start()
{
	mesh = importer->LoadFile("Assets/BakerHouse.fbx");
	return true;
}

update_status ModuleMesh::Update(float dt)
{
	App->renderer3D->Draw(&mesh);
	App->renderer3D->Draw(&App->input->mesh);
	return UPDATE_CONTINUE;
}

bool ModuleMesh::CleanUp()
{
	importer->CleanUp();
	return true;
}