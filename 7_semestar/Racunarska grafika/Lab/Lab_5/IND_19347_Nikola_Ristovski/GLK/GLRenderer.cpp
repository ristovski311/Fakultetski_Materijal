#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
//#pragma comment(lib, "GL\\glut32.lib")

#define TORAD 3.141592/180
#define TODEG 180/3.141592

CGLRenderer::CGLRenderer(void)
{
	redLightOn = false;
	blueLightOn = false;
	greenLightOn = false;

	showNormals = false;

	isMouseDown = false;
	cameraRadius = 200;
	cameraAngleX = 0;
	cameraAngleY = 0;
}

CGLRenderer::~CGLRenderer(void)
{
}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);

	if (nPixelFormat == 0) return false;

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);

	if (!bResult) return false;

	m_hrc = wglCreateContext(pDC->m_hDC);

	if (!m_hrc) return false;

	return true;
}

//KOD: 14284

void CGLRenderer::PrepareScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClearColor(0.5, 0.5, 0.5, 1);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	GLfloat lmAmbient[] = { 0.2,0.2,0.2,1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmAmbient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_NORMALIZE);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}


void CGLRenderer::DrawAxis(int w) {

	glLineWidth(2);
	glPointSize(1);

	glBegin(GL_LINES);

	//X osa
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(w, 0, 0);

	//Y osa
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, w, 0);

	//Z osa
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, w);

	glEnd();
}

void CGLRenderer::DrawSphere(double r, int nSegAlpha, int nSegBeta, bool isHalfSphere)
{
	double betaStep = 360.0 / nSegBeta;
	double alphaStep = 180.0 / nSegAlpha;

	double startAlpha = isHalfSphere ? 0 : -90; //-90 je severni pol, 0 ekvator, 90 juzni pol
	double endAlpha = 90;

	for (double alpha = startAlpha; alpha < endAlpha; alpha += alphaStep)
	{
		glBegin(GL_QUAD_STRIP);
		for (double beta = 0; beta <= 360; beta += betaStep)
		{
			double a1 = alpha * TORAD;
			double a2 = (alpha + alphaStep) * TORAD;
			double b = beta * TORAD;

			double x1 = r * cos(a1) * cos(b);
			double y1 = r * sin(a1);
			double z1 = r * cos(a1) * sin(b);

			double x2 = r * cos(a2) * cos(b);
			double y2 = r * sin(a2);
			double z2 = r * cos(a2) * sin(b);

			glNormal3d(cos(a1) * cos(b), sin(a1), cos(a1) * sin(b));
			glVertex3d(x1, y1, z1);

			glNormal3d(cos(a2) * cos(b), sin(a2), cos(a2) * sin(b));
			glVertex3d(x2, y2, z2);
		}
		glEnd();
	}


}

void CGLRenderer::DrawCylinder(double h, double r1, double r2, int nSeg) {
	double angleStep = 360 / nSeg;
	glBegin(GL_TRIANGLE_FAN);

	//Osnovica donja
	glNormal3d(0, -1, 0);
	glVertex3d(0, 0, 0);
	for (int angle = 0; angle <= 360; angle += angleStep) {

		double p_bottom_an1_x = r1 * cos(angle * TORAD);
		double p_bottom_an1_z = r1 * sin(angle * TORAD);

		glNormal3d(0, -1, 0);
		glVertex3d(p_bottom_an1_x, 0, p_bottom_an1_z);
	}

	glEnd();
	glBegin(GL_TRIANGLE_FAN);

	//Osnovica gornja
	glNormal3d(0, 1, 0);
	glVertex3d(0, h, 0);
	for (int angle = 0; angle < 360; angle += angleStep) {

		double p_top_an1_x = r2 * cos(angle * TORAD);
		double p_top_an1_z = r2 * sin(angle * TORAD);

		glNormal3d(0, 1, 0);
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

		double dr = r1 - r2;
		double L = sqrt(h * h + dr * dr);
		double nr = h / L;

		double nx = nr * cos(angle * TORAD);
		double ny = dr / L;
		double nz = nr * sin(angle * TORAD);

		glNormal3d(nx, ny, nz);
		glVertex3d(p_bottom_an1_x, 0, p_bottom_an1_z);
		glNormal3d(nx, ny, nz);
		glVertex3d(p_top_an1_x, h, p_top_an1_z);
	}

	glEnd();
}

