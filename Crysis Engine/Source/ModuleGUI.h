#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include <vector>
#include <string>
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

	void Docking();
	void ExampleWindow();
	void MenuWindow();
	void HierarchyTab();
	void AssetsTab();
	void ConsoleTab();
	void InspectorTab();
	void AboutWindow();
	void Log(const char* log);

	bool exit;

private:

	bool showDemoWindow = true;
	bool anotherWindow = false;
	bool toolActive;
	bool docking;
	bool hierarchy;
	bool assets;
	bool inspector;
	bool console;
	bool about;
	bool gameObject;
	std::vector<char*> consoleLog;

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


};