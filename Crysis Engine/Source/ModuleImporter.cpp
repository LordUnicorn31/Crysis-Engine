#include "ModuleImporter.h"
#include "Globals.h"
#include "GL/glew.h"


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
			myMesh.numVertex = scene->mMeshes[i]->mNumVertices;
			myMesh.vertex = new float[myMesh.numVertex * 3];
			memcpy(myMesh.vertex, scene->mMeshes[i]->mVertices, sizeof(float) * myMesh.numVertex);
			LOG("New mesh with %d vertices", myMesh.vertex);

			// copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
				myMesh.numIndex = scene->mMeshes[i]->mNumFaces * 3;
				myMesh.index = new uint[myMesh.numIndex];
				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; ++j)
				{
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices");
					}
					else
					{
                        memcpy(&myMesh.index[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, sizeof(uint) * 3);
					}
						
				}
			}

			glGenBuffers(1, &myMesh.numVertex);
			glBindBuffer(GL_ARRAY_BUFFER, myMesh.numVertex);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * myMesh.numVertex, myMesh.index, GL_STATIC_DRAW);
		}
	}
}

void ModuleImporter::CleanUp()
{
	aiDetachAllLogStreams();
}