void CGLRenderer::DrawCube(double a, double b, double h, int segA, int segB, int segH)
{
	double stepA = a / segA;
	double stepB = b / segB;
	double stepH = h / segH;

	double start_x = -a / 2.0, end_x = a / 2.0;
	double start_z = -b / 2.0, end_z = b / 2.0;

	// PREDNJA strana (z = +b/2)
	for (int iy = 0; iy < segH; iy++) {
		double y0 = iy * stepH;
		double y1 = y0 + stepH;
		for (int ix = 0; ix < segA; ix++) {
			double x0 = start_x + ix * stepA;
			double x1 = x0 + stepA;

			glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);
			glVertex3d(x0, y0, end_z);
			glVertex3d(x1, y0, end_z);
			glVertex3d(x1, y1, end_z);
			glVertex3d(x0, y1, end_z);

			glEnd();
		}
	}

	// ZADNJA strana (z = -b/2)
	for (int iy = 0; iy < segH; iy++) {
		double y0 = iy * stepH;
		double y1 = y0 + stepH;
		for (int ix = 0; ix < segA; ix++) {
			double x0 = start_x + ix * stepA;
			double x1 = x0 + stepA;

			glBegin(GL_QUADS);
			glNormal3f(0, 0, -1);
			glVertex3d(x0, y0, start_z);
			glVertex3d(x0, y1, start_z);
			glVertex3d(x1, y1, start_z);
			glVertex3d(x1, y0, start_z);

			glEnd();
		}
	}

	// LEVA strana (x = -a/2)
	for (int iy = 0; iy < segH; iy++) {
		double y0 = iy * stepH;
		double y1 = y0 + stepH;
		for (int iz = 0; iz < segB; iz++) {
			double z0 = start_z + iz * stepB;
			double z1 = z0 + stepB;

			glBegin(GL_QUADS);
			glNormal3f(-1, 0, 0);
			glVertex3d(start_x, y0, z0);
			glVertex3d(start_x, y0, z1);
			glVertex3d(start_x, y1, z1);
			glVertex3d(start_x, y1, z0);

			glEnd();
		}
	}

	// DESNA strana (x = +a/2)
	for (int iy = 0; iy < segH; iy++) {
		double y0 = iy * stepH;
		double y1 = y0 + stepH;
		for (int iz = 0; iz < segB; iz++) {
			double z0 = start_z + iz * stepB;
			double z1 = z0 + stepB;

			glBegin(GL_QUADS);
			glNormal3f(1, 0, 0);
			glVertex3d(end_x, y0, z1);
			glVertex3d(end_x, y0, z0);
			glVertex3d(end_x, y1, z0);
			glVertex3d(end_x, y1, z1);

			glEnd();
		}
	}

	// GORNJA strana (y = h)
	for (int ix = 0; ix < segA; ix++) {
		double x0 = start_x + ix * stepA;
		double x1 = x0 + stepA;
		for (int iz = 0; iz < segB; iz++) {
			double z0 = start_z + iz * stepB;
			double z1 = z0 + stepB;

			glBegin(GL_QUADS);
			glNormal3f(0, 1, 0);
			glVertex3d(x0, h, z0);
			glVertex3d(x0, h, z1);
			glVertex3d(x1, h, z1);
			glVertex3d(x1, h, z0);

			glEnd();			
		}
	}

	// DONJA strana (y = 0)
	for (int ix = 0; ix < segA; ix++) {
		double x0 = start_x + ix * stepA;
		double x1 = x0 + stepA;
		for (int iz = 0; iz < segB; iz++) {
			double z0 = start_z + iz * stepB;
			double z1 = z0 + stepB;

			glBegin(GL_QUADS);
			glNormal3f(0, -1, 0);
			glVertex3d(x0, 0, z0);
			glVertex3d(x1, 0, z0);
			glVertex3d(x1, 0, z1);
			glVertex3d(x0, 0, z1);

			glEnd();
		}
	}
}

