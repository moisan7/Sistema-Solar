//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn bàsic VS2022 MULTIFINESTRA amb OpenGL 4.3, interfície MFC i llibreries GLM
//******** Ferran Poveda, Marc Vivet, Carme Julià, Débora Gil, Enric Martí Gòdia (Setembre 2024)
// constants.h : Definició de constants compartides
//				 CENtornVGIView.cpp, visualitzacio.cpp i escena.cpp


#ifndef CONST_H
#define CONST_H

//--------------- VGI: Tipus de Càmera
#define CAP ' '
#define CAM_ESFERICA 'E'
#define CAM_GEODE 'G'
#define CAM_NAVEGA 'N'

//--------------- VGI: Tipus de Projecció
#define AXONOM 'A'
#define ORTO 'O'
#define PERSPECT 'P'
#define IMA_PICK 3
#define PASSEIG_V 4


//--------------- VGI: Tipus de Polars (per la Visualització Interactiva)
#define POLARZ 'Z'
#define POLARY 'Y'
#define POLARX 'X'

//-------------- VGI: Tipus d'Objectes
#define ARC 'a'
#define CAMIO 'm'
#define CILINDRE 'y'
#define CUB 'c'
#define CUB_RGB 'd'
#define C_BEZIER '2'
#define C_LEMNISCATA 'K'
#define C_LEMNISCATA2D 'W'
#define C_BSPLINE 'q'
#define C_HERMITTE 'h'
#define C_CATMULL_ROM 'R'
#define ESFERA 'e'
#define O_FRACTAL 'f'
#define HIDROAVIO 'H'
#define ICOSAEDRE 'i'
#define MATRIUP 'M'
#define MATRIUP_VAO 'm'
#define ROBOT 'u'
#define TETERA 't'
#define TEXTE_BITMAP 'B'
#define TEXTE_STROKE 'S'
#define TIE 'T'
#define TORUS 'o'
#define VAIXELL 'v'
#define OBJ3DS '3'		// Objecte format 3DS
#define OBJOBJ '4'		// Objecte format OBJ
// SISTEMA SOLAR
#define SIS 'L'
const double M_PI = glm::pi<double>();
const float INCREMENTADOR[9] = { 0, 1, 2, 5, 10, 100, 200, 500, 1000 };
const float ORBIT_SPEED[12] = {			// 1 SEGUNDO = 1 DIA TERRESTRE
    2 * glm::pi<float>() / 88.0f,		// Mercury (88d)
    2 * glm::pi<float>() / 225.0f,		// Venus (225d)
    2 * glm::pi<float>() / 365.0f,		// Earth (365d)
    2 * glm::pi<float>() / 687.0f,		// Mars (687d)
    2 * glm::pi<float>() / 4333.0f,		// Jupiter (4333d)
    2 * glm::pi<float>() / 10759.0f,	// Saturn (10759d)
    2 * glm::pi<float>() / 30689.0f,	// Uranus (30689d)
    2 * glm::pi<float>() / 60182.0f,	// Neptune (60182d)
	2 * glm::pi<float>() / 27.32f,		// Moon (27.32d)
	2 * glm::pi<float>() / 27.32f,      // Europa (3.55d)
	2 * glm::pi<float>() / 27.32f,      // Ganymede (7.15d)
	2 * glm::pi<float>() / 27.32f       // Callisto (16.69d)
};
const float ECCENTRICITIES[12]= { // REAL
	0.2056f,		// Mercury
	0.0067f,		// Venus
	0.0167f,		// Earth
	0.0934f,		// Mars
	0.0489f,		// Jupiter
	0.0565f,		// Saturn
	0.0463f,		// Uranus
	0.0097f,		// Neptune
	0.0549f,		// Moon
	0.0094f,		// Europa
	0.0013f,		// Ganymede
	0.0074f			// Callisto
};
const float INCLINATION[8] = { // REAL (GRADOS)
	7.00487f,	// Mercury
	3.39471f, 	// Venus
	0.00005f,	// Earth
	1.85061f, 	// Mars
	1.30463f, 	// Jupiter 
	2.48524f, 	// Saturn
	0.76986f, 	// Uranus
	1.76917f, 	// Neptune
};
const float ROTATION_SPEED[13] = { // CORRECTO
	365.0f * (1.0f / 25.0f),	// Sun: 25.0 veces más lento
	365.0f * (1.0f / 58.6f),	// Mercury: 58.6 veces más lento
	365.0f * (1.0f / 243.0f),	// Venus: 243 veces más lento
	365.0f,						// Earth: BASE (2pi/24)
	365.0f * 1.025f,            // Mars: 1.025 veces más rápido
	365.0f * 2.4f,				// Jupiter: 2.4 veces más rápido
	365.0f * 2.24f,				// Saturn: 2.24 veces más rápido
	-365.0f * 1.4f,				// Uranus: 1.4 veces más rápido
	365.0f * 1.49f ,            // Neptune: 1.49 veces más rápido
	365.0f * (1.0f / 27.32f),	// Moon: 27.32 veces más lento
	365.0f * (1.0f / 3.55f),    // Europa: 3.55 veces más lento
	365.0f * (1.0f / 7.15f),    // Ganymede: 7.15 veces más lento
	365.0f * (1.0f / 16.69f)    // Callisto: 16.69 veces más lento
};
const float SEMIMAJOR_AXIS[12] = { // REAL (UA) * 100
	38.7f,      // Mercury
	72.3f,      // Venus
	100.0f,     // Earth
	152.0f,     // Mars
	520.0f,     // Jupiter
	956.0f,     // Saturn
	1930.0f,    // Uranus
	3040.0f,    // Neptune
	12.85f,     // Moon * 50 (relative to Earth)
	44.83f,      // Europa * 100 (relative to Jupiter)
	71.54f,      // Ganymede * 100 (relative to Jupiter)
	125.85f      // Callisto * 100 (relative to Jupiter)
};
const float ROTATION_ANGLE[9] = { // INCLINACION DEL EJE (ROTATION_AXIS)
		glm::radians(7.25f),    // Sun
		glm::radians(0.034f),   // Mercury
		glm::radians(177.4f),	// Venus
		glm::radians(23.44f),	// Earth
		glm::radians(25.2f),    // Mars
		glm::radians(3.1f),     // Jupiter
		glm::radians(26.7f),    // Saturn
		glm::radians(97.8f),	// Uranus
		glm::radians(28.3f)		// Neptune
};
const glm::vec3 ROTATION_AXIS[9] = { // EJE SOBRE EL QUE SE APLICA LA INCLINACION
		glm::vec3(1.0f, 0.0f, 0.0f),	// Mercury
		glm::vec3(1.0f, 0.0f, 0.0f),	// Venus
		glm::vec3(1.0f, 0.0f, 0.0f),	// Earth
		glm::vec3(1.0f, 0.0f, 0.0f),    // Mars
		glm::vec3(1.0f, 0.0f, 0.0f),    // Jupiter
		glm::vec3(1.0f, 0.0f, 0.0f),    // Saturn
		glm::vec3(0.0f, 1.0f, 0.0f),	// Uranus
		glm::vec3(1.0f, 0.0f, 0.0f),	// Neptune
};
const float P_SCALE[14] = { // Todo multiplicado * 10000
	  93.058f / 30.0f,    // Sun
	  0.326f,             // Mercury
	  0.809f,             // Venus
	  0.851f,             // Earth
	  0.453f,             // Mars
	  9.34f / 5.0f,       // Jupiter
	  7.78f / 5.0f,       // Saturn
	  3.39f / 2.5f,       // Uranus
	  3.29f / 2.5f,       // Neptune
	  0.232f,			  // Moon
	  0.208f,			  // Europa
	  0.352f,			  // Ganymede
	  0.322f,			  // Callisto
	  (7.78f / 5.0f) * 1.5f // Saturns Ring
};

