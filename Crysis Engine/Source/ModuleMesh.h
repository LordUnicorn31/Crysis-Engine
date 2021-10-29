#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleImporter.h"

class ModuleMesh : public Module
{
public:
	
	ModuleMesh(Application* app, bool start = true);
	~ModuleMesh();
	
	bool Init();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();

private:

	ModuleImporter* importer;
	VertexData mesh;
};