void CGLRenderer::DrawCone(double h, double r, int nSeg) {
	float angleStep = 360 / nSeg;

	glBegin(GL_TRIANGLE_FAN);

	//Osnovica
	glNormal3d(0, -1, 0);
	glVertex3d(0, 0, 0);
	for (int angle = 0; angle <= 360; angle += angleStep) {

		double p_x = r * cos(angle * TORAD);
		double p_z = r * sin(angle * TORAD);

		glNormal3d(0, -1, 0);
		glVertex3d(p_x, 0, p_z);
	}

	glEnd();
	glBegin(GL_TRIANGLE_STRIP);

	//Omotac
	for (int angle = 0; angle <= 360; angle += angleStep) {

		double p_x = r * cos(angle * TORAD);
		double p_z = r * sin(angle * TORAD);

		double L = sqrt(h * h + r * r);
		double nr = h / L;
		double nx = nr * cos(angle * TORAD);
		double ny = (r / L);
		double nz = nr * sin(angle * TORAD);

		glNormal3d(nx, ny, nz);
		glVertex3d(0, h, 0);
		glNormal3d(nx, ny, nz);
		glVertex3d(p_x, 0, p_z);
	}

	glEnd();
}

void CGLRenderer::DrawConeRing(double h, double r1, double r2, int nSeg, float R, float G, float B) {

	double angleStep = 360 / nSeg;

	glBegin(GL_QUAD_STRIP);
	//Omotac spolja
	for (int angle = 0; angle <= 360; angle += angleStep) {

		double p_bottom_an1_x = r1 * cos(angle * TORAD);
		double p_bottom_an1_z = r1 * sin(angle * TORAD);
		double p_top_an1_x = r2 * cos(angle * TORAD);
		double p_top_an1_z = r2 * sin(angle * TORAD);

		double dr = r2 - r1;
		double L = sqrt(h * h + dr * dr);
		double nr = h / L;

		double nx = nr * cos(angle * TORAD);
		double ny = -dr / L;
		double nz = nr * sin(angle * TORAD);

		glColor3f(R, G, B);

		glNormal3d(nx, ny, nz);
		glVertex3d(p_bottom_an1_x, 0, p_bottom_an1_z);

		glNormal3d(nx, ny, nz);
		glVertex3d(p_top_an1_x, h, p_top_an1_z);

	}
	glEnd();

	glDisable(GL_LIGHTING);

	glLineWidth(1);
	//Normale
	if (showNormals)
	{
		glColor3f(0, 1, 0);
		glLineWidth(1);
		glBegin(GL_LINES);
		for (int angle = 0; angle <= 360; angle += angleStep)
		{
			double p_bottom_x = r1 * cos(angle * TORAD);
			double p_bottom_z = r1 * sin(angle * TORAD);
			double p_top_x = r2 * cos(angle * TORAD);
			double p_top_z = r2 * sin(angle * TORAD);

			double dr = r2 - r1;
			double L = sqrt(h * h + dr * dr);
			double nr = h / L;

			double nx = nr * cos(angle * TORAD);
			double ny = -dr / L;
			double nz = nr * sin(angle * TORAD);

			// Bottom normal
			glVertex3d(p_bottom_x, 0, p_bottom_z);
			glVertex3d(p_bottom_x + nx * 5, 0 + ny * 5, p_bottom_z + nz * 5);
			// Top normal
			glVertex3d(p_top_x, h, p_top_z);
			glVertex3d(p_top_x + nx * 5, h + ny * 5, p_top_z + nz * 5);

		}
		glEnd();
	}

	glEnable(GL_LIGHTING);

}

