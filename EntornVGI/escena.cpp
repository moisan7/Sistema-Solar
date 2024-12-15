//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn bàsic VS2022 MULTIFINESTRA amb OpenGL 4.3, interfície MFC i llibreries GLM
//******** Ferran Poveda, Marc Vivet, Carme Julià, Débora Gil, Enric Martí Gòdia (Setembre 2024)
// escena.cpp : Aqui es on ha d'anar el codi de les funcions que 
//              dibuixin les escenes.
//
//    Versió 2.0:	- Objectes Cub, Esfera, Tetera (primitives libreria GLUT)
//
//	  Versió 2.2:	- Objectes Cub, Esfera, Tetera definides en fitxer font glut_geometry amb altres primitives GLUT
//
//	  Versió 2.5:	- Objectes cubRGB i Tie (nau Star Wars fet per alumnes)
//

#include "stdafx.h"
#include "material.h"
#include "visualitzacio.h"
#include "escena.h"

// Dibuixa Eixos Coordenades Món i Reixes, activant un shader propi.
void dibuixa_Eixos(GLuint ax_programID, bool eix, GLuint axis_Id, CMask3D reixa, CPunt3D hreixa, 
	glm::mat4 MatriuProjeccio, glm::mat4 MatriuVista)
{
// Visualització Eixos Coordenades Mòn
	glUseProgram(ax_programID);

// Pas Matrius Projecció i Vista Vista a shader
	glUniformMatrix4fv(glGetUniformLocation(ax_programID, "projectionMatrix"), 1, GL_FALSE, &MatriuProjeccio[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(ax_programID, "viewMatrix"), 1, GL_FALSE, &MatriuVista[0][0]);

// Attribute Locations must be setup before calling glLinkProgram()
	glBindAttribLocation(ax_programID, 0, "in_Vertex"); // Vèrtexs
	glBindAttribLocation(ax_programID, 1, "in_Color");	// Color

//  Dibuix dels eixos
	if (eix) draw_Eixos(axis_Id);

// Dibuixa el grid actiu
	//if ((reixa.x) || (reixa.y) || (reixa.z) || (reixa.w)) draw_Grid(reixa);
}

// Dibuixa Skybox en forma de Cub, activant un shader propi.
void dibuixa_Skybox(GLuint sk_programID, GLuint cmTexture, char eix_Polar, glm::mat4 MatriuProjeccio, glm::mat4 MatriuVista)
{
	glm::mat4 ModelMatrix(1.0);

	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content

// Activació shader per a cub skybox
	glUseProgram(sk_programID);

// Pas Matrius Projecció i Vista a shader
	glUniformMatrix4fv(glGetUniformLocation(sk_programID, "projectionMatrix"), 1, GL_FALSE, &MatriuProjeccio[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(sk_programID, "viewMatrix"), 1, GL_FALSE, &MatriuVista[0][0]);

// Rotar skyBox per a orientar sobre eix superior Z o X en Vista Esfèrica (POLARX, POLARY, POLARZ)
	if (eix_Polar == POLARZ) ModelMatrix = glm::rotate(ModelMatrix, radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
	else if (eix_Polar == POLARX) ModelMatrix = glm::rotate(ModelMatrix, radians(-90.0f), vec3(0.0f, 0.0f, 1.0f));

// Escalar Cub Skybox a 5000 per encabir objectes escena a l'interior
	ModelMatrix = glm::scale(ModelMatrix, vec3(8000.0f, 8000.0f, 8000.0f));		//glScaled(5000.0, 5000.0, 5000.0);
	glUniformMatrix4fv(glGetUniformLocation(sk_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);

// Activar textura cubemaps del Skybox per encabir objectes escena
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cmTexture);

// Attribute Locations must be setup before calling glLinkProgram()
	glBindAttribLocation(sk_programID, 0, "in_Vertex"); // Vèrtexs

//  Dibuix del Skybox
	drawCubeSkybox();

	glDepthFunc(GL_LESS); // set depth function back to default
}


// dibuixa_EscenaGL: Dibuix de l'escena amb comandes GL
void dibuixa_EscenaGL(GLuint sh_programID, bool eix, GLuint axis_Id, CMask3D reixa, CPunt3D hreixa, char objecte,
	CColor col_object, bool sw_mat[5],				//Añadido textures_planeta
	bool textur, GLuint texturID[NUM_MAX_TEXTURES], GLuint* textures_planeta, bool textur_map, bool flagInvertY,
	int nptsU, CPunt3D PC_u[MAX_PATCH_CORBA], GLfloat pasCS, bool sw_PC, bool dib_TFrenet,
	COBJModel* objecteOBJ,
	glm::mat4 MatriuVista, glm::mat4 MatriuTG, float orbit_angle[], float rotation_angle[], bool draw_planets[9], int target_planet, glm::vec3& targetPos, 
	float moon_rotation_angle, float moon_orbit_angle, float jupiter_moon_ort[], float jupiter_moon_rot[])
{
	float altfar = 0;
	GLint npunts = 0, nvertexs = 0;
	int i, j, k;
	GLdouble tras[3]; //Sierpinski Sponge
	CColor color_vermell, color_Mar;
	bool sw_material[5];
	
// Matrius de Transformació
	glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0), TransMatrix(1.0), ScaleMatrix(1.0), RotMatrix(1.0);

// VAO
	CVAO objectVAO;
	objectVAO.vaoId = 0;	objectVAO.vboId = 0;	objectVAO.nVertexs = 0;

	tras[0] = 0.0;	tras[1] = 0.0; tras[2] = 0.0;
	color_vermell.r = 1.0;	color_vermell.g = 0.0; color_vermell.b = 0.0; color_vermell.a = 1.0;
	sw_material[0] = false;	sw_material[1] = true; sw_material[2] = true; sw_material[3] = false;	sw_material[4] = true;

// Shader Visualització Objectes
	glUseProgram(sh_programID);

	// Parametrització i activació/desactivació de textures
			/*if (texturID[0] != -1) {
				SetTextureParameters(texturID[0], true, true, textur_map, false);
			}*/
	if (true) {
		glUniform1i(glGetUniformLocation(sh_programID, "textur"), GL_TRUE); //glEnable(GL_TEXTURE_2D);
		glUniform1i(glGetUniformLocation(sh_programID, "modulate"), GL_TRUE); //glEnable(GL_MODULATE);
	}
	/*else { glUniform1i(glGetUniformLocation(sh_programID, "textur"), GL_FALSE); //glDisable(GL_TEXTURE_2D);
			glUniform1i(glGetUniformLocation(sh_programID, "modulate"), GL_FALSE); //glDisable(GL_MODULATE);
		}*/
	glUniform1i(glGetUniformLocation(sh_programID, "flag_invert_y"), flagInvertY);

	// Attribute Locations must be setup before calling glLinkProgram()
	glBindAttribLocation(sh_programID, 0, "in_Vertex");		// Vèrtexs
	glBindAttribLocation(sh_programID, 1, "in_Normal");		// Normals
	glBindAttribLocation(sh_programID, 2, "in_TexCoord");		// Textura
	glBindAttribLocation(sh_programID, 3, "in_Color");	// Color

	// Definició propietats de reflexió (emissió, ambient, difusa, especular) del material.
	SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
	GLint uni_id = glGetUniformLocation(sh_programID, "texture_CelestialBody");
	switch (objecte)
	{

	// Arc
	case ARC:
		break;

// Dibuix de l'objecte TIE (Nau enemiga Star Wars)
	case TIE:
		break;
//SISTEMA SOLAR
	case SIS:
		// Definició propietats de reflexió (emissió, ambient, difusa, especular) del material pel color de l'objecte.
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		//carrgar texturas de planetas
		sis(sh_programID, MatriuVista, MatriuTG, sw_mat, uni_id, textures_planeta, orbit_angle, rotation_angle, draw_planets, target_planet, targetPos, moon_rotation_angle, moon_orbit_angle, 
			jupiter_moon_ort, jupiter_moon_rot);
		break;

// Dibuix de l'objecte OBJ
	case OBJOBJ:
		ModelMatrix = MatriuTG;
		// Pas ModelView Matrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		// Pas NormalMatrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

		// Definir característiques material de cada punt
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		// Objecte OBJ: Dibuix de l'objecte OBJ amb textures amb varis VAO's, un per a cada material.
		objecteOBJ->draw_TriVAO_OBJ(sh_programID);	// Dibuixar VAO a pantalla
		break;

// Corba Bezier
	case C_BEZIER:
		break;
// Corba Lemniscata
	case C_LEMNISCATA:
		break;
// Corba BSpline
	case C_BSPLINE:
		break;

// Corba Hermitte
	case C_HERMITTE:
		break;
// Corba Catmull-Rom
	case C_CATMULL_ROM:
		break;
// Matriu de Primitives SENSE pre-compilació prèvia en VBO (precompilació, draw i alliberació VBO en una funció)
	case MATRIUP:
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		for (i = 0; i < 10; i++)
			for (j = 0; j < 10; j++)
				for (k = 0; k < 10; k++)
				{	//glPushMatrix();
					  //glTranslated(i * 15.0, j * 15.0, k * 15.0);
					  //glScaled(5.0, 5.0, 5.0);
					TransMatrix = glm::translate(MatriuTG, vec3(i * 15.0f, j * 15.0f, k * 15.0));
					ModelMatrix = glm::scale(TransMatrix, vec3(5.0f, 5.0f, 5.0f));
					// Pas ModelView Matrix a shader
					glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
					// Pas NormalMatrix a shader
					NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
					glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
					glutSolidCube(1.0);
					//glutSolidTorus(1.0,2.0,20,20);
					//glutSolidOctahedron();
					//glutSolidTetrahedron();
					//glutSolidIcosahedron();
					//glutSolidRhombicDodecahedron();
					//glutSolidSierpinskiSponge(3,tras,1.0);
					//glutSolidTeapot(1.0);
					//gluCylinder(0.5,0.5,1.0,20,20);
					//gluSphere(1.0, 20, 20);
					//glPopMatrix();
				}
		for (i = 0; i < 10; i++)
			for (j = 0; j < 10; j++)
			{	//glPushMatrix();
				  //glTranslated(i * 15.0, j * 15.0, 160.0);
				  //glTranslated(i * 15.0, j * 15.0, 160.0);
				ModelMatrix = glm::translate(MatriuTG, vec3(i * 15.0f, j * 15.0f, 160.0f));
				// Pas ModelView Matrix a shader
				glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
				// Pas NormalMatrix a shader
				NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
				glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
				  //glScaled(5.0, 5.0, 5.0);
				  //glutSolidCube(1.0);
				glutSolidTorus(2.0,3.0,20,20);
				//glutSolidOctahedron();
				//glutSolidTetrahedron();
				//glutSolidIcosahedron();
				//glutSolidRhombicDodecahedron();
				//glutSolidSierpinskiSponge(3,tras,1.0);
				//glutSolidTeapot(1.0);
				//gluCylinder(0.5,0.5,1.0,20,20);
				//gluSphere(1.0, 20, 20);
				//glPopMatrix();
			}
// Dibuix una esfera
		//glPushMatrix();
		  //glTranslated(200.0, 200.0, 200.0);
		  //glScaled(5.0, 5.0, 5.0);
		TransMatrix = glm::translate(MatriuTG, vec3(200.0f, 200.0f, 200.0f));
		ModelMatrix = glm::scale(TransMatrix, vec3(5.0f, 5.0f, 5.0f));
		// Pas ModelView Matrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		// Pas NormalMatrix a shader
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
		gluSphere(1.0, 20, 20);
		//glPopMatrix();
		break;

// Matriu de Primitives AMB pre-compilació prèvia en VBO 
//	(separació en 3 funcions: *_VBO() per precompilació, draw*() per dibuix i deleteVBO() per alliberar VBO)
	case MATRIUP_VAO:
		break;

// Dibuix de la resta d'objectes
	default:
		// Definició propietats de reflexió (emissió, ambient, difusa, especular) del material.
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		dibuixa(sh_programID, objecte,MatriuVista, MatriuTG);
		break;
	}

// Enviar les comandes gràfiques a pantalla
//	glFlush();
}


// dibuixa: Funció que dibuixa objectes simples de la llibreria GLUT segons obj
void dibuixa(GLuint sh_programID, char obj, glm::mat4 MatriuVista, glm::mat4 MatriuTG)
{
	glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0), TransMatrix(1.0); // ScaleMatrix(1.0), RotMatrix(1.0);
	GLdouble tras[3]; //Sierpinski Sponge
	
	tras[0] = 0.0;	tras[1] = 0.0; tras[2] = 0.0;
}

// OBJECTE ARC
void arc(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5]){}


