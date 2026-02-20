#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#pragma comment(lib, "GL\\glut32.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")

#define TORAD 3.14159/180

CGLRenderer::CGLRenderer(void)
{
	m_angleX = 45*TORAD;
	m_angleY = 0;
	m_radius = 200;
	alpha = 0;

	m_mouseDown = false;
}

//Broj za lab: 13147

CGLRenderer::~CGLRenderer(void)
{
}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd ;
   	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
   	pfd.nSize  = sizeof(PIXELFORMATDESCRIPTOR);
   	pfd.nVersion   = 1; 
   	pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;   
   	pfd.iPixelType = PFD_TYPE_RGBA; 
   	pfd.cColorBits = 32;
   	pfd.cDepthBits = 24; 
   	pfd.iLayerType = PFD_MAIN_PLANE;
	
	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);
	
	if (nPixelFormat == 0) return false; 

	BOOL bResult = SetPixelFormat (pDC->m_hDC, nPixelFormat, &pfd);
  	
	if (!bResult) return false; 

   	m_hrc = wglCreateContext(pDC->m_hDC); 

	if (!m_hrc) return false; 

	return true;	
}

void CGLRenderer::PrepareScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClearColor(0.5, 0.75, 1.0, 0.0);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawAxis(double width) {

	glLineWidth(1.0);
	glPointSize(1.0);
	
	glBegin(GL_LINES);
	
	glColor3f(1, 0, 0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(width, 0.0, 0.0);

	glColor3f(0, 1, 0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, width, 0.0);

	glColor3f(0, 0, 1);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, width);

	glEnd();
}

void CGLRenderer::DrawSphere(double r, int nSegAlpha, int nSegBeta) {
	double betaStep = 360 / nSegBeta;
	double alphaStep = 360 / nSegAlpha;

	double startAlpha = 90;
	double endAlpha = 270;

	double startBeta = 0;
	double endBeta = 360;

	/*glBegin(GL_TRIANGLES);

	for (double alpha = startAlpha; alpha < endAlpha; alpha += alphaStep)
	{
		for (double beta = startBeta; beta < endBeta; beta += betaStep)
		{
			double p_b1_a1_x = r * cos(alpha * TORAD) * cos(beta * TORAD);
			double p_b1_a1_y = r * sin(alpha * TORAD);
			double p_b1_a1_z = r * cos(alpha * TORAD) * sin(beta * TORAD);

			double p_b2_a1_x = r * cos(alpha * TORAD) * cos((beta + betaStep)*TORAD);
			double p_b2_a1_y = r * sin(alpha * TORAD);
			double p_b2_a1_z = r * cos(alpha * TORAD) * sin((beta + betaStep)*TORAD);

			double p_b2_a2_x = r * cos((alpha + alphaStep) * TORAD) * cos((beta + betaStep)*TORAD);
			double p_b2_a2_y = r * sin((alpha + alphaStep)*TORAD);
			double p_b2_a2_z = r * cos((alpha + alphaStep) * TORAD) * sin((beta + betaStep)*TORAD);

			double p_b1_a2_x = r * cos((alpha + alphaStep)*TORAD) * cos(beta*TORAD);
			double p_b1_a2_y = r * sin((alpha + alphaStep)*TORAD);
			double p_b1_a2_z = r * cos((alpha + alphaStep)*TORAD) * sin(beta*TORAD);

			glVertex3d(p_b1_a1_x, p_b1_a1_y, p_b1_a1_z);
			glVertex3d(p_b2_a1_x, p_b2_a1_y, p_b2_a1_z);
			glVertex3d(p_b2_a2_x, p_b2_a2_y, p_b2_a2_z);

			glVertex3d(p_b2_a2_x, p_b2_a2_y, p_b2_a2_z);
			glVertex3d(p_b1_a2_x, p_b1_a2_y, p_b1_a2_z);
			glVertex3d(p_b1_a1_x, p_b1_a1_y, p_b1_a1_z);
		}
	}
	*/

	glBegin(GL_QUAD_STRIP);

	for (double alpha = startAlpha; alpha <= endAlpha; alpha += alphaStep)
	{
		for (double beta = startBeta; beta <= endBeta; beta += betaStep)
		{
			double p_b1_a1_x = r * cos(alpha * TORAD) * cos(beta * TORAD);
			double p_b1_a1_y = r * sin(alpha * TORAD);
			double p_b1_a1_z = r * cos(alpha * TORAD) * sin(beta * TORAD);

			double p_b1_a2_x = r * cos((alpha + alphaStep) * TORAD) * cos(beta * TORAD);
			double p_b1_a2_y = r * sin((alpha + alphaStep) * TORAD);
			double p_b1_a2_z = r * cos((alpha + alphaStep) * TORAD) * sin(beta * TORAD);
			
			glVertex3d(p_b1_a1_x, p_b1_a1_y, p_b1_a1_z);
			glVertex3d(p_b1_a2_x, p_b1_a2_y, p_b1_a2_z);
		}
	}

	glEnd();
}

