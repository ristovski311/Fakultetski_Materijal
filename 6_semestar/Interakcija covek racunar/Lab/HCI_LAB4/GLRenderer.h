#pragma once

class CGLRenderer
{
public:
	CGLRenderer(void);
	virtual ~CGLRenderer(void);
		
	float m_y = 0.0f;
	float m_z = 0.0f;
	float m_x = 0.0f;

	float m_Ry = 0.0f;
	float m_Rx = 0.0f;

	bool CreateGLContext(CDC* pDC);			// kreira OpenGL Rendering Context
	void PrepareScene(CDC* pDC);			// inicijalizuje scenu,
	void Reshape(CDC* pDC, int w, int h);	// kod koji treba da se izvrsi svaki put kada se promeni velicina prozora ili pogleda i
	void DrawScene(CDC* pDC);				// iscrtava scenu
	void DestroyScene(CDC* pDC);			// dealocira resurse alocirane u drugim funkcijama ove klase,
	void DrawScene();

	void ProcessHits(int hits, unsigned int buffer[], unsigned int* ids);
	void PickObject(CDC *pDC, int x, int y, unsigned int* ids);
protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 
	float	m_aspect;

};
