#include "stdafx.h"
#include "visualitzacio.h"
#include "escena.h"
#include "shader.h"


void flipImageVertically(unsigned char* image, int width, int height, int channels) {
	int rowSize = width * channels;
	unsigned char* tempRow = (unsigned char*)malloc(rowSize);

	for (int y = 0; y < height / 2; ++y) {
		unsigned char* row1 = image + y * rowSize;
		unsigned char* row2 = image + (height - y - 1) * rowSize;
		memcpy(tempRow, row1, rowSize);
		memcpy(row1, row2, rowSize);
		memcpy(row2, tempRow, rowSize);
	}

	free(tempRow);
}


GLuint* loadIMA_SOIL_texture()
{
	FILE* file = NULL;
	int errno;
	GLuint* textureID = new GLuint[10];

	std::vector<std::string> filenames =
	{ 
		".\\textures\\planets\\2k_sun.jpg",
		".\\textures\\planets\\8k_mercury.jpg",
		".\\textures\\planets\\4k_venus_atmosphere.jpg",
		".\\textures\\planets\\8k_earth_daymap.jpg",
		//".\\textures\\planets\\8k_moon.jpg",
		".\\textures\\planets\\8k_mars.jpg",
		".\\textures\\planets\\8k_jupiter.jpg",
		".\\textures\\planets\\8k_saturn.jpg",
		".\\textures\\planets\\2k_uranus.jpg",
		".\\textures\\planets\\2k_neptune.jpg",
		".\\textures\\planets\\8k_moon.jpg",
		".\\textures\\planets\\8k_saturn_ring_alpha.png"
	};

	glGenTextures(11, textureID);


	int i = 0;
	for (std::string filename : filenames) {

		// Open the image file for reading
		//  file=fopen(nomf,"r");					// Funció Visual Studio 6.0
		errno = fopen_s(&file, filename.c_str(), "rb");		// Funció Visual 2010

		// If the file is empty (or non existent) print an error and return false
		// if (file == NULL)
		if (errno != 0)
		{	//	printf("Could not open file '%s'.\n",filename) ;
			return false;
		}

		// Close the image file
		fclose(file);

		/*
		// SOIL_load_OGL_texture: Funció que llegeix la imatge del fitxer filename
		//				si és compatible amb els formats SOIL (BMP,JPG,GIF,TIF,TGA,etc.)
		//				i defineix la imatge com a textura OpenGL retornant l'identificador
		//				de textura OpenGL.
			textureID = SOIL_load_OGL_texture
			(filename,
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_MIPMAPS | SOIL_FLAG_DDS_LOAD_DIRECT | SOIL_FLAG_INVERT_Y
			);
		*/

		//Generate texture ID and load texture data 
		int width, height;
		unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

		//Problema con coord textura de OpenGL, hacemos una inversión de Y 
		// Flip the loaded image
		flipImageVertically(image, width, height, SOIL_LOAD_RGB);


		// Assign texture to ID
		glBindTexture(GL_TEXTURE_2D, textureID[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		SOIL_free_image_data(image);

		i += 1;
	}


	// If execution arrives here it means that all went well. Return true
	return textureID;
}

void load_skybox(GLuint skC_programID, Shader shader_SkyBoxC, CVAO skC_VAOID, GLuint cubemapTexture) {

	// Càrrega Shader Skybox
	if (!skC_programID) skC_programID = shader_SkyBoxC.loadFileShaders(".\\shaders\\skybox.VERT", ".\\shaders\\skybox.FRAG");

	// Càrrega VAO Skybox Cube
	if (skC_VAOID.vaoId == 0) skC_VAOID = loadCubeSkybox_VAO();
	Set_VAOList(CUBE_SKYBOX, skC_VAOID);

	if (!cubemapTexture)
	{	// load Skybox textures
		// -------------
		std::vector<std::string> faces =
		{ ".\\textures\\skybox\\right.jpg",
			".\\textures\\skybox\\left.jpg",
			".\\textures\\skybox\\top.jpg",
			".\\textures\\skybox\\bottom.jpg",
			".\\textures\\skybox\\front.jpg",
			".\\textures\\skybox\\back.jpg"
		};
		cubemapTexture = loadCubemap(faces);
	}
}