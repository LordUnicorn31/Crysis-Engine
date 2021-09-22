#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#define MAX_LIGHTS 8

class ModuleGUI : public Module
{
public:
	
	ModuleGUI(Application* app, bool start = true);
	~ModuleGUI();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

public:


	void ExampleWindow();
	void MenuWindow();

private:

	bool showDemoWindow = true;
	bool anotherWindow = false;
	bool toolActive;

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


};