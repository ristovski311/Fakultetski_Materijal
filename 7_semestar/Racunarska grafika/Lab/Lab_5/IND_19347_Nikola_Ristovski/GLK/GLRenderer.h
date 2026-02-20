#pragma once

class CGLRenderer
{
public:
	CGLRenderer(void);
	virtual ~CGLRenderer(void);
		
	bool CreateGLContext(CDC* pDC);			// kreira OpenGL Rendering Context
	void PrepareScene(CDC* pDC);			// inicijalizuje scenu,
	void Reshape(CDC* pDC, int w, int h);	// kod koji treba da se izvrsi svaki put kada se promeni velicina prozora ili pogleda i
	void DrawScene(CDC* pDC);				// iscrtava scenu
	void DestroyScene(CDC* pDC);			// dealocira resurse alocirane u drugim funkcijama ove klase,

	//Moje fje:
	void DrawAxis(int w);
	void DrawCube(double a, double b, double h, int segA, int segB, int segH);
	void DrawSphere(double r, int nSegAlpha, int nSegBeta, bool isHalfSphere);
	void DrawCylinder(double h, double r1, double r2, int nSeg);
	void DrawCone(double h, double r, int nSeg);
	void DrawConeRing(double h, double r1, double r2, int nSeg, float R, float G, float B);
	void DrawFigure();

protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 
public:
	bool redLightOn;
	bool blueLightOn;
	bool greenLightOn;
	bool showNormals;

	double cameraAngleX;
	double cameraAngleY;
	double cameraRadius;
	CPoint lastMousePos;
	bool isMouseDown;
};
