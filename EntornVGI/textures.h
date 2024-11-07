#pragma once

#include "EntornVGI.h"
#include "stdafx.h"
#include "visualitzacio.h"
#include "escena.h"
#include "shader.h"

GLuint* loadIMA_SOIL_texture();
void load_skybox(GLuint skC_programID, Shader shader_SkyBoxC, CVAO skC_VAOID, GLuint cubemapTexture);