// Mar amb ondulacions
CVAO loadSea_VAO(CColor colorM)
{
	int i, j, step, it1, it2;
	double angle, delay, Nx;
	glm::mat4 ModelMatrix(1.0), NormalMatrix(1.0);

// VAO
	GLuint vaoId = 0; GLuint vboId = 0;
	CVAO seaVAO;
	seaVAO.vaoId = 0;	seaVAO.vboId = 0;	seaVAO.nVertexs = 0;
	std::vector <double> vertices, normals, colors, textures;	// Definició vectors dinàmics per a vertexs, normals i textures 
	vertices.resize(0);		normals.resize(0);		colors.resize(0);	textures.resize(0);			// Reinicialitzar vectors

// Aigua amb ondulacions simulades a partir de normals sinusoidals
	step = 10; //step = 5;
	delay = 0;
	it1 = 0;

//   SeleccionaMaterial(MAT_DEFAULT);	
	float h = 2 * PI*step / 500;
	for (j = -250; j<250 - step; j = j + step)
	{	delay = 1.0*h*it1;

		it2 = 0;
		//glColor3f(0.5f, 0.4f, 0.9f);
		for (i = -250; i<250 - step; i = i + step)
		{	//glBegin(GL_POLYGON);
			  angle = 1.0*it2*h * 15;
			  Nx = -cos(angle);
			  //glNormal3f(-cos(angle), 0, 1);
			  //glVertex3f(i, j, 0);			// Vèrtex P1
			  colors.push_back(colorM.r);		colors.push_back(colorM.g);		colors.push_back(colorM.b);		colors.push_back(colorM.a);  // Vector Colors
			  normals.push_back(Nx);			normals.push_back(0.0);			normals.push_back(1.0);			// Vector Normals
			  textures.push_back(0.0);			textures.push_back(0.0);										// Vector Textures
			  vertices.push_back(i);			vertices.push_back(j);			vertices.push_back(0.0);		// Vector Vertices

			  angle = 1.0*(it2 + 1.0)*h * 15;
			  Nx = -cos(angle);
			  //glNormal3f(-cos(angle), 0, 1);
			  //glVertex3f(i + step, j, 0);		// Vèrtex P2
			  colors.push_back(colorM.r);		colors.push_back(colorM.g);		colors.push_back(colorM.b);		colors.push_back(colorM.a);  // Vector Colors
			  normals.push_back(Nx);			normals.push_back(0.0);			normals.push_back(1.0);			// Vector Normals
			  textures.push_back(1.0);			textures.push_back(0.0);										// Vector Textures
			  vertices.push_back(i+step);		vertices.push_back(j);			vertices.push_back(0.0);		// Vector Vertices

			  angle = 1.0*(it2 + 1.0)*h * 15;
			  Nx = -cos(angle);
			  //glNormal3f(-cos(angle), 0, 1);
			  //glVertex3f(i + step, j + step, 0);// Vèrtex P3
			  colors.push_back(colorM.r);		colors.push_back(colorM.g);		colors.push_back(colorM.b);		colors.push_back(colorM.a);  // Vector Colors
			  normals.push_back(Nx);			normals.push_back(0.0);			normals.push_back(1.0);			// Vector Normals
			  textures.push_back(1.0);			textures.push_back(1.0);										// Vector Textures
			  vertices.push_back(i+step);		vertices.push_back(j+step);		vertices.push_back(0.0);		// Vector Vertices

			//glEnd();
// ----------------------- VAO
			//std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
			//draw_GL_TRIANGLES_VAO(vertices, normals, colors, textures);
			//vertices.resize(0);	normals.resize(0);	colors.resize(0);	textures.resize(0);	// Reinicialitzar vectors

			//glBegin(GL_POLYGON);
			  angle = 1.0*it2*h * 15;
			  //glNormal3f(-cos(angle), 0, 1);
			  //glVertex3f(i, j, 0);			// Vèrtex P1
			  colors.push_back(colorM.r);		colors.push_back(colorM.g);		colors.push_back(colorM.b);		colors.push_back(colorM.a);  // Vector Colors
			  normals.push_back(-cos(angle));	normals.push_back(0.0);			normals.push_back(1.0);			// Vector Normals
			  textures.push_back(1.0);			textures.push_back(1.0);										// Vector Textures
			  vertices.push_back(i);			vertices.push_back(j);			vertices.push_back(0.0);		// Vector Vertices

			  angle = 1.0*(it2 + 1)*h * 15;
			  //glNormal3f(-cos(angle), 0, 1);
			  //glVertex3f(i + step, j + step, 0);// Vèrtex P2
			  colors.push_back(colorM.r);		colors.push_back(colorM.g);		colors.push_back(colorM.b);		colors.push_back(colorM.a);  // Vector Colors
			  normals.push_back(-cos(angle));	normals.push_back(0.0);			normals.push_back(1.0);			// Vector Normals
			  textures.push_back(1.0);			textures.push_back(1.0);										// Vector Textures
			  vertices.push_back(i + step);		vertices.push_back(j + step);	vertices.push_back(0.0);		// Vector Vertices

			  angle = 1.0*it2*h * 15;
			  //glNormal3f(-cos(angle), 0, 1);
			  //glVertex3f(i, j + step, 0);		// Vèrtex P3
			  colors.push_back(colorM.r);		colors.push_back(colorM.g);		colors.push_back(colorM.b);		colors.push_back(colorM.a);  // Vector Colors
			  normals.push_back(-cos(angle));	normals.push_back(0.0);			normals.push_back(1.0);			// Vector Normals
			  textures.push_back(0.0);			textures.push_back(1.0);										// Vector Textures
			  vertices.push_back(i);			vertices.push_back(j + step);		vertices.push_back(0.0);	// Vector Vertices

			//glEnd();

			it2++;
		}
		it1++;
	}
// ----------------------- VAO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	//draw_GL_TRIANGLES_VAO(vertices, normals, colors, textures);
	// 
// Creació d'un VAO i un VBO i càrrega de la geometria. Guardar identificador VAO identificador VBO a struct CVAO.
	seaVAO = load_TRIANGLES_VAO(vertices, normals, colors, textures);
	//seaVAO.vaoId = vaoId;
	//seaVAO.vboId = vboId;

	seaVAO.nVertexs = (int)nv / 3;
	return seaVAO;
}

