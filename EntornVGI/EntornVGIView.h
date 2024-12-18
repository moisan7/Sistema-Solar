//******** PRACTICA VISUALITZACI� GR�FICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn b�sic VS2022 MULTIFINESTRA amb OpenGL 4.3, interf�cie MFC i llibreries GLM
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� G�dia (Setembre 2024)
// EntornVGIView.h : interface of the CEntornVGI class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "MainFrm.h"

// Entorn VGI: Constants de l'aplicaci� entorn VGI
#include "constants.h"

// Entorn VGI: Includes shaders GLSL
#include <gl/glew.h>
#include <gl/wglew.h>

// Include all GLM core / GLSL features
#include <glm/glm.hpp>		// perspective, translate, rotate
// Include all GLM extensions
#include <glm/ext.hpp>

#include "shader.h"

// Entorn VGI: OBJECTE OBJ. Include per la definici� de l'objecte Obj_OBJ
#include "objLoader.h"	

class CEntornVGIView : public CView
{
protected: // Crear s�lo a partir de serializaci�n
	CEntornVGIView();
	DECLARE_DYNCREATE(CEntornVGIView)

// Atributos
public:
	CEntornVGIDoc* GetDocument() const;

//-------------- Entorn VGI: Variables globals de CPractivaView
	HGLRC	 m_hrc;		// OpenGL Rendering Context 

// Entorn V3D: Variables de control per Men� C�mera: Esf�rica, Navega, M�bil, Zoom, Satelit, Polars... 
	char camera;	// Variable que controla el tipus de c�mera segons valors definits en constants.h
	bool mobil;		// Opci� canvi de Punt de Vista interactiu (mobil) [0:NO,1:SI]
	bool zzoom;		// Opci� Zoom interactiu (zoom) [0:NO,1:SI]
	bool zzoomO;	// Opci� Zoom en Projecci� Ortogr�fica adaptant Volum Visualitzaci� [0:NO,1:SI]
	bool satelit;	// Opci� de navegaci� animada al volt de l'objecte centrat definint increment per mouse (SAT�LIT)

// Entorn VGI: Variables de control de l'opci� C�mera->Navega?
	GLdouble n[3];			// Punt cap on mira.
	CPunt3D opvN;			// Definici� Or�gen Punt de Vista (en coordenades m�n)
	double angleZ;			// angle de rotaci� de la traject�ria.
	glm::mat4 ViewMatrix;	// Matriu de C�mera a passar al shader

// Entorn VGI: Variables de control de l'opci� C�mera->Geode?
	CEsfe3D OPV_G;			// Par�metres camera en coord. esf�riques (R,alfa,beta) per a Vista Geode

// Entorn VGI: Variables de control per Men� Vista: fullsecreen, pan, dibuixar eixos i grid. 
	bool fullscreen;	// Opci� booleana per Pantalla Completal [0:NO,1:SI]
	bool pan;			// Opcio Pan. Despla�ament del centre de l'esfera de Vista [0:NO,1:SI]
	bool eixos;			// Opci� per dibuixar els eixos X,Y,Z (Eixos?) [0:NO,1:SI]
	Shader shaderEixos;	// Ientificador pel shader d'eixos.
	GLuint eixos_programID;
	GLuint eixos_Id;	// Identificador del VBO per a dibuixar els eixos.
	bool sw_grid;		// Opci� per activar comandes teclat per moure grids [TRUE] o no [FALSE]
	CMask3D grid;		// Opci� per a dibuixar grids (.x: grid XY, .y:grid XZ, .z: grid YZ, .w:grid XYZ)
	CPunt3D hgrid;		// Al�ada de cada grid (.x: grid XY, .y:grid XZ, .z: grid YZ, .w:grid XYZ)

// Entorn VGI: Variables de l'opci� Vista->Pan
	double fact_pan;	// Factor de despla�ament de la c�mara (opci� pan).
	CPunt3D tr_cpv;		// Vector de Traslaci� del Centre del Punt de Vista actiu dins opci� pan.
	CPunt3D tr_cpvF;	// Vector de Traslaci� del Centre del Punt de Vista (fixat amb INSERT dins opci� pan) 
						//       i actiu fora l'opci� pan.

// Entorn VGI: Variables de control per les opcions de men� Projecci�, Objecte
	char projeccio;	// Men� Projecci�: Tipus de projeccio
	glm::mat4 ProjectionMatrix;// Matriu de Projecci� a passar al shader
	char objecte;	// Men� Objecte: Tipus d'Objecte

// Entorn VGI: Variables de control Skybox Cube
	bool SkyBoxCube;			// Booleana que controla si es visualitza Skybox [TRUE] o no [FALSE].
	Shader shader_SkyBoxC;		// Shader Skybox Cub
	GLuint skC_programID;		// Identificador program Skybox Cube
	CVAO skC_VAOID;				// Identificador VAO List (vaoId, vboId, nVertexs) per a Skybox Cube
	GLuint cubemapTexture;		// Identificador textura cubemap.
	Shader shaderSkyBox;		// Shader SkyBox

// Entorn VGI: Variables de control del men� Transforma
	bool transf;	// Booleana per activar Transformacions (true) o no (false).
	bool trasl;		// Booleana d'activaci� de la Traslaci� (true) o no (false).
	bool rota;		// Booleana d'activaci� de la Rotaci� (true) o no (false).
	bool escal;		// Booleana d'activaci� de l'Escalatge (true) o no (false).
	double fact_Tras, fact_Rota;	// Increments de Traslaci� i Rotaci�.
	INSTANCIA TG;	// Estructura que cont� TG del men� Transforma actiu dins qualsevol opci� de Transforma 
					//      (Traslaci� Rotaci� i Escalatge).
	INSTANCIA TGF;	// Estructura que cont� TG del men� Transforma fixat amb INSERT dins les opcions de Transforma
					//     i actiu fora l'opci� Transforma.
	bool transX;	// Opci� Mobil Eix X?: TG interactives per l'eix X via mouse [F:NO,T:SI].
	bool transY;	// Opci� Mobil Eix Y?: TG interactives per l'eix Y via mouse [F:NO,T:SI].
	bool transZ;	// Opci� Mobil Eix Z?: TG interactives per l'eix Z via mouse [F:NO,T:SI].
	glm::mat4 GTMatrix; // Matriu de Transformacions Geom�triques a passar al shader

// Entorn VGI: Variables de control per les opcions de men� Ocultacions
	bool front_faces;// Men� ocultacions: Determina si les cares visibles s�n les frontals [true-defecte] o les back [false] pel Test de Visibilitat.
	bool test_vis;  // Men� ocultacions: Activa [true] o desactiva [false] Test Visibilitat.
	bool oculta;    // Men� ocultacions: Activa [true] o desactiva [false] Ocultacions (Z-buffer).

// Entorn VGI: Variables de control del men� Iluminaci�	
	bool ifixe;         // Iluminaci� fixe independent del PV (ifixe=1) 
						// o depenent (mobil) respecte el PV (casc miner) (ifixe=0)
	bool ilum2sides;	// Iluminaci� de les cares FRONT i BACK [TRUE] o nom�s les FRONT [FALSE]
	char ilumina;		// Tipus d'il.luminaci� [PUNTS 'P',FILFERROS 'w', PLANA 'f',GOURAUD 'g', PHONG 'p']
	bool sw_material[5];// Variable que controla els coeficients de reflectivitat del material [TRUE] o no [FALSE]:
						// [0]: emission, [1]: ambient, [2]: difusa, [3] especular.
	bool sw_material_old[5]; // Variable que guarda els valors de sw_material mentre no hi ha reflectivitat de material (refl_material=false).
	bool textura;       // Control de textures desactivades [0:NO] o activades [1:SI]
	char t_textura;		// Tipus de textures (predefinides o per fitxer)
	bool textura_map;	// Mapping de textura modulat amb la llum [TRUE] o calcat [FALSE]
	GLuint texturesID[NUM_MAX_TEXTURES];// Vector d'identificadors de textura de l'entorn. Si no hi ha textura activa, agafa el valor -1.
										// 0: Textura general, assignada a la lectura de fitxer.
										// 1-6: Textures assignables
										// 7: Textura pel Fractal
										// 8-9: Lliures
	bool tFlag_invert_Y; // Booleana que activa la inversi� coordenada textura t (o Y) a 1.0-cty segons llibreria SOIL (TRUE) o no (FALSE).

// Entorn VGI: Variables de control del men� Llums
	bool llum_ambient;		// Booleana que controla la llum ambient (SI/NO).
	LLUM llumGL[NUM_MAX_LLUMS];		// Vector de llums d'OpenGL
	bool sw_llambient;		// Booleana que controla modus de configurar el color de la llum ambient [TRUE] o no [FALSE]
	CColor col_llambient;	// Color llum ambient.

// Entorn VGI: Variables de control del men� Shaders
	char shader;				// Tipus de shader [FLAT, GOURAUD, PHONG, FILE, PROG_BINARY_SHADER]
	GLuint shader_programID;	// Shader Program que cont� el Vertex i Fragment program.
	Shader shaderLighting;		// Shader que implementa els codis GLSL d'il.luminaci�
	
// Entorn VGI: Variables butons de mouse 
	CPoint m_PosEAvall, m_PosDAvall; // Coordenades del cursor quan el boto esquerre(E) o dret(D) del 
									 //    mouse ha estat clicat.
	bool m_ButoEAvall, m_ButoDAvall; //TRUE si el boto esquerre(E) o dret(D) del mouse esta clicat.
	CEsfe3D m_EsfeEAvall;			 // Coordenades Esf�riques del PV (OPV) quan el boto esquerre(E) o dret(D) del 
	//										mouse ha estat clicat.
	CEsfe3D m_EsfeIncEAvall;		 // Increment de despla�ament en coordenades Esf�riques del PV (OPV).

// Entorn VGI: Variables que controlen par�metres visualitzaci�: Mides finestra Windows i PV
	int w, h;				// Mides de la finestra Windows (w-amplada,h-al�ada)
	int w_old, h_old;		// Mides de la finestra Windows (w-amplada,h-al�ada) per restaurar Finestra des de fullscreen
	CEsfe3D OPV;			// Par�metres camera en coord. esf�riques (R,alfa,beta)
	char Vis_Polar;			// Variable que controla orientaci� dels eixos en Visualitzaci� Interactiva (POLARZ,POLARY,POLARX)

// Entorn VGI: Color de fons i de l'objecte
	bool fonsR, fonsG, fonsB;	// Booleanes per controlar variaci� de color per teclat.
	CColor c_fons;			// Intensitat de color de fons.
	bool sw_color;			// Booleana que controla el modus de configurar color de l'objecte per teclat [TRUE] o no [FALSE]
	CColor col_obj;			// Color de l'objecte simple.

// Entorn VGI: Objecte OBJ:
	COBJModel* ObOBJ;		// Variable d'objecte format OBJ (*.OBJ)
	CVAO vao_OBJ;			// Identificador VAO per a objecte OBJ

// Entorn VGI: OBJECTE --> Corbes Bezier i BSpline
	int npts_T;							// N�mero de punts de control de la corba en el Vector corbaSpline (<=MAX_PATH_SPLINE)
	CPunt3D PC_t[MAX_PATCH_CORBA];		// Vector que enmagatzema Punts de Control Corba Spline
	GLdouble pas_Corba;					// Increment del par�metre t per al dibuix de les corbes.
	GLdouble pas_CS;						// Increment del par�metre t per al dibuix de corbes i superficies.
	bool sw_Punts_Control;				// Booleana que activa o desactiva la visualitzaci� dels punts de control de la corba o de la superficie

// Entorn VGI. TRIEDRE DE FRENET / DARBOUX: VT: vector Tangent, VNP: Vector Normal Principal, VBN: vector BiNormal
	bool dibuixa_TriedreFrenet;			// Booleana que controla dibuix de Triedre de Frenet per a cada punt de la Corba [TRUE-dibuixa, FALSE-no dibuixa]
	bool dibuixa_TriedreDarboux;		// Booleana que controla dibuix de Triedre de Darboux per a cada punt de la Corba Loxodroma[TRUE-dibuixa, FALSE-no dibuixa]
	CPunt3D VT, VNP, VBN;				// TRIEDRE de FRENET: VT: Vector Tangent, VNP: Vector Normal Principal, VBN: Vector BiNormal.

// Entorn VGI: Variables del Timer
	double t;		// Par�metre t pel Timer.
	bool anima;		// Booleana que controla si l'animaci� �s activa (TRUE) o no (FALSE)
					//    dins la funci� de control del rellotge OnTimer.
	bool rotation;
	bool translation;
	bool translation_orbit;
	bool sis_start;
	float orbit_angle[9];		// ANGULO TRASLACION
	float rotation_angle[10];	// ANGULO ROTACION
	float speed_inc, speed_index;

// Entorn VGI: Variables de l'objecte FRACTAL
	char t_fractal;		// Tipus de fractal.
	char soroll;		// Men� Fractals: Tipus de soroll
	int pas, pas_ini;	// Resoluci� del fractal inicial (pas_ini) i de visualitzaci� (pas).
	bool sw_il;			// Booleana que controla si cal compilar el fractal (sw_il=1) o no (sw_il=0)
	bool palcolFractal;	// Booleana que activa coloraci� del fractal segons paleta de colors [TRUE] o no [FALSE].

// Entorn VGI: Altres variables
	GLdouble mida;	// Factor d'escala per calcular Volum de Visualitzaci� de l'objecte que encaixi.
	CString nom;	// Nom de fitxer.
	CString buffer; // Buffer que magatzema string caracters corresponent a variables double a printar en Status Bar (funci� Barra_Estat).
	// SISTEMA SOLAR
	GLuint* texturesID_planets;
	bool load_textures;
	bool skyb;
	bool draw_planets[9];
	// Camera
	vec3 targetPos = glm::vec3(0.0f, 0.0f, 0.0f);
	int target_planet = 0; 
	// Moon
	float moon_rotation_angle;
	float moon_orbit_angle;
	float jupiter_moon_rot[3];
	float jupiter_moon_ort[3];
	float saturn_titan_rot;
	float saturn_titan_ort;
	float unanos_titania_rot;
	float unanos_titania_ort;
	float neptune_triton_rot;
	float neptune_triton_ort;
	// ====== Buttons GUI ============
	CButton m_btnStart;
	// Show/Hide
	bool showMenu;
	CButton m_btnShowMenu;
	CButton m_btnShowMercury;
	CButton m_btnShowVenus;
	CButton m_btnShowEarth;
	CButton m_btnShowMars;
	CButton m_btnShowJupiter;
	CButton m_btnShowSaturn;
	CButton m_btnShowUranus;
	CButton m_btnShowNeptune;
	CButton m_btnShowOrbits;
	// Camera
	bool cameraMenu;
	CButton m_btnCameraMenu;
	CButton m_btnCameraSun;
	CButton m_btnCameraMercury;
	CButton m_btnCameraVenus;
	CButton m_btnCameraEarth;
	CButton m_btnCameraMars;
	CButton m_btnCameraJupiter;
	CButton m_btnCameraSaturn;
	CButton m_btnCameraUranus;
	CButton m_btnCameraNeptune;
	// Slider Speeds
	bool speedMenu;
	CButton m_btnSpeedMenu;
	CSliderCtrl m_sliderSpeed;
	int m_speedIndex = 0;
	// Slider Scales
	bool scaleMenu;
	CButton m_btnScaleMenu;
	CSliderCtrl m_sliderScale;
	int m_scaleIndex = 4;
	// Timer display
	CTime m_currentDate;    // Current date and time for the timer display
	CString m_dateString;   // String to hold the formatted date
	CStatic m_timerLabel;   // Static text control to display the timer
	CString m_planetName;
	CStatic m_planetLabel;
//-------------- Entorn VGI: Fi De Variables globals de CEntornVGIView

// Operaciones
public:

// Reemplazos
public:
	virtual void OnDraw(CDC* pDC);  // Reemplazado para dibujar esta vista
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void UpdateSpeedFromSlider();
	void UpdateScaleFromSlider();
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Funcions de c�rrega i activaci� de shaders
	void InitAPI();
	void GetGLVersion(int* major, int* minor);
	void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
		const GLchar* message, const void* userParam);
	void OnInitialUpdate();