void CGLRenderer::DrawCone(double h, double r, int nSeg) {

	double angleStep = 360 / nSeg;

	/*glBegin(GL_TRIANGLES);

	for (int angle = 0; angle < 360; angle += angleStep) {
		
		double p_an1_x = r * cos(angle * TORAD);
		double p_an1_z = r * sin(angle * TORAD);

		double p_an2_x = r * cos((angle + angleStep)*TORAD);
		double p_an2_z = r * sin((angle + angleStep)*TORAD);

		//Osnovica trougao

		glVertex3d(p_an1_x, 0, p_an1_z);
		glVertex3d(0, 0, 0);
		glVertex3d(p_an2_x, 0, p_an2_z);

		//Stranica trougao

		glVertex3d(p_an1_x, 0, p_an1_z);
		glVertex3d(p_an2_x, 0, p_an2_z);
		glVertex3d(0, h, 0); 
	}*/

	glBegin(GL_TRIANGLE_FAN);

	//Osnovica
	glVertex3d(0, 0, 0);
	for (int angle = 0; angle <= 360; angle += angleStep) {

		double p_x = r * cos(angle * TORAD);
		double p_z = r * sin(angle * TORAD);

		glVertex3d(p_x, 0, p_z);
	}
	
	glEnd();
	glBegin(GL_TRIANGLE_FAN);

	//Omotac
	glVertex3d(0, h, 0);
	for (int angle = 0; angle <= 360; angle += angleStep) {

		double p_x = r * cos(angle * TORAD);
		double p_z = r * sin(angle * TORAD);

		glVertex3d(p_x, 0, p_z);
	}

	glEnd();
}

void CGLRenderer::DrawCylinder(double h, double r1, double r2, int nSeg) {
	double angleStep = 360 / nSeg;

	/*glBegin(GL_TRIANGLES);

	for (int angle = 0; angle < 360; angle += angleStep) {
		
		double p_bottom_an1_x = r1 * cos(angle * TORAD);
		double p_bottom_an1_z = r1 * sin(angle * TORAD);
		double p_bottom_an2_x = r1 * cos((angle + angleStep)*TORAD);
		double p_bottom_an2_z = r1 * sin((angle + angleStep)*TORAD);

		double p_top_an1_x = r2 * cos(angle * TORAD);
		double p_top_an1_z = r2 * sin(angle * TORAD);
		double p_top_an2_x = r2 * cos((angle + angleStep) * TORAD);
		double p_top_an2_z = r2 * sin((angle + angleStep) * TORAD);

		//Osnovica donja trougao

		glVertex3d(p_bottom_an1_x, 0, p_bottom_an1_z);
		glVertex3d(0, 0, 0);
		glVertex3d(p_bottom_an2_x, 0, p_bottom_an2_z);

		//Osnovica gornja trougao

		glVertex3d(p_top_an1_x, h, p_top_an1_z);
		glVertex3d(p_top_an2_x, h, p_top_an2_z);
		glVertex3d(0, h, 0);

		//Stranica od 2 trougla

		glVertex3d(p_bottom_an1_x, 0, p_bottom_an1_z);
		glVertex3d(p_bottom_an2_x, 0, p_bottom_an2_z);
		glVertex3d(p_top_an2_x, h, p_top_an2_z);

		glVertex3d(p_top_an2_x, h, p_top_an2_z);
		glVertex3d(p_top_an1_x, h, p_top_an1_z);
		glVertex3d(p_bottom_an1_x, 0, p_bottom_an1_z);
	} */

	glBegin(GL_TRIANGLE_FAN);

	//Osnovica donja
	glVertex3d(0, 0, 0);
	for (int angle = 0; angle <= 360; angle += angleStep) {

		double p_bottom_an1_x = r1 * cos(angle * TORAD);
		double p_bottom_an1_z = r1 * sin(angle * TORAD);

		glVertex3d(p_bottom_an1_x, 0, p_bottom_an1_z);
	}

	glEnd();
	glBegin(GL_TRIANGLE_FAN);

	//Osnovica gornja
	glVertex3d(0, h, 0);
	for (int angle = 0; angle <= 360; angle += angleStep) {

		double p_top_an1_x = r2 * cos(angle * TORAD);
		double p_top_an1_z = r2 * sin(angle * TORAD);

		glVertex3d(p_top_an1_x, h, p_top_an1_z);
	}

	glEnd();
	glBegin(GL_QUAD_STRIP);

	//Omotac
	for (int angle = 0; angle <= 360; angle += angleStep) {

		double p_bottom_an1_x = r1 * cos(angle * TORAD);
		double p_bottom_an1_z = r1 * sin(angle * TORAD);
		double p_top_an1_x = r2 * cos(angle * TORAD);
		double p_top_an1_z = r2 * sin(angle * TORAD);

		glVertex3d(p_top_an1_x, h, p_top_an1_z);
		glVertex3d(p_bottom_an1_x, 0, p_bottom_an1_z);
	}

	glEnd();
}

