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

void ModuleImporter::LoadFile(const char* path)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		//Use scene->numMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; ++i)
		{
		
			//Copy vertices
			
			
		}
	}
}

void ModuleImporter::CleanUp()
{
	aiDetachAllLogStreams();
}