// Implementaci�n
public:
	virtual ~CEntornVGIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void CEntornVGIView::configura_Escena();
	void CEntornVGIView::dibuixa_Escena();
	void CEntornVGIView::Barra_Estat();
	void CEntornVGIView::double2CString(double varf);
	int CEntornVGIView::Log2(int num);							// Log2: C�lcul del log base 2 de num
	char * CEntornVGIView::CString2Char(CString entrada);		// Conversi� string CString --> char *
	void CEntornVGIView::Refl_MaterialOff();					// Desactivar Reflexi� de Material
	void CEntornVGIView::Refl_MaterialOn();						// Activar Reflexi� de Material
	int CEntornVGIView::llegir_ptsC(char *nomf);				// Lectura Punts de Control Corba (B-spline o Bezier)
	bool CEntornVGIView::llegir_FontLlum(char* nomf);			// Lectura Par�metres Font de Llum
	std::string CEntornVGIView::CString2String(const CString& cString); // Conversi� CString --> std::string

// Entorn VGI: Funcions de c�rrega i activaci� de shaders
	GLuint CEntornVGIView::initializeShaders(CString filename);
	GLuint CEntornVGIView::loadFileShaders(CString file_Vert, CString file_Frag);
	char *CEntornVGIView::textFileRead(char *fn);
	void CEntornVGIView::releaseAllShaders();

