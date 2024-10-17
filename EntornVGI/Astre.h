// Incluir una vegada
#pragma once

// Incluim l'entorn VGI
#include "stdafx.h"
#include "material.h"
#include "visualitzacio.h"
#include "escena.h"

// Per evitar repetir codi, utilitzarem la classe Astre com a molde
// pel sol, planetes, llunes...
class Astre {
public:
	// Constructor de la clase Astre, inicialitza les propietats i determina ya quin shader utilitzar
	Astre(vec3 radius, vec3 possition, GLuint sh_programID,
		mat4 matriuTG, mat4 viewMatrix);
	Astre(float radius, vec3 possition, GLuint sh_programID,
		mat4 matriuTG, mat4 viewMatrix);
	// Funció que s'encarrega de dibuixar l'Astre a l'espai.
	void draw();

private:
	vec3 m_radius; // Radi de l'objecte
	vec3 m_possition; // Possició a on volem tenir l'objecte 
	GLuint m_sh_programID; // ID del tipus de shader aplicat
	// Matrius de Transformació
	mat4 m_normalMatrix,
		 m_modelMatrix,
		 m_transMatrix,
		 m_scaleMatrix,
		 m_rotMatrix;
	// Altres matrius
	mat4 m_viewMatrix,
	     m_matriuTG;
};