void CGLRenderer::DrawFigure()
{
	int SphereRadius = 30;
	int SphereSegments = 30;
	int CylinderHeight = 20;
	int CylinderRadius = 10;
	int CylinderSegments = 8;

	int CubeSide = 100;
	int CubeHeight = 20;

	int RingHeight = 5;
	int RingRadiusL = 20;
	int RingRadiusM = 15;
	int RingRadiusS = 10;
	int RingSegments = 30;

	glPushMatrix();

	//Bela
	glColor3f(1, 1, 1);

	GLfloat ambPedestal[] = { 0.2, 0.2, 0.2 ,1 };
	GLfloat difPedestal[] = { 0.8,0.8,0.8,1 };
	GLfloat specPedestal[] = { 1,1,1,1 };
	GLfloat shPedestal = 32;
	GLfloat emPedestal[] = { 0,0,0,1 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambPedestal);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difPedestal);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specPedestal);
	glMaterialf(GL_FRONT, GL_SHININESS, shPedestal);
	glMaterialfv(GL_FRONT, GL_EMISSION, emPedestal);

	//Polusfera
	DrawSphere(SphereRadius, SphereSegments, SphereSegments, true);
	glTranslatef(0, SphereRadius - SphereRadius / 10, 0);

	//Cilindar
	DrawCylinder(CylinderHeight, CylinderRadius, CylinderRadius, CylinderSegments);
	glTranslatef(0, CylinderHeight, 0);

	GLfloat ambCube[] = { 0.1, 0.1, 0.1 ,1 };
	GLfloat difCube[] = { 0.5,0.5,0.5,1 };
	GLfloat specCube[] = { 1,1,1,1 };
	GLfloat shCube = 8;
	GLfloat emCube[] = { 0,0,0,1 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambCube);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difCube);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specCube);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shCube);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emCube);

	//Kvadar
	DrawCube(CubeSide, CubeSide, CubeHeight, 50, 50, 50);
	glTranslatef(0, CubeHeight, 0);

	//Boja - plava
	float color1R = 0.0;
	float color1G = 0.0;
	float color1B = 1.0;

	//Boja - zuta
	float color2R = 1.0;
	float color2G = 1.0;
	float color2B = 0.0;

	GLfloat ambVase[] = { 0.2, 0.2,0.2,1 };
	GLfloat difVase[] = { 0.7,0.7,0.7,1 };
	GLfloat specVase[] = { 1,1,1,1 };
	GLfloat shVase = 8.0;
	GLfloat emVase[] = { 0,0,0,1 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambVase);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difVase);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specVase);
	glMaterialf(GL_FRONT, GL_SHININESS, shVase);
	glMaterialfv(GL_FRONT, GL_EMISSION, emVase);

	//Vaza deo 1 - plava
	DrawConeRing(RingHeight, RingRadiusL, RingRadiusM, RingSegments, color1R, color1G, color1B);
	glTranslatef(0, RingHeight, 0);

	//Vaza deo2 - zuta
	DrawConeRing(RingHeight, RingRadiusM, RingRadiusS, RingSegments, color2R, color2G, color2B);
	glTranslatef(0, RingHeight, 0);

	//Vaza deo 3 - plava
	DrawConeRing(RingHeight, RingRadiusS, RingRadiusS, RingSegments, color1R, color1G, color1B);
	glTranslatef(0, RingHeight, 0);

	//Vaza deo 4 - zuta
	DrawConeRing(RingHeight, RingRadiusS, RingRadiusS, RingSegments, color2R, color2G, color2B);
	glTranslatef(0, RingHeight, 0);

	//Vaza deo 5 - plava
	DrawConeRing(RingHeight, RingRadiusS, RingRadiusM, RingSegments, color1R, color1G, color1B);
	glTranslatef(0, RingHeight, 0);

	//Vaza deo 6 - zuta
	DrawConeRing(RingHeight, RingRadiusM, RingRadiusL, RingSegments, color2R, color2G, color2B);
	glTranslatef(0, RingHeight, 0);

	//Vaza deo 7 - plava
	DrawConeRing(RingHeight, RingRadiusL, RingRadiusM, RingSegments, color1R, color1G, color1B);
	glTranslatef(0, RingHeight, 0);

	//Vaza deo 8 - zuta
	DrawConeRing(RingHeight, RingRadiusM, RingRadiusL, RingSegments, color2R, color2G, color2B);
	glTranslatef(0, RingHeight, 0);

	//Vaza deo 9 - plava
	DrawConeRing(RingHeight, RingRadiusL, RingRadiusM, RingSegments, color1R, color1G, color1B);
	glTranslatef(0, RingHeight, 0);

	//Vaza deo 10 - zuta
	DrawConeRing(RingHeight, RingRadiusM, RingRadiusL, RingSegments, color2R, color2G, color2B);
	glTranslatef(0, RingHeight, 0);

	//Vaza deo 11 - plava
	DrawConeRing(RingHeight, RingRadiusL, RingRadiusM, RingSegments, color1R, color1G, color1B);
	glTranslatef(0, RingHeight, 0);

	//Vaza deo 12 - zuta
	DrawConeRing(RingHeight, RingRadiusM, RingRadiusS, RingSegments, color2R, color2G, color2B);
	glTranslatef(0, RingHeight, 0);

	//Vaza deo 13 - plava
	DrawConeRing(RingHeight, RingRadiusS, RingRadiusM, RingSegments, color1R, color1G, color1B);
	glTranslatef(0, RingHeight, 0);

	//Vaza deo 14 - zuta
	DrawConeRing(RingHeight, RingRadiusM, RingRadiusL, RingSegments, color2R, color2G, color2B);
	glTranslatef(0, RingHeight, 0);

	glPopMatrix();

}