// // Entorn VGI: Funcions de tractament de teclat en diferents modus
	void CEntornVGIView::Teclat_ColorObjecte(UINT nChar, UINT nRepCnt);
	void CEntornVGIView::Teclat_ColorFons(UINT nChar, UINT nRepCnt);
	void CEntornVGIView::Teclat_Navega(UINT nChar, UINT nRepCnt);
	void CEntornVGIView::Teclat_Pan(UINT nChar, UINT nRepCnt);
	void CEntornVGIView::Teclat_TransEscala(UINT nChar, UINT nRepCnt);
	void CEntornVGIView::Teclat_TransRota(UINT nChar, UINT nRepCnt);
	void CEntornVGIView::Teclat_TransTraslada(UINT nChar, UINT nRepCnt);
	void CEntornVGIView::Teclat_Grid(UINT nChar, UINT nRepCnt);
	void CEntornVGIView::Teclat_PasCorbes(UINT nChar, UINT nRepCnt);

	CMFCStatusBar& GetStatusBar() const
	{
		return ((CMainFrame*)AfxGetMainWnd())->GetStatusBar();
	}

// Variables Full Screen
protected:
	CWnd *saveParent;
	CMenu *ContextMenu;

private:

//Rendering Context and Device Context Pointers
	HGLRC     m_hRC;
	CDC*      m_pDC;

