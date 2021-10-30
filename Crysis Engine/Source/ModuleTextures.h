#include "Globals.h"
#include "GL/glew.h"

#define CHECKERS_HEIGHT 128
#define CHECKERS_WIDTH 128

class ModuleTextures
{
public:

	ModuleTextures();
	~ModuleTextures();

	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	
	void LoadTexture();

private:

	GLuint textureId;
};
