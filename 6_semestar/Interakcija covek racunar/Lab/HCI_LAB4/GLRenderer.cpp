#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"

CGLRenderer::CGLRenderer(void)
{
	
}

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
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	DrawScene();
	//---------------------------------
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(m_x, m_y, -3.0 + m_z);

	glRotatef(m_Rx, 1.0, 0.0, 0.0);
	glRotatef(m_Ry, 0.0, 1.0, 0.0);

	glPushMatrix();
	//-------------------------------------

	glLoadName(1); //Load-ujem crvenu kocku u stek imena
	glColor3f(1.0, 0, 0);
	glutSolidCube(1.0);

	glTranslatef(1.0, 0.0, -1.0);
	glLoadName(2); //Load-ujem zelenu kocku u stek imena
	glColor3f(0, 1.0, 0);
	glutSolidCube(1.0);

	glTranslatef(-2.0, 0.0, 0.0);
	glLoadName(3); //Load-ujem plavu kocku u stek imena
	glColor3f(0, 0, 1.0);
	glutSolidCube(1.0);

	glTranslatef(1.0, 0.0, -1.0);
	glLoadName(4); //Load-ujem zutu kocku u stek imena
	glColor3f(1.0, 1.0, 0);
	glutSolidCube(1.0);

	glTranslatef(1.0, 0.0, -1.0);
	glPushName(5); //Push-ujem ljubicastu kocku, ne load-ujem da bi i prethodna zuta ostala na steku i ova nova je sad unutar nje logicki
	glColor3f(1.0, 0.0, 1.0);
	glutSolidCube(0.5);
	glPopName();//Brisem ljubicastu kocku

	//-------------------------------------

	glPopMatrix();

	glFlush();
	
}
void CGLRenderer::Reshape(CDC *pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	m_aspect = (float)w / (float)h;
	gluPerspective(40, m_aspect, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC *pDC)
{
	//wglMakeCurrent(pDC->m_hDC, m_hrc);
	wglMakeCurrent(NULL,NULL); 
	if(m_hrc) 
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

void CGLRenderer::PickObject(CDC *pDC, int x, int y, unsigned int* a)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	GLint viewport[4];
	GLuint selectBuf[512];

	glSelectBuffer(512, selectBuf);
	glRenderMode(GL_SELECT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glGetIntegerv(GL_VIEWPORT, viewport);
	gluPickMatrix(x, viewport[3] - y, 3, 3, viewport);
	//-----------------------------
	gluPerspective(40.0, m_aspect, 0.1, 100.0);
	//-----------------------------
	glMatrixMode(GL_MODELVIEW);
	glInitNames();
	glPushName(0);
	DrawScene();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();

	int hits = glRenderMode(GL_RENDER);
	unsigned int retVal = 0;
	
	GLuint resultIDs[2]; //rezultat processhits-a ce biti ovde smesten

	if (hits != 0)
	{
		ProcessHits(hits, selectBuf, resultIDs);
		a[0] = resultIDs[0];
		a[1] = resultIDs[1];
	}
	else
	{
		a[0] = 0;
		a[1] = 0;
	}

	//---------------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::ProcessHits(GLint hits, GLuint* buffer, GLuint* ids) {
	GLuint* ptr = buffer;
	GLuint minZ = 0xFFFFFFFF; // poredimo minZ sa ovim za pocetak da bismo odredili najblizi objekat korisniku tj kameri
	GLuint najbliziIds[2] = { 0, 0 }; // vracam najvise 2 imena najdublja jer u zadatku imamo ljubicastu u zutoj dakle 2

	for (int i = 0; i < hits; ++i) {
		GLuint names = *ptr++;// broj imena ovog ulaza i onda preskacem na minZ
		GLuint z1 = *ptr++;// minZ trenutni i onda preskacem na maxZ
		ptr++;// preskacemo maxZ

		if (z1 < minZ && names > 0) { //Ovde odredjujemo da li selekcija ima nekog objekta u steku imena uopste i da li je najblizi kameri
			minZ = z1;

			if (names == 1) {
				najbliziIds[0] = 0;// nema roditelja pa stavljam 0
				najbliziIds[1] = ptr[0];// samo jedan objekat to su plava crvena zuta zelena kocka
			}
			else {
				najbliziIds[0] = ptr[names-2];// pretposlednji na stacku je direktni roditelj pa je ovde zuta kocka ako kliknemo na ljubicastu
				najbliziIds[1] = ptr[names-1];// poslednji objekat je dete pa je to sama ljubicasta kocka
			}
		}

		ptr += names; // idemo na sledeci hit tj ulaz u buffer
	}

	ids[0] = najbliziIds[0];
	ids[1] = najbliziIds[1];
}
