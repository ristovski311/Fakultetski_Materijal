#pragma once
#include "DImage.h"

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

	//Moje metode:

	void DrawAxis(double width);
	void DrawSphere(double radius, int alphaSeg, int betaSeg, bool isHalfSphere);
	void DrawEllipsoid();
	void DrawGround();
	void DrawCylinder(double r,double height, int seg);
	void DrawWheel();
	void DrawTruckBody();
	void DrawFigure();
	UINT LoadTexture(DImage* img, bool isSClamp, bool isTClamp);

protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context
public:
	//Atributi:
	double angleCameraX;
	double angleCameraY;
	double radiusCamera;
	CPoint lastMousePos;
	bool isMouseDown;
	DImage* grassTexture;
	DImage* figureTexture;
	bool enableLight;

	UINT grassTextureID;
	UINT figureTextureID;

	double wheelRotationAngle;
	double wheelSteerAngle;

	double offsetX;
	double offsetZ;
	double truckRotationAngle;
};