void CGLRenderer::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Kamera
	{
		double eyeX = cameraRadius * cos(cameraAngleX) * sin(cameraAngleY);
		double eyeY = cameraRadius * sin(cameraAngleX);
		double eyeZ = cameraRadius * cos(cameraAngleX) * cos(cameraAngleY);

		double lookingAtX = 0;
		double lookingAtY = 70;
		double lookingAtZ = 0;

		gluLookAt(
			eyeX, eyeY, eyeZ,
			lookingAtX, lookingAtY, lookingAtZ,
			0, 1, 0
		);
	}

	//Svetlost
	{
		GLfloat l0Pos[] = { 1,1,1, 0 };
		GLfloat l0Amb[] = { 0.2, 0.2, 0.2, 1 };
		GLfloat l0Diff[] = { 0.5, 0.5, 0.5, 1 };
		glLightfv(GL_LIGHT0, GL_POSITION, l0Pos);
		glLightfv(GL_LIGHT0, GL_AMBIENT, l0Amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, l0Diff);

		//Bela svetlost
		glEnable(GL_LIGHT0);



		//Crvena
		GLfloat l1Pos[] = { 0, 200, 200, 1 };
		GLfloat l1Amb[] = { 0.5, 0, 0, 1 };
		GLfloat l1Diff[] = { 1, 0, 0, 1 };
		GLfloat l1Spec[] = { 1, 0, 0, 1 };
		glLightfv(GL_LIGHT1, GL_POSITION, l1Pos);
		glLightfv(GL_LIGHT1, GL_AMBIENT, l1Amb);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, l1Diff);
		glLightfv(GL_LIGHT1, GL_SPECULAR, l1Spec);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.5);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20.0);
		GLfloat l1SpotDir[] = { 0, 0, -1 };
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, l1SpotDir);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

		if (redLightOn)
		{
			glEnable(GL_LIGHT1);

			glDisable(GL_LIGHTING);
			glTranslated(0, 200, 200);
			glColor3f(1, 0, 0);
			DrawSphere(10, 20, 20, false);
			glTranslated(0, -200, -200);
			glEnable(GL_LIGHTING);

		}
		else
			glDisable(GL_LIGHT1);

		//Plava
		GLfloat l2Pos[] = { 0, 200, -200, 1 };
		GLfloat l2Amb[] = { 0, 0.5, 0.5, 1 };
		GLfloat l2Diff[] = { 0, 1, 1, 1 };
		GLfloat l2Spec[] = { 0, 1, 1, 1 };
		GLfloat l2SpotDir[] = { 0,0, 1 };
		glLightfv(GL_LIGHT2, GL_POSITION, l2Pos);
		glLightfv(GL_LIGHT2, GL_AMBIENT, l2Amb);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, l2Diff);
		glLightfv(GL_LIGHT2, GL_SPECULAR, l2Spec);
		glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.5);
		glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0);
		glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 20.0);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, l2SpotDir);
		glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2);

		if (greenLightOn)
		{
			glEnable(GL_LIGHT2);

			glDisable(GL_LIGHTING);
			glTranslated(0, 200, -200);
			glColor3f(0, 1, 1);
			DrawSphere(10, 20, 20, false);
			glTranslated(0, -200, 200);
			glEnable(GL_LIGHTING);

		}
		else
			glDisable(GL_LIGHT2);

		//Zuta
		GLfloat l3Pos[] = { 0, 400, 0, 1 };
		GLfloat l3Amb[] = { 0.2, 0.2, 0, 1 };
		GLfloat l3Diff[] = { 0.5, 0.5, 0, 1 };
		GLfloat l3Spec[] = { 0.5, 0.5, 0, 1 };
		GLfloat l3SpotDir[] = { 0,-1,0 };
		glLightfv(GL_LIGHT3, GL_POSITION, l3Pos);
		glLightfv(GL_LIGHT3, GL_AMBIENT, l3Amb);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, l3Diff);
		glLightfv(GL_LIGHT3, GL_SPECULAR, l3Spec);
		glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.5);
		glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.0);
		glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.0);
		glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 20.0);
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, l3SpotDir);
		glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 2.0);

		if (blueLightOn)
		{
			glEnable(GL_LIGHT3);

			glDisable(GL_LIGHTING);
			glTranslated(0, 400, 0);
			glColor3f(1, 1, 0);
			DrawSphere(10, 20, 20, false);
			glTranslated(0, -400, 0);
			glEnable(GL_LIGHTING);
		}
		else
			glDisable(GL_LIGHT3);
	}

	//Iscrtavanje
	{
		glDisable(GL_LIGHTING);
		DrawAxis(400);
		glEnable(GL_LIGHTING);

		//SOBA
		GLfloat ambCube[] = { 0.8, 0.8, 0.8 ,1 };
		GLfloat difCube[] = { 0.9,0.9,0.9,1 };
		GLfloat specCube[] = { 1,1,1,1 };
		GLfloat shCube = 8;
		GLfloat emCube[] = { 0,0,0,1 };

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambCube);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difCube);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specCube);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shCube);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emCube);

		//glTranslatef(0, 100, 0);

		//SOBA
		glColor3d(1, 1, 1);
		DrawCube(600, 600, 600, 100, 100, 100);
		
		//FIGURA
		DrawFigure();

		//glTranslatef(0, -100, 0);
	}

	glFlush();
	SwapBuffers(pDC->m_hDC);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Reshape(CDC* pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, (double)w / (double)h, 0.1, 2000);
	glMatrixMode(GL_MODELVIEW);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 
	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}
