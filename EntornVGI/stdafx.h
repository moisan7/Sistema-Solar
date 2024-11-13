// stdafx.h: archivo de inclusi�n para archivos de inclusi�n est�ndar del sistema,
// o archivos de inclusi�n espec�ficos del proyecto utilizados frecuentemente,
// pero cambiados rara vez

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Excluir material rara vez utilizado de encabezados de Windows
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // Algunos constructores CString ser�n expl�citos

// Desactiva la ocultaci�n de MFC para algunos mensajes de advertencia comunes y, muchas veces, omitidos de forma consciente
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // Componentes principales y est�ndar de MFC
#include <afxext.h>         // Extensiones de MFC

#include <afxdisp.h>        // Clases de automatizaci�n de MFC

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Compatibilidad MFC para controles comunes de Internet Explorer 4
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Compatibilidad MFC para controles comunes de Windows
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // Compatibilidad de MFC con cintas y barras de control

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

/* ------------------------------------------------------------------------- */
/*                                INCLUDES                                   */
/* ------------------------------------------------------------------------- */

// VGI: Includes llibreria GLEW 2.1.0
#define GLEW_STATIC
#define GLEW_NO_GLU	// Sense usar llibreria GLU
#include <gl/glew.h>
#include <gl/wglew.h>

// Include all GLM core / GLSL features
#include <glm/glm.hpp>		// perspective, translate, rotate
// Include all GLM extensions
#include <glm/ext.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
//#include <glm/gtx/norm.hpp>
using namespace glm;

// VGI: Llibreries OpenGL
//#include <gl/gl.h>
//#include <gl/glaux.h>
//#include <gl/glu.h>
//#include <gl/glut.h>
#include "glut_geometry.h"			// Fonts dels Objectes de la llibreria freeglut

// VGI: Llibreria SOIL2 (actualitzaci� de SOIL) per a llegir imatges de diferents formats 
//     (BMP,JPG,TIF,GIF,etc.) en la funci� loadIMA (visualitzacio.cpp)
#include <gl/SOIL2.h>

// VGI: Includes per lectura fitxers, funcions trigonom�triques i nombres aleatoris.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <string>

// VGI: Constants de l'aplicaci� Practica
#include "constants.h"

//Llibreria irrKlang per audio
#include "irrKlang/irrKlang.h"

using namespace irrklang;

// Desactivar en llistat compilaci� warning C4244: 'argumento': conversi�n de 'double' a 'GLfloat'; posible p�rdida de datos
#  pragma warning (disable:4244)  // Disable bogus VC++ 4.2 conversion warnings.
#  pragma warning (disable:4305)  // VC++ 5.0 version of above warning.
#  pragma warning (disable:4473)  // Disable strpcpy deprecated command in objLoader.cpp
#  pragma warning (disable:4099)  // Warning 'no se encontro vc120.pdb
#  pragma warning (disable:4996)  // Disable strpcpy deprecated command in objLoader.cpp