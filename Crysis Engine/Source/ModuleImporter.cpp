#include "ModuleImporter.h"
#include "Globals.h"

ModuleImporter::ModuleImporter() {};

ModuleImporter::~ModuleImporter() {};

void ModuleImporter::Init()
{
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
}

void ModuleImporter::CleanUp()
{
	aiDetachAllLogStreams();
}