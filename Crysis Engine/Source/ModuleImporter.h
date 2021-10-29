#pragma once
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Globals.h"
#include "GL/glew.h"

struct VertexData
{
	uint idIndex = 0; //Index in VRAM
	uint numIndex = 0;
	uint* index = nullptr;

	uint idVertex = 0; //Unique vertex in VRAM
	uint numVertex = 0;
	float* vertex = nullptr;

	GLuint buffer = 0;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
};

class ModuleImporter
{
public:

	ModuleImporter();
	~ModuleImporter();

	void Init();
	void CleanUp();
	VertexData LoadFile(const char* path);
	void CreateBuffer(VertexData& mesh);

private:


	aiMesh* aMesh;
};