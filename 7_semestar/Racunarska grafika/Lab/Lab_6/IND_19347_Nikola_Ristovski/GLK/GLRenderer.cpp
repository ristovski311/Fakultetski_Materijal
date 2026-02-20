#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#include "DImage.h"
//#pragma comment(lib, "GL\\glut32.lib")

#define TORAD 3.141592/180
#define SQUARE_SIDE 10
#define SQUARE_COUNT 16
#define GRASS_SQUARE_COUNT 8

CGLRenderer::CGLRenderer(void)
{
	angleCameraX = 0;
	angleCameraY = 0;

	isMouseDown = false;
	radiusCamera = 200;

	enableLight = true;

	wheelRotationAngle = 0;
	wheelSteerAngle = 0;

	offsetX = 0;
	offsetZ = 0;
	truckRotationAngle = 0;

	grassTexture = new DImage();
	grassTexture->Load(L"grassTexture.jpg");

	figureTexture = new DImage();
	figureTexture->Load(L"figureTexture2.png");
}

CGLRenderer::~CGLRenderer(void)
{
	if (grassTexture)
		delete grassTexture;

	if (figureTexture)
		delete figureTexture;
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
	glClearColor(0.14, 0.69, 1, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	//Light
	if(enableLight){
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

		GLfloat lmAmb[] = { 0.4,0.4,0.4,1 };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmAmb);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	}

	//Load texture-a

	glEnable(GL_TEXTURE_2D);

	grassTextureID = LoadTexture(grassTexture, false, false);
	figureTextureID = LoadTexture(figureTexture, true, true);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

// CRTANJE ====================================================================================================================

void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Camera
	{
		double eyeX = radiusCamera * cos(angleCameraX) * sin(angleCameraY);
		double eyeY = radiusCamera * sin(angleCameraX);
		double eyeZ = radiusCamera * cos(angleCameraX) * cos(angleCameraY);

		double centerX = 0;
		double centerY = 20;
		double centerZ = 0;

		gluLookAt(eyeX, eyeY, eyeZ,
			centerX, centerY, centerZ,
			0, 1, 0);
	}

	//Svetlo
	{
		GLfloat ambient[] = { 0.2,0.2,0.2,1 };
		GLfloat position[] = { 0, 1, 0, 0 };
		GLfloat diffuse[] = { 0.5,0.5,0.5,1 };

		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

		if (enableLight)
			glEnable(GL_LIGHT0);
		else
			glDisable(GL_LIGHT0);
	}

	//Crtanje
	{
		DrawAxis(500);
		DrawGround();
		glTranslatef(offsetX, 0, offsetZ);
		glRotatef(truckRotationAngle, 0, 1, 0);
		DrawFigure();
		glRotatef(-truckRotationAngle, 0, 1, 0);
		glTranslatef(-offsetX, 0, -offsetZ);
	}

	glFlush();
	SwapBuffers(pDC->m_hDC);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

// CRTANJE ====================================================================================================================

void CGLRenderer::Reshape(CDC *pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	double aspect = (double)w / h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, aspect, 0.1, 3000);
	glMatrixMode(GL_MODELVIEW);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 

	UINT txts[] = { grassTextureID, figureTextureID };
	glDeleteTextures(2, txts);

	wglMakeCurrent(NULL,NULL); 
	if(m_hrc) 
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

UINT CGLRenderer::LoadTexture(DImage* img, bool isSClamp, bool isTClamp) {

	UINT textureID;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	if(isSClamp)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	else
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	if (isTClamp)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	else
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (enableLight)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	else
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img->Width(), img->Height(), GL_RGBA, GL_UNSIGNED_BYTE, img->GetDIBBits());

	return textureID;
}

// MOJE FJE 22518

void CGLRenderer::DrawAxis(double width) {

	if(enableLight)
		glDisable(GL_LIGHTING);
	
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINES);

	//X osa
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(width, 0, 0);

	//Y osa
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, width, 0);

	//Z osa
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, width);

	glEnd();
	glEnable(GL_TEXTURE_2D);

	if(enableLight)
		glEnable(GL_LIGHTING);
}