// OBJECTE TIE: FETS PER ALUMNES -----------------------------------------------------------------
// Objecte TIE
void tie(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5]){};
void Alas(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5]){};
void Motor(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5]){};
void Canon(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5]){}
void Cuerpo(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5]){}
void Cabina(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5]){}
// FI OBJECTE TIE: FETS PER ALUMNES -----------------------------------------------------------------

void IluminacioSol(GLint shaderId)
{
	//Inicialització Llum Sol
	LLUM llumSol;
	llumSol.posicio.R = 0;
	llumSol.posicio.alfa = 0;
	llumSol.posicio.beta = 0;
	llumSol.encesa = true;
	llumSol.difusa[0] = 1.0; llumSol.difusa[1] = 1.0; llumSol.difusa[2] = 1.0; llumSol.difusa[3] = 1.0;
	llumSol.especular[0] = 1.0; llumSol.especular[1] = 1.0; llumSol.especular[2] = 1.0; llumSol.especular[3] = 0.0;
	llumSol.atenuacio.a = 0.0;
	llumSol.atenuacio.b = 0.0015;
	llumSol.atenuacio.c = 0.0;

	//// Conversió angles graus -> radians
	GLdouble angv = llumSol.posicio.alfa * PI / 180;
	GLdouble angh = llumSol.posicio.beta * PI / 180;

	// Conversió Coord. esfèriques -> Coord. cartesianes per a la posició de la llum
	GLfloat position[] = { llumSol.posicio.R * cos(angh) * cos(angv),
						llumSol.posicio.R * sin(angh) * cos(angv),
						llumSol.posicio.R * sin(angv), 1.0f };

	//Pas de paràmetres de llum a shader
	glUniform4f(glGetUniformLocation(shaderId, "LightSource[0].position"), position[0], position[1], position[2], position[3]);

	glUniform4f(glGetUniformLocation(shaderId, "LightSource[0].diffuse"), llumSol.difusa[0], llumSol.difusa[1],
		llumSol.difusa[2], llumSol.difusa[3]);

	glUniform4f(glGetUniformLocation(shaderId, "LightSource[0].specular"), llumSol.especular[0], llumSol.especular[1],
		llumSol.especular[2], llumSol.especular[3]);

	glUniform1i(glGetUniformLocation(shaderId, "LightSource[0].restricted"), false);

	glUniform3f(glGetUniformLocation(shaderId, "LightSource[0].attenuation"), llumSol.atenuacio.a, llumSol.atenuacio.b, llumSol.atenuacio.c);

	glUniform1i(glGetUniformLocation(shaderId, "LightSource[0].sw_light"), llumSol.encesa);

	
}

