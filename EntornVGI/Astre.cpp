#include "stdafx.h"
#include "Astre.h"



// Funció que s'encarrega de dibuixar l'Astre a l'espai.
void Astre::draw(){
	m_transMatrix = glm::translate(m_matriuTG, vec3(0.0f, 0.0f, 0.0f));
	m_modelMatrix = glm::scale(m_transMatrix, vec3(m_radius, m_radius, m_radius));
	glUniformMatrix4fv(glGetUniformLocation(m_sh_programID, "modelMatrix"), 1, GL_FALSE, &m_modelMatrix[0][0]);
	m_normalMatrix = transpose(inverse(m_viewMatrix * m_modelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(m_sh_programID, "normalMatrix"), 1, GL_FALSE, &m_normalMatrix[0][0]);
	draw_TriEBO_Object(GLU_SPHERE);
}