//-------------- VGI: Tipus d'Iluminacio
#define PUNTS 'P'
#define FILFERROS 'w'
#define PLANA 'p'
#define SUAU 's'

//-------------- VGI: Objectes precompilats OpenGL amb glNewList
#define EIXOS 1			// Eixos
#define FRACTAL 2		// Fractal
#define OBJECTEOBJ 3	// Objecte OBJ sense textures
#define OBJECTEOBJT 4   // Objecte OBJ amb textures
#define SEA 5			// Objecte SEA

// -------------- VGI: Definició dels valors del pla near i far del Volum de Visualització en Perspectiva
const double p_near=0.01;
const double p_far=50000.0;

//-------------- VGI: Tipus d'Objectes Picking
#define PICKCAP 0
#define PICKFAR 1
#define PICKVAIXELL 2 
#define PICKHIDRO 3 

// -------------- VGI: CONSTANTS TEXTURES
// Nombre màxim de textures
#define NUM_MAX_TEXTURES 10

// Tipus de textures
#define CAP ' '
#define FUSTA 'F'
#define MARBRE 'M'
#define METALL 'E'
#define FITXER 'f'
#define FITXERBMP 'f'
#define FITXERIMA 'I'

// --------------  VGI: NOMBRE DE LLUMS: Nombre de Llums de l'aplicació, les d'OpenGL
const int NUM_MAX_LLUMS = 8;