// Funciones de asignaci�n de mensajes generadas
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnPaint();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnArxiuObrirFractal();
	afx_msg void OnArxiuObrirFitxerObj();
//	afx_msg void OnArxiuObrirFitxer3ds();
	afx_msg void OnVistaMobil();
	afx_msg void OnUpdateVistaMobil(CCmdUI *pCmdUI);
	afx_msg void OnVistaZoom();
	afx_msg void OnUpdateVistaZoom(CCmdUI *pCmdUI);
	afx_msg void OnVistaPolarsX();
	afx_msg void OnUpdateVistaPolarsX(CCmdUI *pCmdUI);
	afx_msg void OnVistaPolarsY();
	afx_msg void OnUpdateVistaPolarsY(CCmdUI *pCmdUI);
	afx_msg void OnVistaPolarsZ();
	afx_msg void OnUpdateVistaPolarsZ(CCmdUI *pCmdUI);
	afx_msg void OnVistaPan();
	afx_msg void OnUpdateVistaPan(CCmdUI *pCmdUI);
	afx_msg void OnVistaOrigenpan();
	afx_msg void OnVistaNavega();
	afx_msg void OnUpdateVistaNavega(CCmdUI *pCmdUI);
	afx_msg void OnVistaOrigennavega();
	afx_msg void OnVistaEixos();
	afx_msg void OnUpdateVistaEixos(CCmdUI *pCmdUI);
	afx_msg void OnProjeccioPerspectiva();
	afx_msg void OnUpdateProjeccioPerspectiva(CCmdUI *pCmdUI);
	afx_msg void OnObjecteCub();
	afx_msg void OnUpdateObjecteCub(CCmdUI *pCmdUI);
	afx_msg void OnObjecteEsfera();
	afx_msg void OnUpdateObjecteEsfera(CCmdUI *pCmdUI);
	afx_msg void OnObjecteTetera();
	afx_msg void OnUpdateObjecteTetera(CCmdUI *pCmdUI);
	afx_msg void OnTransformaTraslacio();
	afx_msg void OnUpdateTransformaTraslacio(CCmdUI *pCmdUI);
	afx_msg void OnTransformaOrigentraslacio();
	afx_msg void OnTransformaRotacio();
	afx_msg void OnUpdateTransformaRotacio(CCmdUI *pCmdUI);
	afx_msg void OnTransformaOrigenrotacio();
	afx_msg void OnTransformaEscalat();
	afx_msg void OnUpdateTransformaEscalat(CCmdUI *pCmdUI);
	afx_msg void OnTransformaOrigenescalat();
	afx_msg void OnTransformaMobilx();
	afx_msg void OnUpdateTransformaMobilx(CCmdUI *pCmdUI);
	afx_msg void OnTransformaMobily();
	afx_msg void OnUpdateTransformaMobily(CCmdUI *pCmdUI);
	afx_msg void OnTransformaMobilz();
	afx_msg void OnUpdateTransformaMobilz(CCmdUI *pCmdUI);
	afx_msg void OnOcultacionsTestvis();
	afx_msg void OnUpdateOcultacionsTestvis(CCmdUI *pCmdUI);
	afx_msg void OnOcultacionsZbuffer();
	afx_msg void OnUpdateOcultacionsZbuffer(CCmdUI *pCmdUI);
