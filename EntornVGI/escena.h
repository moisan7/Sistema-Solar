//******** PRACTICA VISUALITZACI� GR�FICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn b�sic VS2022 MONO-MULTIFINESTRA amb OpenGL 4.3 i llibreries GLM
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� G�dia (Setembre 2024)
// escena.h : interface de escena.cpp
//

#ifndef GLSOURCE_H
#define GLSOURCE_H

// Entorn VGI: OBJECTE OBJ. Include per la definici� de l'objecte Obj_OBJ
#include "objLoader.h"	

/* ------------------------------------------------------------------------- */
/*                            Funcions de les escenes                        */
/* ------------------------------------------------------------------------- */
void dibuixa_Eixos(GLuint ax_programID, bool eix, GLuint axis_Id, CMask3D reixa, CPunt3D hreixa, glm::mat4 MatriuProjeccio, glm::mat4 MatriuVista);
void dibuixa_Skybox(GLuint sk_programID, GLuint cmTexture, char eix_Polar, glm::mat4 MatriuProjeccio, glm::mat4 MatriuVista);

// Entorn VGI: dibuixa_EscenaGL -> Dibuix de l'escena GL
void dibuixa_EscenaGL(GLuint sh_programID, bool eix, GLuint axis_Id, CMask3D reixa, CPunt3D hreixa, char objecte, CColor col_object,
	bool sw_mat[5],
	bool textur, GLuint texturID[NUM_MAX_TEXTURES], GLuint* textures_planeta, bool textur_map, bool flagInvertY,
	int nptsU, CPunt3D PC_u[MAX_PATCH_CORBA], GLfloat pasCS, bool sw_PC, bool dib_TFrenet,
	COBJModel* objecteOBJ,
	glm::mat4 MatriuVista, glm::mat4 MatriuTG, float orbit_angle[], float rotation_angle[], bool draw_planets[9], int target_planet, glm::vec3& targetPos, 
	float moon_rotation_angle, float moon_orbit_angle, float jupiter_moon_ort[], float jupiter_moon_rot[], float saturn_titan_rot, float saturn_titan_ort,
	float unanos_titania_rot, float unanos_titania_ort, float neptune_triton_rot, float neptune_triton_ort, int scale_inc_index);

// Entorn VGI: dibuixa -> Funci� que dibuixa objectes simples de la llibreria GLUT segons obj
void dibuixa(GLuint sh_programID, char obj, glm::mat4 MatriuVista, glm::mat4 MatriuTG);

// Entorn VGI: Objecte Arc
void arc(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5]);
//oid sea(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, CColor colorM);
CVAO loadSea_VAO(CColor colorM);

// Entorn VGI: Tie (Nau enemiga Star Wars) - Objecte fet per alumnes.
void tie(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5]);
void Alas(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5]);
void Motor(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5]);
void Canon(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5]);
void Cuerpo(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5]);
void Cabina(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5]);

// Entorn VGI: Sis.
void sis(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], GLint uni_id, GLuint* textures_planeta, float orbit_angle[], float rotation_angle[], bool draw_planets[9], 
	int target_planet, glm::vec3& targetPos, float moon_rotation_angle, float moon_orbit_angle, float jupiter_moon_ort[], float jupiter_moon_rot[],
	float saturn_titan_rot, float saturn_titan_ort,
	float unanos_titania_rot, float unanos_titania_ort, float neptune_triton_rot, float neptune_triton_ort, int scale_inc_index);
// Dibujar �rbitas planetas
void DrawOrbit(float a, float b, int planet, int numSegments);

// Entorn VGI: Funcions locals a escena.cpp
// CString2char: Funci� de conversi� de variable CString a char * per a noms de fitxers 
//char* CString2Char(CString entrada);
#endif