//Objecte sis
void sis(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5],
	GLint uni_id, GLuint* textures_planeta, float orbit_angle[], float rotation_angle[], 
	bool draw_planets[9], int target_planet, glm::vec3& targetPos, float moon_rotation_angle, float moon_orbit_angle, 
	float jupiter_moon_ort[], float jupiter_moon_rot[])
{	
	glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0), TransMatrix(1.0);
	CColor col_object;
	col_object.r = 0.5; col_object.g = 0.5; col_object.b = 0.5; col_object.a = 1.0;
	SeleccionaColorMaterial(shaderId, col_object, sw_mat);

	/*------------SUN------------*/
	glm::mat4 sunMatrix(1.0f);
	// Pas de paràmetres material a shader
	glUniform4f(glGetUniformLocation(shaderId, "material.emission"), 1.0, 1.0, 1.0, 1.0);
	glActiveTexture(GL_TEXTURE0);
	SetTextureParameters(textures_planeta[0], true, true, false, false);
	glUniform1i(uni_id, 0);
	TransMatrix = glm::translate(MatriuTG, vec3(0.0f, 0.0f, 0.0f));
	TransMatrix = glm::rotate(TransMatrix, -ROTATION_ANGLE[0], glm::vec3(1.0f, 0.0f, 0.0f));
	TransMatrix = glm::rotate(TransMatrix, radians(rotation_angle[0]), glm::vec3(0.0f, 0.0f, 1.0f));
	sunMatrix = glm::scale(TransMatrix, vec3(P_SCALE[0], P_SCALE[0], P_SCALE[0]));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &sunMatrix[0][0]);
	// Pas NormalMatrix a shader
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &sunMatrix[0][0]);
	draw_TriEBO_Object(GLU_SPHERE);
	IluminacioSol(shaderId);
	/*------------SUN------------*/

	// Dibujado de órbitas
	if (draw_planets[8]) {
		glm::mat4 orbitMatrix(1.0f); // Matriz órbitas
		glEnable(GL_BLEND);                                 // Habilitar transparencia
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // Configuración de transparencia

		for (int i = 1; i <= 8; i++) { // De 1 a 9 para dibujar todas
			float a = SEMIMAJOR_AXIS[i - 1]; // Semieje mayor del planeta
			float b = a * sqrt(1.0f - ECCENTRICITIES[i - 1] * ECCENTRICITIES[i - 1]);

			glColor4f(1.0f, 1.0f, 1.0f, 0.2f); // Blanco con transparencia 50%
			glLineWidth(0.5f);                 // Grosor de línea

			glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &orbitMatrix[0][0]);
			// Desactivar reflectivitat de llum d'emissió
			//glUniform4f(glGetUniformLocation(shaderId, "material.emission"), 0.0, 0.0, 0.0, 1.0);
			// Dibujar órbita
			DrawOrbit(a, b, (i - 1), 10000); // 10000 segmentos (para suavizar la línea)
		}
	}

	// Dibujado de planetas + movimiento
	for (int i = 1; i <= 8; i++) { // De 1 a 8 para dibujar todos (Moon => i = 9)
		// Verificar si el planeta debe dibujarse
		if (draw_planets[i - 1] == false) continue; // Saltar si el planeta no debe dibujarse

		/*----------MOON----------*/
		if (i-1 == 3 && draw_planets[2]) // if drawing Earth, draw Moon:
		{
			float x = 0;
			float y = 0;
			glm::mat4 moonTransMatrix = glm::mat4(1.0f);

			glActiveTexture(GL_TEXTURE0);
			SetTextureParameters(textures_planeta[9], true, true, false, false);
			glUniform1i(uni_id, 0);

			// Calculos de orbitas con excentricidad
			float a = SEMIMAJOR_AXIS[8];
			float e = ECCENTRICITIES[8];
			float r = (a * (1 - e * e)) / (1 + e * cos(moon_rotation_angle));
			x = r * cos(moon_rotation_angle); // X position based on orbit angle and excentricity
			y = r * sin(moon_rotation_angle); // Y position based on orbit angle and excentricity

			// Transformaciones
			moonTransMatrix = glm::translate(TransMatrix, vec3(x, y, 0.0f));
			moonTransMatrix = glm::rotate(moonTransMatrix, radians(moon_orbit_angle), vec3(0.0f, 0.0f, 1.0f));
			moonTransMatrix = glm::scale(moonTransMatrix, vec3(P_SCALE[9], P_SCALE[9], P_SCALE[9]));

			// Pas ModelView Matrix a shader
			glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &moonTransMatrix[0][0]);
			// Pas NormalMatrix a shader
			NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
			glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

			draw_TriEBO_Object(GLU_SPHERE);
		}
		/*----------MOON----------*/

		/*----------JUIPTER MOON----------*/
		if (i - 1 == 5 && draw_planets[4]) // if drawing Earth, draw Moon:
		{
			for (int i = 0; i < 3; i++)
			{
				float x = 0;
				float y = 0;
				glm::mat4 ju_moonTransMatrix = glm::mat4(1.0f);

				glActiveTexture(GL_TEXTURE0);
				SetTextureParameters(textures_planeta[11 + i], true, true, false, false);
				glUniform1i(uni_id, 0);

				// CAlculos de Orbitas con excentricidad
				float a = SEMIMAJOR_AXIS[9 + i];
				float e = ECCENTRICITIES[9 + i];
				float r = (a * (1 - e * e)) / (1 + e * cos(jupiter_moon_rot[i])); // Distancia radial
				x = r * cos(jupiter_moon_rot[i]); // Posición X basada en el ángulo orbital
				y = r * sin(jupiter_moon_rot[i]); // Posición Y basada en el ángulo orbital

				// Transformaciones
				ju_moonTransMatrix = glm::translate(TransMatrix, vec3(x, y, 0.0f));
				ju_moonTransMatrix = glm::rotate(ju_moonTransMatrix, radians(jupiter_moon_ort[i]), vec3(0.0f, 0.0f, 1.0f));
				ju_moonTransMatrix = glm::scale(ju_moonTransMatrix, vec3(P_SCALE[10 + i], P_SCALE[10 + i], P_SCALE[10 + i]));

				// Pasar ModelView Matrix a shader
				glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ju_moonTransMatrix[0][0]);
				// Pasar NormalMatrix a shader
				NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
				glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

				draw_TriEBO_Object(GLU_SPHERE);
			}
		}
		/*----------JUIPTER MOON----------*/

		/*----------SATRUN RING----------*/
		if (i - 1 == 6 && draw_planets[5]) // if drawing Earth, draw Moon:
		{
			
			glm::mat4 moonTransMatrix = glm::mat4(1.0f);

			glActiveTexture(GL_TEXTURE0);
			SetTextureParameters(textures_planeta[10], true, true, false, false);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Clamp in the s direction
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Clamp in the t direction
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Minification filtering
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Magnification filtering
			glUniform1i(uni_id, 0);
			
			moonTransMatrix = glm::translate(TransMatrix, vec3(0.0f, 0.0f, 0.0f));
			moonTransMatrix = glm::rotate(moonTransMatrix, radians(rotation_angle[i]), glm::vec3(0.0f, 0.0f, 1.0f));
			moonTransMatrix = glm::scale(moonTransMatrix, vec3(P_SCALE[13], P_SCALE[13], P_SCALE[13]));

			// Pas ModelView Matrix a shader
			glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &moonTransMatrix[0][0]);
			// Pas NormalMatrix a shader
			NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
			glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
			draw_TriEBO_Object(GLU_DISK);
		}
		/*----------SATRUN RING----------*/


		glActiveTexture(GL_TEXTURE0);
		SetTextureParameters(textures_planeta[i], true, true, false, false);
		glUniform1i(uni_id, 0);

		// Desactivar reflectivitat de llum d'emissió
		glUniform4f(glGetUniformLocation(shaderId, "material.emission"), 0.0, 0.0, 0.0, 1.0);

		// Calculos órbitas elípticas
		float a = SEMIMAJOR_AXIS[i - 1]; // Semieje mayor para cada planeta
		float b = a * sqrt(1.0f - ECCENTRICITIES[i - 1] * ECCENTRICITIES[i - 1]); // Semieje menor
		float x = a * (cos(orbit_angle[i - 1]) - ECCENTRICITIES[i - 1]);  // Coordenada X en la elipse
		float y = b * sin(orbit_angle[i - 1]);  // Coordenada Y en la elipse

		float ORBIT_ANGLE_Y = y * cos(radians(INCLINATION[i - 1])); // Efecto de inclinación en Y
		float ORBIT_ANGLE_Z = y * sin(radians(INCLINATION[i - 1])); // Efecto de inclinación en Z

		TransMatrix = glm::translate(MatriuTG, vec3(x, ORBIT_ANGLE_Y, ORBIT_ANGLE_Z));
		// Inclinacion
		TransMatrix = glm::rotate(TransMatrix, -ROTATION_ANGLE[i], ROTATION_AXIS[i - 1]);
		// Rotacion
		TransMatrix = glm::rotate(TransMatrix, radians(rotation_angle[i]), glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(TransMatrix, vec3(P_SCALE[i], P_SCALE[i], P_SCALE[i]));

		// Pas ModelView Matrix a shader
		glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);

		// Pas NormalMatrix a shader
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

		draw_TriEBO_Object(GLU_SPHERE);
		// Si el planeta es el objetivo, actualiza la posición de la cámara
		if (i == target_planet) {
			targetPos = glm::vec3(x, ORBIT_ANGLE_Y, ORBIT_ANGLE_Z);
		}
		else if (target_planet == 0) {
			targetPos = vec3(0.0f);
		}
	}
};

// Dibujar órbitas planetas
void DrawOrbit(float a, float b, int planet, int numSegments) {
	glBegin(GL_LINE_LOOP); // Dibujar como bucle cerrado
	for (int i = 0; i < numSegments; i++) {
		float angle = 2.0f * M_PI * i / numSegments; // Ángulo actual
		float x = a * (cos(angle) - ECCENTRICITIES[planet]); // Coordenada X elipse
		float y = b * sin(angle); // Coordenada Y elipse
		float ORBIT_ANGLE_Y = y * cos(radians(INCLINATION[planet])); // Efecto de inclinación en Y
		float ORBIT_ANGLE_Z = y * sin(radians(INCLINATION[planet])); // Efecto de inclinación en Z
		glVertex3f(x, ORBIT_ANGLE_Y, ORBIT_ANGLE_Z);   // Punto en la órbita XY
	}
	glEnd();
}