void CGLRenderer::DrawGround() {

	int half_size = 20 * SQUARE_SIDE;

	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, grassTextureID);

	glBegin(GL_QUADS);
	glNormal3d(0, 1, 0);

	//Prvo teme -x -z
	glTexCoord2f(5.0, 5.0);
	glVertex3d(-half_size, 0, -half_size);

	//Drugo teme -x z
	glTexCoord2f(0.0, 5.0);
	glVertex3d(-half_size, 0, half_size);

	//Trece teme x z
	glTexCoord2f(0.0, 0.0);
	glVertex3d(half_size, 0, half_size);

	//Cetvrto teme x -z
	glTexCoord2f(5.0, 0.0);
	glVertex3d(half_size, 0, -half_size);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void CGLRenderer::DrawSphere(double radius, int alphaSeg, int betaSeg, bool isHalfSphere) {

	double alphaStep = 180.0 / alphaSeg;
	double betaStep = 360.0 / betaSeg;

	double alphaStart = isHalfSphere ? 0 : -90;
	double alphaEnd = 90;

	glBindTexture(GL_TEXTURE_2D, figureTextureID);

	glColor3f(1, 1, 1);
	glBegin(GL_QUAD_STRIP);

	for (double alpha = alphaStart; alpha < alphaEnd; alpha += alphaStep)	
	{
		double y_top =  sin(alpha * TORAD);
		double y_bottom =  sin((alpha + alphaStep) * TORAD);

		double t_top = 1 - ((alpha + 90) / 180) * 0.5; // procentualno izracunamo gde je t na osnovu ugla alfa
		double t_bottom = 1 - (((alpha + 90 + alphaStep) / 180) * 0.5);

		for (double beta = 0; beta <= 360; beta += betaStep)
		{
			double x_top = cos(alpha*TORAD) * sin(beta*TORAD);
			double x_bottom = cos((alpha + alphaStep)*TORAD) * sin(beta*TORAD);
			double z_top =  cos(alpha * TORAD) * cos(beta * TORAD);
			double z_bottom =  cos((alpha + alphaStep) * TORAD) * cos(beta * TORAD);

			double s = beta / 360;

			glNormal3f(x_top, y_top, z_top);
			glTexCoord2f(s, t_top);
			glVertex3f(x_top * radius, y_top * radius, z_top * radius);

			glNormal3f(x_bottom, y_bottom, z_bottom);
			glTexCoord2d(s, t_bottom);
			glVertex3f(x_bottom * radius, y_bottom * radius, z_bottom * radius);
		}
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CGLRenderer::DrawEllipsoid()
{
	double sphereRadius = 2*SQUARE_SIDE;
	int sphereSegments = 16;

	glPushMatrix();
	glScaled(3.0 / 2, 1, 3.5 / 2);
	DrawSphere(sphereRadius, sphereSegments, sphereSegments, false);
	glPopMatrix();
}

void CGLRenderer::DrawCylinder(double r, double height, int seg)
{
	double angleStep = 360.0 / seg;

	double s_center = 6.0 / 16;
	double t_center = 1.5 / 16; //Slika je sacuvana naopacke?
	double texture_radius = 1.5 / 16;

	glBindTexture(GL_TEXTURE_2D, figureTextureID);
	glColor3f(1, 1, 1);

	//Osnovica gornja
	glBegin(GL_TRIANGLE_FAN);

	glNormal3d(0, 1, 0);
	glTexCoord2d(s_center, t_center);
	glVertex3d(0, height/2, 0);
	for(double alpha = 0; alpha <= 360; alpha+= angleStep)
	{
		double x = r * cos(alpha * TORAD);
		double z = r * sin(alpha * TORAD);

		double s = s_center + texture_radius * cos(alpha * TORAD);
		double t = t_center + texture_radius * sin(alpha * TORAD);

		glTexCoord2d(s, t);
		glVertex3d(x, height / 2, z);
	}
	glEnd();


	//Osnovica donja
	glBegin(GL_TRIANGLE_FAN);

	glNormal3d(0, -1, 0);
	glTexCoord2d(s_center, t_center);
	glVertex3d(0, -height / 2, 0);
	for (double alpha = 360; alpha >= 0; alpha -= angleStep)
	{
		double x = r * cos(alpha * TORAD);
		double z = r * sin(alpha * TORAD);

		double s = s_center + texture_radius * cos(alpha * TORAD);
		double t = t_center + texture_radius * sin(alpha * TORAD);

		glTexCoord2d(s, t);
		glVertex3d(x, -height / 2, z);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(0.7, 0.7, 0.7);

	//Omotac
	glBegin(GL_QUAD_STRIP);

	for (double alpha = 0; alpha <= 360; alpha += angleStep)
	{
		double x = cos(alpha * TORAD);
		double z = sin(alpha * TORAD);

		//Bottom
		glNormal3d(x, -height / 2, z);
		glVertex3d(x * r, -height / 2, z * r);

		//Top
		glNormal3d(x, height / 2, z);
		glVertex3d(x * r, height / 2, z * r);
	}
	
	glEnd();
}

void CGLRenderer::DrawWheel()
{
	double radius = SQUARE_SIDE * 1.5;
	double height = SQUARE_SIDE;
	int segments = 16;

	glPushMatrix();
	glRotated(90, 1, 0, 0);
	DrawCylinder(radius, height, segments);
	glPopMatrix();
}

struct point_with_st {
	double x;
	double y;
	double z;
	double s;
	double t;
};

void DrawQuad(const point_with_st* pts, int a, int b, int c, int d, bool isReverse)
{
	glBegin(GL_QUADS);
	if (!isReverse)
	{
		glNormal3d(0, 0, 1);
		glTexCoord2d(pts[a].s, pts[a].t);
		glVertex3d(pts[a].x, pts[a].y, pts[a].z);
		glTexCoord2d(pts[b].s, pts[b].t);
		glVertex3d(pts[b].x, pts[b].y, pts[b].z);
		glTexCoord2d(pts[c].s, pts[c].t);
		glVertex3d(pts[c].x, pts[c].y, pts[c].z);
		glTexCoord2d(pts[d].s, pts[d].t);
		glVertex3d(pts[d].x, pts[d].y, pts[d].z);
	}
	else
	{
		glNormal3d(0, 0, -1);
		glTexCoord2d(pts[a].s, pts[a].t);
		glVertex3d(pts[a].x, pts[a].y, pts[a].z);
		glTexCoord2d(pts[d].s, pts[d].t);
		glVertex3d(pts[d].x, pts[d].y, pts[d].z);
		glTexCoord2d(pts[c].s, pts[c].t);
		glVertex3d(pts[c].x, pts[c].y, pts[c].z);
		glTexCoord2d(pts[b].s, pts[b].t);
		glVertex3d(pts[b].x, pts[b].y, pts[b].z);
	}
	glEnd();
}

void CGLRenderer::DrawTruckBody()
{
	double negativeX0 = -5.5 * SQUARE_SIDE;
	double negativeX1 = -4.5 * SQUARE_SIDE;
	double negativeX2 = -3.5 * SQUARE_SIDE;
	double negativeX3 = -2.5 * SQUARE_SIDE;
	double negativeX4 = -1.5 * SQUARE_SIDE;
	double negativeX5 = 1.5 * SQUARE_SIDE;

	double positiveX0 = 2.5 * SQUARE_SIDE;
	double positiveX1 = 3.5 * SQUARE_SIDE;
	double positiveX2 = 4.5 * SQUARE_SIDE;
	double positiveX3 = 5.5 * SQUARE_SIDE;

	double positiveZ = 3 * SQUARE_SIDE;
	double negativeZ = -3 * SQUARE_SIDE;

	double y0 = 0;
	double y1 = SQUARE_SIDE;
	double y2 = 2 * SQUARE_SIDE;
	double y3 = 3 * SQUARE_SIDE;
	double y4 = 5 * SQUARE_SIDE;
	double y5 = 7 * SQUARE_SIDE;


	glBindTexture(GL_TEXTURE_2D, 0);

	//Deo bez teksture - krenuvsi spreda od vetrobrana pa nagore i ukrug
	{
		glColor3f(1,1,1);
		glBegin(GL_QUADS);

		//Vetrobran
		glNormal3f(-1, 0, 0);
		glVertex3f(negativeX0, y0, negativeZ);
		glVertex3f(negativeX0, y0, positiveZ);
		glVertex3f(negativeX0, y4, positiveZ);
		glVertex3f(negativeX0, y4, negativeZ);

		//Celo
		glNormal3f(-1, 1, 0);
		glVertex3f(negativeX0, y4, negativeZ);
		glVertex3f(negativeX0, y4, positiveZ);
		glVertex3f(negativeX2, y5, positiveZ);
		glVertex3f(negativeX2, y5, negativeZ);

		//Glava
		glNormal3f(0, 1, 0);
		glVertex3f(negativeX2, y5, negativeZ);
		glVertex3f(negativeX2, y5, positiveZ);
		glVertex3f(negativeX4, y5, positiveZ);
		glVertex3f(negativeX4, y5, negativeZ);

		//Vrat
		glNormal3f(1, 0, 0);
		glVertex3f(negativeX4, y5, negativeZ);
		glVertex3f(negativeX4, y5, positiveZ);
		glVertex3f(negativeX4, y3, positiveZ);
		glVertex3f(negativeX4, y3, negativeZ);

		//Ledja
		glNormal3f(0, 1, 0);
		glVertex3f(negativeX4, y3, negativeZ);
		glVertex3f(negativeX4, y3, positiveZ);
		glVertex3f(positiveX3, y3, positiveZ);
		glVertex3f(positiveX3, y3, negativeZ);

		//Branik iza
		glNormal3f(1, 0, 0);
		glVertex3f(positiveX3, y3, positiveZ);
		glVertex3f(positiveX3, y3, negativeZ);
		glVertex3f(positiveX3, y0, negativeZ);
		glVertex3f(positiveX3, y0, positiveZ);

		//Auspuh
		glNormal3f(0, -1, 0);
		glVertex3f(positiveX3, y0, negativeZ);
		glVertex3f(positiveX3, y0, positiveZ);
		glVertex3f(positiveX2, y0, positiveZ);
		glVertex3f(positiveX2, y0, negativeZ);

		//Tocak zadnji deo 1
		glNormal3f(-1, 0, 0);
		glVertex3f(positiveX2, y0, negativeZ);
		glVertex3f(positiveX2, y0, positiveZ);
		glVertex3f(positiveX2, y1, positiveZ);
		glVertex3f(positiveX2, y1, negativeZ);

		//Tocak zadnji deo 2
		glNormal3f(-1, -1, 0);
		glVertex3f(positiveX2, y1, negativeZ);
		glVertex3f(positiveX2, y1, positiveZ);
		glVertex3f(positiveX1, y2, positiveZ);
		glVertex3f(positiveX1, y2, negativeZ);

		//Tocak zadnji deo 3
		glNormal3f(0, -1, 0);
		glVertex3f(positiveX1, y2, negativeZ);
		glVertex3f(positiveX1, y2, positiveZ);
		glVertex3f(positiveX0, y2, positiveZ);
		glVertex3f(positiveX0, y2, negativeZ);

		//Tocak zadnji deo 4
		glNormal3f(1, -1, 0);
		glVertex3f(positiveX0, y2, negativeZ);
		glVertex3f(positiveX0, y2, positiveZ);
		glVertex3f(negativeX5, y1, positiveZ);
		glVertex3f(negativeX5, y1, negativeZ);

		//Tocak zadnji deo 5
		glNormal3f(1, 0, 0);
		glVertex3f(negativeX5, y1, negativeZ);
		glVertex3f(negativeX5, y1, positiveZ);
		glVertex3f(negativeX5, y0, positiveZ);
		glVertex3f(negativeX5, y0, negativeZ);

		//Deo izmedju tockova
		glNormal3f(0, -1, 0);
		glVertex3f(negativeX5, y0, negativeZ);
		glVertex3f(negativeX5, y0, positiveZ);
		glVertex3f(negativeX4, y0, positiveZ);
		glVertex3f(negativeX4, y0, negativeZ);

		//Tocak prednji deo 1
		glNormal3f(-1, 0, 0);
		glVertex3f(negativeX4, y0, negativeZ);
		glVertex3f(negativeX4, y0, positiveZ);
		glVertex3f(negativeX4, y1, positiveZ);
		glVertex3f(negativeX4, y1, negativeZ);

		//Tocak prednji deo 2
		glNormal3f(-1, -1, 0);
		glVertex3f(negativeX4, y1, negativeZ);
		glVertex3f(negativeX4, y1, positiveZ);
		glVertex3f(negativeX3, y2, positiveZ);
		glVertex3f(negativeX3, y2, negativeZ);

		//Tocak prednji deo 3
		glNormal3f(0, -1, 0);
		glVertex3f(negativeX3, y2, negativeZ);
		glVertex3f(negativeX3, y2, positiveZ);
		glVertex3f(negativeX2, y2, positiveZ);
		glVertex3f(negativeX2, y2, negativeZ);

		//Tocak prednji deo 4
		glNormal3f(1, -1, 0);
		glVertex3f(negativeX2, y2, negativeZ);
		glVertex3f(negativeX2, y2, positiveZ);
		glVertex3f(negativeX1, y1, positiveZ);
		glVertex3f(negativeX1, y1, negativeZ);

		//Tocak prednji deo 5
		glNormal3f(1, 0, 0);
		glVertex3f(negativeX1, y1, negativeZ);
		glVertex3f(negativeX1, y1, positiveZ);
		glVertex3f(negativeX1, y0, positiveZ);
		glVertex3f(negativeX1, y0, negativeZ);

		//Prednji deo ispod vetrobrana
		glNormal3f(0, -1, 0);
		glVertex3f(negativeX1, y0, negativeZ);
		glVertex3f(negativeX1, y0, positiveZ);
		glVertex3f(negativeX0, y0, positiveZ);
		glVertex3f(negativeX0, y0, negativeZ);

		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, figureTextureID);
	
	//Leva i desna strana
	{
		glColor3f(1, 1, 1);

		point_with_st pts[] = {
			{negativeX0, y0, 0, 0.0 / 16, 7.0 / 16},
			{negativeX1, y0, 0, 1.0 / 16, 7.0 / 16},
			{negativeX1, y1, 0, 1.0 / 16, 6.0 / 16},
			{negativeX2, y2, 0, 2.0 / 16, 5.0 / 16},
			{negativeX3, y2, 0, 3.0 / 16, 5.0 / 16},
			{negativeX4, y1, 0, 4.0 / 16, 6.0 / 16},
			{negativeX4, y0, 0, 4.0 / 16, 7.0 / 16},
			{negativeX5, y0, 0, 7.0 / 16, 7.0 / 16},
			{negativeX5, y1, 0, 7.0 / 16, 6.0 / 16},
			{positiveX0, y2, 0, 8.0 / 16, 5.0 / 16},
			{positiveX1, y2, 0, 9.0 / 16, 5.0 / 16},
			{positiveX2, y1, 0, 10.0 / 16, 6.0 / 16},
			{positiveX2, y0, 0, 10.0 / 16, 7.0 / 16},
			{positiveX3, y0, 0, 11.0 / 16, 7.0 / 16},
			{positiveX3, y3, 0, 11.0 / 16, 4.0 / 16},
			{negativeX4, y3, 0, 4.0 / 16, 4.0 / 16},
			{negativeX4, y5, 0, 4.0 / 16, 0.0 / 16},
			{negativeX2, y5, 0, 2.0 / 16, 0.0 / 16},
			{negativeX0, y4, 0, 0.0 / 16, 2.0 / 16},
		};

		glPushMatrix();

		//Leva strana (gledamo otpozadi)
		glTranslatef(0, 0, positiveZ);
		{
			DrawQuad(pts, 0, 1, 2, 18, false);
			DrawQuad(pts, 2, 3, 17, 18, false);
			DrawQuad(pts, 3, 4, 16, 17, false);
			DrawQuad(pts, 4, 5, 15, 16, false);
			DrawQuad(pts, 5, 8, 9, 15, false);
			DrawQuad(pts, 5, 6, 7, 8, false);
			DrawQuad(pts, 9, 10, 14, 15, false);
			DrawQuad(pts, 10, 11, 13, 14, false);
			DrawQuad(pts, 11, 12, 13, 14, false);
		}

		glPopMatrix();
		glPushMatrix();

		//Desna strana
		glTranslatef(0, 0, negativeZ);
		{
			DrawQuad(pts, 0, 1, 2, 18, true);
			DrawQuad(pts, 2, 3, 17, 18, true);
			DrawQuad(pts, 3, 4, 16, 17, true);
			DrawQuad(pts, 4, 5, 15, 16, true);
			DrawQuad(pts, 5, 8, 9, 15, true);
			DrawQuad(pts, 5, 6, 7, 8, true);
			DrawQuad(pts, 9, 10, 14, 15, true);
			DrawQuad(pts, 10, 11, 13, 14, true);
			DrawQuad(pts, 11, 12, 13, 14, true);
		}

		glPopMatrix();
	}
}

void CGLRenderer::DrawFigure()
{
	double truck_depth = 6 * SQUARE_SIDE;
	double wheel_offset_z = 2 * SQUARE_SIDE;
	double wheel_offset_x_rear = 3 * SQUARE_SIDE;
	double wheel_offset_x_front = -3 * SQUARE_SIDE;
	double wheel_offset_y = 1.5 * SQUARE_SIDE;

	double ellipsoid_offset_x = 2 * SQUARE_SIDE;
	double ellipsoid_offset_y = 4.5 * SQUARE_SIDE + 2 * SQUARE_SIDE;

	glPushMatrix();

	{
		//Tocak zadnji levi (gledano otpozadi)
		glTranslatef(wheel_offset_x_rear, wheel_offset_y, wheel_offset_z);
		glRotatef(wheelRotationAngle, 0, 0, 1);
		DrawWheel();
		glRotatef(-wheelRotationAngle, 0, 0, 1);
		glTranslatef(-wheel_offset_x_rear, -wheel_offset_y, -wheel_offset_z);

		//Tocak zadnji desni
		glTranslatef(wheel_offset_x_rear, wheel_offset_y, -wheel_offset_z);
		glRotatef(wheelRotationAngle, 0, 0, 1);
		DrawWheel();
		glRotatef(-wheelRotationAngle, 0, 0, 1);
		glTranslatef(-wheel_offset_x_rear, -wheel_offset_y, wheel_offset_z);

		//Tocak prednji levi (gledano otpozadi idalje)
		glTranslatef(wheel_offset_x_front, wheel_offset_y, wheel_offset_z);
		glRotatef(wheelSteerAngle, 0, 1, 0);
		glRotatef(wheelRotationAngle, 0, 0, 1);
		DrawWheel();
		glRotatef(-wheelRotationAngle, 0, 0, 1);
		glRotatef(-wheelSteerAngle, 0, 1, 0);
		glTranslatef(-wheel_offset_x_front, -wheel_offset_y, -wheel_offset_z);

		//Tocak prednji desni
		glTranslatef(wheel_offset_x_front, wheel_offset_y, -wheel_offset_z);
		glRotatef(wheelSteerAngle, 0, 1, 0);
		glRotatef(wheelRotationAngle, 0, 0, 1);
		DrawWheel();
		glRotatef(-wheelRotationAngle, 0, 0, 1);
		glRotatef(-wheelSteerAngle, 0, 1, 0);
		glTranslatef(-wheel_offset_x_front, -wheel_offset_y, wheel_offset_z);
	}

	//Elipsoid
	glTranslatef(ellipsoid_offset_x, ellipsoid_offset_y, 0);
	glRotated(-90, 0, 1, 0);
	DrawEllipsoid();
	glRotated(90, 0, 1, 0);
	glTranslatef(-ellipsoid_offset_x, -ellipsoid_offset_y, 0);

	//Telo kamiona
	glTranslatef(0, wheel_offset_y, 0);
	DrawTruckBody();
	glTranslatef(0, -wheel_offset_y, 0);

	glPopMatrix();
}