// Permet prendre les funcions _s enlloc de les deprecated (strcpy -> strcpy_s). Ja definit
//#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1

// Elimina missatges warning que venen de crides deprecated (strcpy -> strcpy_s).
//#define _CRT_SECURE_NO_WARNINGS //-> Posat a "Project"->"Properties"->"Configuration properties"->"C/C++"->"Preprocessor"->"Preprocessor definitions".

// -------------- VGI: SHADERS --> Tipus de Shaders
#define CAP_SHADER ' '
#define FLAT_SHADER 'f'
#define GOURAUD_SHADER 'G'
#define PHONG_SHADER 'P'
#define FILE_SHADER 'F'
#define PROG_BINARY_SHADER 'p'
#define PROG_BINARY_SHADERW 'W'

//--------------- VGI: Valor constant de pi
const double PI=3.14159;
const double TWOPI = 2 * PI;
const double PID2 = PI / 2;
//const double pi=3.14159265358979323846264338327950288419716939937510f;

// --------------- GMS. GRID
#define GRID_SIZE 50	// Maximum size of the grid in OpenGL World Coordenates unities.
#define PAS_GRID 1		// Step to shift the grid planes.

/* --------------- VGI: Estructura coordenada 2D (Ja definida en Visual Studio 2022)
struct CPoint
{   GLint x;
    GLint y;
};
*/

// --------------- VGI: Estructura coordenada 3D
struct CPunt3D
{   GLdouble x;
    GLdouble y;
	GLdouble z;
	GLdouble w;
};

// --------------- GMS: 3Màscara booleana sobre coordenades 3D
struct CMask3D
{	bool x;
	bool y;
	bool z;
	bool w;
};

// --------------- VGI: Estructura de color R,G,B,A
struct CColor
{   GLdouble r;
    GLdouble g;
	GLdouble b;
	GLdouble a;
};

// --------------- VGI: Estructura coordenada Esfèrica 3D
struct CEsfe3D
{   GLdouble R;
    GLdouble alfa;
	GLdouble beta;
};

// --------------- VGI: Estructura LLista VAO
struct CVAO
{	GLuint vaoId;
	GLuint vboId;
	GLuint eboId;
	GLint nVertexs;
	GLint nIndices;
};

// --------------- VGI: INSTANCIA (TG d'instanciació d'un objecte)
struct INSTANCIA
{	CPunt3D VTras;	// Vector de Traslació
	CPunt3D VScal;	// Vector d'Escalatge
	CPunt3D VRota;	// Vector de Rotació
	float rotationAngle; // Ángulo de rotación
};

// --------------- VGI: Coeficients equació d'atenuació de la llum fatt=1/(ad2+bd+c)
struct CAtenua
{   GLdouble a;
    GLdouble b;
	GLdouble c;
};

// --------------- VGI: Estructura de coeficients de reflectivitat de materials
struct MATERIAL
{
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat emission[4];
	GLfloat shininess;
};

// --------------- VGI: Estructura font de llum
struct LLUM
{	bool encesa;				// Booleana que controla si la llum és encesa [TRUE] o no [FALSE]
	CEsfe3D posicio;			// Posició d ela foont de llum en coordenades esfèriques.
	GLfloat difusa[4];			// Intensitat difusa de la font de llum (r,g,b,a)
	GLfloat especular[4];		// Intensitat especular de la font de llum (r,g,b,a)
	CAtenua atenuacio;			// Coeficients de l'equació d'atenuació de la llum fatt=1/(ad2+bd+c)
	bool restringida;			// Booleana que indica si la font de llum és restringida [TRUE] i per tant són vàlids els coeficients posteriors o no [FALSE].
	GLfloat spotdirection[3];	// Vector de direció de la font de llum restringida (x,y,z).
	GLfloat spotcoscutoff;		// Coseno de l'angle d'obertura de la font de llum restringida.
	GLfloat spotexponent;		// Exponent que indica l'atenuació de la font del centre de l'eix a l'exterior, segons model de Warn.
};

#endif