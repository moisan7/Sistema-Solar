#include "stdafx.h"
#include "Astre.h"

Astre::Astre(vec3 radius, vec3 possition, GLuint sh_programID,
	mat4 matriuTG, mat4 viewMatrix)
{
	// Matrius de Transformació 
	m_normalMatrix = mat4(1.0);
	m_modelMatrix = mat4(1.0);
	m_transMatrix = mat4(1.0);
	m_scaleMatrix = mat4(1.0);
	m_rotMatrix = mat4(1.0);
	// Característiques de l'Astre
	m_radius = radius;
	m_possition = possition;
	// Paràmetres importants
	m_sh_programID = sh_programID;
	m_matriuTG = matriuTG;
	m_viewMatrix = viewMatrix;
}

Astre::Astre(float radius,  vec3 possition, GLuint sh_programID,
	 mat4 matriuTG,  mat4 viewMatrix)
{
	// Matrius de Transformació 
	m_normalMatrix = mat4(1.0);
	m_modelMatrix = mat4(1.0);
	m_transMatrix = mat4(1.0);
	m_scaleMatrix = mat4(1.0);
	m_rotMatrix = mat4(1.0);
	// Característiques de l'Astre
	m_radius =  vec3(radius, radius, radius);
	m_possition = possition;
	// Paràmetres importants
	m_sh_programID = sh_programID;
	m_matriuTG = matriuTG;
	m_viewMatrix = viewMatrix;
}

// Funció que s'encarrega de dibuixar l'Astre a l'espai.
void Astre::draw(){
	m_transMatrix = translate(m_matriuTG, m_possition);
	m_modelMatrix = scale(m_transMatrix, m_radius);
	glUniformMatrix4fv(glGetUniformLocation(m_sh_programID, "modelMatrix"), 1, GL_FALSE, &m_modelMatrix[0][0]);
	m_normalMatrix = transpose(inverse(m_viewMatrix * m_modelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(m_sh_programID, "normalMatrix"), 1, GL_FALSE, &m_normalMatrix[0][0]);
	draw_TriEBO_Object(GLU_SPHERE);
}
