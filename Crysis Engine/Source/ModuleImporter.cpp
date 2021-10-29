#include "ModuleImporter.h"
#include "Globals.h"
#include "GL/glew.h"

GLuint meshBuffer;

ModuleImporter::ModuleImporter() {};

ModuleImporter::~ModuleImporter() {};

void ModuleImporter::Init()
{
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
}

VertexData ModuleImporter::LoadFile(const char* path)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	VertexData mesh;
	if (scene != nullptr && scene->HasMeshes())
	{
		//Use scene->numMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; ++i)
		{
			VertexData myMesh;
		
			//Copy vertices
			myMesh.numVertex = scene->mMeshes[i]->mNumVertices;
			myMesh.vertex = new float[myMesh.numVertex * 3];
			memcpy(myMesh.vertex, scene->mMeshes[i]->mVertices, sizeof(float) * myMesh.numVertex * 3);
			LOG("New mesh with %d vertices", myMesh.numVertex);

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

			CreateBuffer(myMesh);

			mesh = myMesh;
		}
	}

	return mesh;
}

void ModuleImporter::CreateBuffer(VertexData& mesh)
{
	glGenVertexArrays(1, &mesh.VAO);
	glBindVertexArray(mesh.VAO);

	glGenBuffers(1, &mesh.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);

	glBufferData(GL_ARRAY_BUFFER, mesh.numVertex * sizeof(float) * 3, mesh.vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.numIndex * sizeof(unsigned int), mesh.index, GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

	glBindVertexArray(0);
}

void ModuleImporter::CleanUp()
{
	aiDetachAllLogStreams();
}