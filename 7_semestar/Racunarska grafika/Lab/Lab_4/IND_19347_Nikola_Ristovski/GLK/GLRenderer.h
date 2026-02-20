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
	void DestroyScene(CDC* pDC);		// dealocira resurse alocirane u drugim funkcijama ove klase,

	// Moje f-je

	void DrawAxis(double w);
	void DrawGrid(double width, double height, int nSegW, int nSegH);
	void DrawSphere(double r, int nSegAlpha, int nSegBeta);
	void DrawCylinder(double h, double r1, double r2, int nSeg);
	void DrawCone(double h, double r, int nSeg);
	void DrawFigure(double angle);

protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 
public:
	double m_angleX;
	double m_angleY;
	double m_radius;
	CPoint m_lastMousePos;
	bool m_mouseDown;
	double alpha;

};