//	afx_msg void OnOcultacionsBackline();
//	afx_msg void OnUpdateOcultacionsBackline(CCmdUI *pCmdUI);
	afx_msg void OnIluminacioLlumfixe();
	afx_msg void OnUpdateIluminacioLlumfixe(CCmdUI *pCmdUI);
	afx_msg void OnIluminacioFilferros();
	afx_msg void OnUpdateIluminacioFilferros(CCmdUI *pCmdUI);
	afx_msg void OnIluminacioGouraud();
	afx_msg void OnUpdateIluminacioGouraud(CCmdUI *pCmdUI);
	afx_msg void OnMaterialEmissio();
	afx_msg void OnUpdateMaterialEmissio(CCmdUI *pCmdUI);
	afx_msg void OnMaterialAmbient();
	afx_msg void OnUpdateMaterialAmbient(CCmdUI *pCmdUI);
	afx_msg void OnMaterialDifusa();
	afx_msg void OnUpdateMaterialDifusa(CCmdUI *pCmdUI);
	afx_msg void OnMaterialEspecular();
	afx_msg void OnUpdateMaterialEspecular(CCmdUI *pCmdUI);
	afx_msg void OnIluminacioTextures();
	afx_msg void OnUpdateIluminacioTextures(CCmdUI *pCmdUI);
	afx_msg void OnIluminacioTexturaFitxerimatge();
	afx_msg void OnUpdateIluminacioTexturaFitxerimatge(CCmdUI *pCmdUI);
	afx_msg void OnLlumsLlumambient();
	afx_msg void OnUpdateLlumsLlumambient(CCmdUI *pCmdUI);
	afx_msg void OnLlumsLlum0();
	afx_msg void OnUpdateLlumsLlum0(CCmdUI *pCmdUI);
