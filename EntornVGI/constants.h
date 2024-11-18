//******** PRACTICA VISUALITZACI� GR�FICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn b�sic VS2022 MULTIFINESTRA amb OpenGL 4.3, interf�cie MFC i llibreries GLM
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� G�dia (Setembre 2024)
// constants.h : Definici� de constants compartides
//				 CENtornVGIView.cpp, visualitzacio.cpp i escena.cpp


#ifndef CONST_H
#define CONST_H

//--------------- VGI: Tipus de C�mera
#define CAP ' '
#define CAM_ESFERICA 'E'
#define CAM_GEODE 'G'
#define CAM_NAVEGA 'N'

//--------------- VGI: Tipus de Projecci�
#define AXONOM 'A'
#define ORTO 'O'
#define PERSPECT 'P'
#define IMA_PICK 3
#define PASSEIG_V 4


//--------------- VGI: Tipus de Polars (per la Visualitzaci� Interactiva)
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
const double M_PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;
const float DISTANCE_FROM_SUN[9] = { 47.5f, 67.5f, 87.5f, 107.5f, 157.5f, 217.5f, 257.5f, 287.5f, 295.0f };
//const float ORBIT_SPEED[9] = { 0.001f, -0.002f, 0.003f, -0.004f, 0.005f, -0.006f, 0.007f, -0.008f, 0.009f };
const float ORBIT_SPEED[9] = { 0.005f, 0.005f, 0.005f, 0.005f, 0.005f, 0.005f, 0.005f, 0.005f, 0.005f };
//const float ROTATION_SPEED[10] = { 1.0f, -1.0f, 5.0f, -5.0f, 10.0f, -10.0f, 20.0f, -20.0f, 50.0f, -50.0f };
const float ROTATION_SPEED[10] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
const float SEMIMAJOR_AXIS[9] = { 47.5f, 67.5f, 87.5f, 107.5f, 157.5f, 217.5f, 257.5f, 287.5f, 295.0f };
const float SEMIMINOR_AXIS[9] = {
	47.5f * 0.7f,  // Mercurio - 33.25
	67.5f * 0.75f, // Venus - 50.625
	87.5f * 0.75f, // Tierra - 65.625
	107.5f * 0.7f, // Marte - 75.25
	157.5f * 0.65f, // J�piter - 102.375
	217.5f * 0.6f, // Saturno - 130.5
	257.5f * 0.65f, // Urano - 167.375
	287.5f * 0.6f,  // Neptuno - 172.5
	295.0f * 0.55f  // Plut�n - 162.25
};
/*
const float SEMIMINOR_AXIS[9] = {
	47.5f * 0.5f,  // Mercurio - 23.75
	67.5f * 0.5f,  // Venus - 33.75
	87.5f * 0.45f, // Tierra - 39.375
	107.5f * 0.45f, // Marte - 48.375
	157.5f * 0.4f, // J�piter - 63.0
	217.5f * 0.4f, // Saturno - 87.0
	257.5f * 0.45f, // Urano - 115.875
	287.5f * 0.4f,  // Neptuno - 115.0
	295.0f * 0.4f   // Plut�n - 118.0
};
*/



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

// -------------- VGI: Definici� dels valors del pla near i far del Volum de Visualitzaci� en Perspectiva
const double p_near=0.01;
const double p_far=50000.0;

//-------------- VGI: Tipus d'Objectes Picking
#define PICKCAP 0
#define PICKFAR 1
#define PICKVAIXELL 2 
#define PICKHIDRO 3 

// -------------- VGI: CONSTANTS TEXTURES
// Nombre m�xim de textures
#define NUM_MAX_TEXTURES 10

// Tipus de textures
#define CAP ' '
#define FUSTA 'F'
#define MARBRE 'M'
#define METALL 'E'
#define FITXER 'f'
#define FITXERBMP 'f'
#define FITXERIMA 'I'

// --------------  VGI: NOMBRE DE LLUMS: Nombre de Llums de l'aplicaci�, les d'OpenGL
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

// --------------- GMS: 3M�scara booleana sobre coordenades 3D
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

// --------------- VGI: Estructura coordenada Esf�rica 3D
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

// --------------- VGI: INSTANCIA (TG d'instanciaci� d'un objecte)
struct INSTANCIA
{	CPunt3D VTras;	// Vector de Traslaci�
	CPunt3D VScal;	// Vector d'Escalatge
	CPunt3D VRota;	// Vector de Rotaci�
	float rotationAngle; // �ngulo de rotaci�n
};

// --------------- VGI: Coeficients equaci� d'atenuaci� de la llum fatt=1/(ad2+bd+c)
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
{	bool encesa;				// Booleana que controla si la llum �s encesa [TRUE] o no [FALSE]
	CEsfe3D posicio;			// Posici� d ela foont de llum en coordenades esf�riques.
	GLfloat difusa[4];			// Intensitat difusa de la font de llum (r,g,b,a)
	GLfloat especular[4];		// Intensitat especular de la font de llum (r,g,b,a)
	CAtenua atenuacio;			// Coeficients de l'equaci� d'atenuaci� de la llum fatt=1/(ad2+bd+c)
	bool restringida;			// Booleana que indica si la font de llum �s restringida [TRUE] i per tant s�n v�lids els coeficients posteriors o no [FALSE].
	GLfloat spotdirection[3];	// Vector de direci� de la font de llum restringida (x,y,z).
	GLfloat spotcoscutoff;		// Coseno de l'angle d'obertura de la font de llum restringida.
	GLfloat spotexponent;		// Exponent que indica l'atenuaci� de la font del centre de l'eix a l'exterior, segons model de Warn.
};

#endif