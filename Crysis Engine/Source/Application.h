#pragma once

#include "p2List.h"
#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleGUI.h"
#include "ModuleCamera3D.h"
#include "ModulePlayer.h"
#include "ModuleMesh.h"

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleSceneIntro* scene_intro;
	ModuleRenderer3D* renderer3D;
	ModuleGUI* gui;
	ModuleCamera3D* camera;
	ModulePlayer* player;
	ModuleMesh* mesh;

private:

	Timer	ms_timer;
	float	dt;
	p2List<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	void AddConsoleLog(const char* string);

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

extern Application* app;