//	afx_msg void OnShadersSense();
//	afx_msg void OnUpdateShadersSense(CCmdUI *pCmdUI);
//	afx_msg void OnShadersGouraud();
//	afx_msg void OnUpdateShadersGouraud(CCmdUI *pCmdUI);
//	afx_msg void OnShadersPhong();
//	afx_msg void OnUpdateShadersPhong(CCmdUI *pCmdUI);
	afx_msg void OnVistaSatelit();
	afx_msg void OnUpdateVistaSatelit(CCmdUI *pCmdUI);
	afx_msg void OnVistaFullscreen();
	afx_msg void OnUpdateVistaFullscreen(CCmdUI *pCmdUI);
//	afx_msg void OnObjecteCubRGB();
//	afx_msg void OnUpdateObjecteCubRGB(CCmdUI *pCmdUI);
	afx_msg void OnObjecteTie();
	afx_msg void OnUpdateObjecteTie(CCmdUI *pCmdUI);
	afx_msg void OnIluminacioPunts();
	afx_msg void OnUpdateIluminacioPunts(CCmdUI *pCmdUI);
	afx_msg void OnShaderLoadFiles();
	afx_msg void OnUpdateShaderLoadFiles(CCmdUI *pCmdUI);
	afx_msg void OnOcultacionsFrontFaces();
	afx_msg void OnUpdateOcultacionsFrontFaces(CCmdUI *pCmdUI);
	afx_msg void OnLlumsLlum1();
	afx_msg void OnUpdateLlumsLlum1(CCmdUI *pCmdUI);
	afx_msg void OnLlumsLlum2();
	afx_msg void OnUpdateLlumsLlum2(CCmdUI *pCmdUI);
	afx_msg void OnLlumsLlum3();
	afx_msg void OnUpdateLlumsLlum3(CCmdUI *pCmdUI);
	afx_msg void OnLlumsLlum4();
	afx_msg void OnUpdateLlumsLlum4(CCmdUI *pCmdUI);
	afx_msg void OnObjeteCorbaBezier();
	afx_msg void OnUpdateObjeteCorbaBezier(CCmdUI *pCmdUI);
	afx_msg void OnObjecteCorbaLemniscata();
	afx_msg void OnUpdateObjecteCorbaLemniscata(CCmdUI *pCmdUI);
	afx_msg void OnObjecteCorbaBSpline();
	afx_msg void OnUpdateObjecteCorbaBSpline(CCmdUI *pCmdUI);
	afx_msg void OnObjectePuntsControl();
	afx_msg void OnUpdateObjectePuntsControl(CCmdUI *pCmdUI);
	afx_msg void OnIluminacio2Sides();
	afx_msg void OnUpdateIluminacio2Sides(CCmdUI *pCmdUI);
	afx_msg void OnObjecteMatriuPrimitives();
	afx_msg void OnUpdateObjecteMatriuPrimitives(CCmdUI* pCmdUI);
	afx_msg void OnObjecteMatriuPrimitivesVBO();
	afx_msg void OnUpdateObjecteMatriuPrimitivesVBO(CCmdUI* pCmdUI);
	afx_msg void OnVistaSkyBox();
	afx_msg void OnUpdateVistaSkyBox(CCmdUI* pCmdUI);
	afx_msg void OnIluminacioPhong();
	afx_msg void OnUpdateIluminacioPhong(CCmdUI* pCmdUI);
	afx_msg void OnObjecteArc();
	afx_msg void OnUpdateObjecteArc(CCmdUI* pCmdUI);
	afx_msg void OnCameraEsferica();
	afx_msg void OnUpdateCameraEsferica(CCmdUI* pCmdUI);
	afx_msg void OnVistaZoomOrto();
	afx_msg void OnUpdateVistaZoomOrto(CCmdUI* pCmdUI);
	afx_msg void OnCameraGeode();
	afx_msg void OnUpdateCameraGeode(CCmdUI* pCmdUI);
	afx_msg void OnCameraOrigenGeode();
	afx_msg void OnCorbesTriedreFrenet();
	afx_msg void OnUpdateCorbesTriedreFrenet(CCmdUI* pCmdUI);
	afx_msg void OnObjecteCubRGB();
	afx_msg void OnUpdateObjecteCubRGB(CCmdUI* pCmdUI);
	afx_msg void OnIluminacioTexturaFlagInvertY();
	afx_msg void OnUpdateIluminacioTexturaFlagInvertY(CCmdUI* pCmdUI);
	afx_msg void OnMaterialReflmaterial();
	afx_msg void OnUpdateMaterialReflMaterial(CCmdUI* pCmdUI);
	afx_msg void OnArxiuObrirFitxerFontLlum();
	afx_msg void OnObjecteCap();
	afx_msg void OnUpdateObjecteCap(CCmdUI* pCmdUI);
	afx_msg void OnArxiuObrirSkybox();
	afx_msg void OnShaderPBinaryWrite();
	afx_msg void OnShaderPBinaryRead();
	afx_msg void OnUpdateShaderPBinaryRead(CCmdUI* pCmdUI);
	afx_msg void OnShadersFlat();
	afx_msg void OnUpdateShadersFlat(CCmdUI* pCmdUI);
	afx_msg void OnIluminacioSuau();
	afx_msg void OnUpdateIluminacioSuau(CCmdUI* pCmdUI);
	afx_msg void OnIluminacioPlana();
	afx_msg void OnUpdateIluminacioPlana(CCmdUI* pCmdUI);
	afx_msg void OnObjecteCorbaHermitte();
	afx_msg void OnUpdateObjecteCorbaHermitte(CCmdUI* pCmdUI);
	afx_msg void OnObjecteCorbaCatmullRom();
	afx_msg void OnUpdateObjecteCorbaCatmullRom(CCmdUI* pCmdUI);
	// A�ADIDO PARA EL SISTEMA SOLAR:
	afx_msg void OnSistemasolarStart();
	afx_msg void OnUpdateSistemasolarStart(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarTestRotacio();
	afx_msg void OnUpdateSistemasolarTestRotacio(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarTestTranslacio();
	afx_msg void OnUpdateSistemasolarTestTranslacio(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarTestTextures();
	afx_msg void OnUpdateSistemasolarTestTextures(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarTestOrbita();
	afx_msg void OnUpdateSistemasolarTestOrbita(CCmdUI* pCmdUI);
	// Increment Speed
	afx_msg void OnSistemasolarIncrementx0();
	afx_msg void OnUpdateSistemasolarIncrementx0(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarIncrementx1();
	afx_msg void OnUpdateSistemasolarIncrementx1(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarIncrementx2();
	afx_msg void OnUpdateSistemasolarIncrementx2(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarIncrementx5();
	afx_msg void OnUpdateSistemasolarIncrementx5(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarIncrementx10();
	afx_msg void OnUpdateSistemasolarIncrementx10(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarIncrementx100();
	afx_msg void OnUpdateSistemasolarIncrementx100(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarIncrementx200();
	afx_msg void OnUpdateSistemasolarIncrementx200(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarIncrementx500();
	afx_msg void OnUpdateSistemasolarIncrementx500(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarIncrementx1000();
	afx_msg void OnUpdateSistemasolarIncrementx1000(CCmdUI* pCmdUI);
	// Show Planets
	afx_msg void OnSistemasolarShowMercury();
	afx_msg void OnUpdateSistemasolarShowMercury(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarShowVenus();
	afx_msg void OnUpdateSistemasolarShowVenus(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarShowEarth();
	afx_msg void OnUpdateSistemasolarShowEarth(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarShowMars();
	afx_msg void OnUpdateSistemasolarShowMars(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarShowJupiter();
	afx_msg void OnUpdateSistemasolarShowJupiter(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarShowSaturn();
	afx_msg void OnUpdateSistemasolarShowSaturn(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarShowUranus();
	afx_msg void OnUpdateSistemasolarShowUranus(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarShowNeptune();
	afx_msg void OnUpdateSistemasolarShowNeptune(CCmdUI* pCmdUI);
	afx_msg void OnSistemasolarShowOrbits();
	afx_msg void OnUpdateSistemasolarShowOrbits(CCmdUI* pCmdUI);
	// Camera Lock
	afx_msg void OnLockonplanetSun();
	afx_msg void OnLockonplanetMercury();
	afx_msg void OnLockonplanetVenus();
	afx_msg void OnLockonplanetEarth();
	afx_msg void OnLockonplanetMars();
	afx_msg void OnLockonplanetJupiter();
	afx_msg void OnLockonplanetSaturn();
	afx_msg void OnLockonplanetUranus();
	afx_msg void OnLockonplanetNeptune();
	afx_msg void OnUpdateLockonplanetSun(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLockonplanetMercury(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLockonplanetVenus(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLockonplanetEarth(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLockonplanetMars(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLockonplanetJupiter(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLockonplanetSaturn(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLockonplanetUranus(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLockonplanetNeptune(CCmdUI* pCmdUI);
	// ====== Buttons GUI ============
	afx_msg void OnBtnStartClicked();
	// Show / Hide
	afx_msg void OnBtnShowMenu();
	afx_msg void OnBtnShowMercury();
	afx_msg void OnBtnShowVenus();
	afx_msg void OnBtnShowEarth();
	afx_msg void OnBtnShowMars();
	afx_msg void OnBtnShowJupiter();
	afx_msg void OnBtnShowSaturn();
	afx_msg void OnBtnShowUranus();
	afx_msg void OnBtnShowNeptune();
	afx_msg void OnBtnShowOrbits();
	// Camera
	afx_msg void OnBtnCameraMenu();
	afx_msg void OnBtnCameraSun();
	afx_msg void OnBtnCameraMercury();
	afx_msg void OnBtnCameraVenus();
	afx_msg void OnBtnCameraEarth();
	afx_msg void OnBtnCameraMars();
	afx_msg void OnBtnCameraJupiter();
	afx_msg void OnBtnCameraSaturn();
	afx_msg void OnBtnCameraUranus();
	afx_msg void OnBtnCameraNeptune();
	// Slider Speeds
	afx_msg void OnBtnSpeedMenu();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// Slider Scales
	afx_msg void OnBtnScaleMenu();
	afx_msg void OnHScrollScale(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// Fullscreen
	afx_msg LRESULT OnForceFullscreen(WPARAM wParam, LPARAM lParam);
	// Timer
	void UpdateTimerDisplay();
	// FIN A�ADIDO PARA EL SISTEMA SOLAR
	
};

#ifndef _DEBUG  // Versi�n de depuraci�n en EntornVGIView.cpp
inline CEntornVGIDoc* CEntornVGIView::GetDocument() const
   { return reinterpret_cast<CEntornVGIDoc*>(m_pDocument); }
#endif

