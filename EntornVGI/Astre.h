// Incluir una vegada
#pragma once

// Incluim l'entorn VGI
#include "stdafx.h"
#include "material.h"
#include "visualitzacio.h"
#include "escena.h"

// MatriuTG Constant
const glm::mat4 MATRIU_TG(1.0);

// Per evitar repetir codi, utilitzarem la classe Astre com a molde
// pel sol, planetes, llunes...
class Astre {
public:
	// Constructor de la clase Astre, inicialitza les propietats i determina ya quin shader utilitzar
	Astre(float radius, GLuint sh_programID,
		glm::mat4 matriuTG, glm::mat4 viewMatrix) :
			m_radius(radius), m_sh_programID(sh_programID), //m_possition(glm::vec3(1.0)),
			m_normalMatrix(glm::mat4(1.0)), m_modelMatrix(glm::mat4(1.0)),
			m_transMatrix(glm::mat4(1.0)), m_scaleMatrix(glm::mat4(1.0)),
			m_rotMatrix(glm::mat4(1.0)), m_matriuTG(matriuTG),
			m_viewMatrix(viewMatrix) {}
	// Funció que s'encarrega de dibuixar l'Astre a l'espai.
	void draw();

private:
	float m_radius; // Radi de l'objecte (Per utilitzar amb m_scaleMatrix la majoría de vegades)
	//glm::vec3 m_possition; // Possició a on volem tenir l'objecte (s'uitlitzará posteriorment per translació)
	GLuint m_sh_programID; // ID del tipus de shader aplicat
	// Matrius de Transformació
	glm::mat4 m_normalMatrix,
			  m_modelMatrix,
			  m_transMatrix,
			  m_scaleMatrix,
			  m_rotMatrix;
	// Altres matrius
	glm::mat4 m_viewMatrix,
	          m_matriuTG;
};