void CGLRenderer::DrawGrid(double width, double height, int nSegW, int nSegH) {

	glLineWidth(1);
	glPointSize(1);

	double segWidth = width / nSegW;
	double segHeight = height / nSegH;

	double startx = -segWidth * nSegW/2;
	double startz = -segHeight * nSegH/2;

	glBegin(GL_LINES);
	
	glColor3f(1, 1, 1);
	for (int i = 0; i <= nSegW; i++) {
		glVertex3f(startx + i * segWidth, 0, startz);
		glVertex3f(startx + i * segWidth, 0, startz + height);
	}

	for (int i = 0; i <= nSegH; i++) {
		glVertex3f(startx, 0, startz + i * segHeight);
		glVertex3f(startx + width, 0, startz + i* segHeight);
	}

	glEnd();
}

void CGLRenderer::DrawFigure(double yellowAngle) {

	double cylinderHeight = 15;
	double cylinderRadius = 5;
	double coneHeight = 15;
	double coneRadius = 5;
	double cylinderSegments = 8;
	double coneSegments = 8;
	double sphereRadius = 4;
	double sphereSegments = 20;

	//Cuvanje matrice transformacije koja je postojala pre pozivanja fje za crtanje figure
	glPushMatrix();

	//Donji deo saksije
	glColor3f(0.00, 0.80, 0.00);
	DrawCylinder(15, 10, 12, 8);

	//Gornji deo saksije	
	glTranslatef(0,15,0);
	DrawCylinder(5, 15, 15, 8);

	//Prvi kaktus cilindar (sad je kupa)
	glTranslatef(0, 5, 0);
	glColor3f(1, 0.6, 0);
	DrawCone(coneHeight, coneRadius, coneSegments);

	//Prva kaktus sfera
	glTranslatef(0, cylinderHeight+sphereRadius, 0);
	glColor3f(0.47, 0.00, 0.00);
	DrawSphere(sphereRadius, sphereSegments, sphereSegments);

	glPushMatrix();

	//Leva grana - ZUTI KOJI SE ROTIRA
	glRotatef(alpha + 45, 1, 0, 0);

		//Cilindar - ZUTI
		glTranslatef(0, sphereRadius, 0);
		glColor3f(1, 1, 0);
		DrawCylinder(cylinderHeight, cylinderRadius, cylinderRadius, cylinderSegments);

		//Sfera
		glTranslatef(0, cylinderHeight+sphereRadius, 0);
		glColor3f(0.47, 0.00, 0.00);
		DrawSphere(sphereRadius, sphereSegments, sphereSegments);

		glPushMatrix();

		//Leva grana - kupa

		glRotatef(45, 1, 0, 0);

			//Kupa
			glTranslatef(0, sphereRadius, 0);
			glColor3f(1, 0.6, 0);
			DrawCone(coneHeight, coneRadius, coneSegments);

			//Sfera
			glTranslatef(0, coneHeight+sphereRadius, 0);
			glColor3f(0.47, 0.00, 0.00);
			DrawSphere(sphereRadius, sphereSegments, sphereSegments);

		glPopMatrix();

		//Desna grana - kupa

		glRotatef(-45, 1, 0, 0);

			//Kupa
			glTranslatef(0, sphereRadius, 0);
			glColor3f(1, 0.6, 0);
			DrawCone(coneHeight, coneRadius, coneSegments);

			//Sfera
			glTranslatef(0, coneHeight + sphereRadius, 0);
			glColor3f(0.47, 0.00, 0.00);
			DrawSphere(sphereRadius, sphereSegments, sphereSegments);

	glPopMatrix();

	glPushMatrix();

	//Desna strana
	glRotatef(-45, 1, 0, 0);

		//Cilindar -sad cone
		glTranslatef(0, sphereRadius, 0);
		glColor3f(1, 0.6, 0);
		DrawCone(coneHeight, coneRadius, coneSegments);

		//Sfera
		glTranslatef(0, cylinderHeight + sphereRadius, 0);
		glColor3f(0.47, 0.00, 0.00);
		DrawSphere(sphereRadius, sphereSegments, sphereSegments);

		//Kupa - sad cilindar
		glTranslatef(0, sphereRadius, 0);
		glColor3f(1, 0.6, 0);
		DrawCylinder(cylinderHeight, cylinderRadius, cylinderRadius, cylinderSegments);

		//Sfera
		glTranslatef(0, coneHeight + sphereRadius, 0);
		glColor3f(0.47, 0.00, 0.00);
		DrawSphere(sphereRadius, sphereSegments, sphereSegments);

		//Kupa - sad cilindar
		glTranslatef(0, sphereRadius, 0);
		glColor3f(1, 0.6, 0);
		DrawCylinder(cylinderHeight, cylinderRadius, cylinderRadius, cylinderSegments);

		//Sfera
		glTranslatef(0, coneHeight + sphereRadius, 0);
		glColor3f(0.47, 0.00, 0.00);
		DrawSphere(sphereRadius, sphereSegments, sphereSegments);

	glPopMatrix();

	//Uspravno

		//Cilindar - sad cone
		glTranslatef(0, sphereRadius, 0);
		glColor3f(1, 0.6, 0);
		DrawCone(coneHeight, coneRadius, coneSegments);

		//Sfera
		glTranslatef(0, coneHeight + sphereRadius, 0);
		glColor3f(0.47, 0.00, 0.00);
		DrawSphere(sphereRadius, sphereSegments, sphereSegments);

		//Cone
		glTranslatef(0, sphereRadius, 0);
		glColor3f(1, 0.6, 0);
		DrawCone(coneHeight, coneRadius, coneSegments);

		//Sfera
		glTranslatef(0, coneHeight + sphereRadius, 0);
		glColor3f(0.47, 0.00, 0.00);
		DrawSphere(sphereRadius, sphereSegments, sphereSegments);

		//Levo
		glPushMatrix();

		glRotatef(45, 1, 0, 0);

			//Cilindar - sad cone
			glTranslatef(0, sphereRadius, 0);
			glColor3f(1, 0.6, 0);
			DrawCone(coneHeight, coneRadius, coneSegments);

			//Sfera
			glTranslatef(0, cylinderHeight+sphereRadius, 0);
			glColor3f(0.47, 0.00, 0.00);
			DrawSphere(sphereRadius, sphereSegments, sphereSegments);


		glPopMatrix();

		//Desno
		glPushMatrix();

		glRotatef(-45, 1, 0, 0);

			//Cilindar - sad cone
			glTranslatef(0, sphereRadius, 0);
			glColor3f(1, 0.6, 0);
			DrawCone(coneHeight, coneRadius, coneSegments);

			//Sfera
			glTranslatef(0, cylinderHeight + sphereRadius, 0);
			glColor3f(0.47, 0.00, 0.00);
			DrawSphere(sphereRadius, sphereSegments, sphereSegments);

		glPopMatrix();

	//Vracanje one matrice transformacije koja je bila pre poziva ove fje za crtanje figure
	glPopMatrix();
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	double eyeX = m_radius * cos(m_angleX) * cos(m_angleY);
	double eyeY = m_radius * sin(m_angleX);
	double eyeZ = m_radius * cos(m_angleX) * sin(m_angleY);
	
	double upX = 0;
	double upY = 1;
	double upZ = 0;

	gluLookAt(eyeX, eyeY, eyeZ, 
			  0, 60, 0,
			  upX, upY, upZ);
	
	DrawGrid(100, 100, 10, 10);
	DrawAxis(200);

	//Kaktus
	DrawFigure(alpha);

	glFlush();
	//---------------------------------
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}


void CGLRenderer::Reshape(CDC *pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)w / (double)h, 1, 500);
	glMatrixMode(GL_MODELVIEW);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 
	wglMakeCurrent(NULL,NULL); 
	if(m_hrc) 
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}
