//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TOpenGLPanel"
#pragma resource "*.dfm"
TForm1 *Form1;

#define glRGB(x, y, z)	glColor3ub((GLubyte)x, (GLubyte)y, (GLubyte)z)


// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

static int angle = 60;
static float unknown = 1.0;
static depth = 400;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OpenGLPanel1Paint(TObject *Sender)
{
    resize();
 glClear(GL_COLOR_BUFFER_BIT);
 	float fZ,bZ;

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	fZ = 100.0f;
	bZ = -100.0f;

	// Save the matrix state and do the rotations
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, -300.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 1.0f);
    //glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	//glRotatef(yRot, 0.0f, 1.0f, 0.0f);


	// Nose Cone /////////////////////////////
	// Set material color, Red
	glRGB(255, 0, 0);

	// Front Face ///////////////////////////////////
	glBegin(GL_QUADS);
		// Pointing straight out Z
		glNormal3f(0.0f, 0.0f, 1.0f);

		// Left Panel
		glVertex3f(-50.0f, 50.0f, fZ);
		glVertex3f(-50.0f, -50.0f, fZ);
		glVertex3f(-35.0f, -50.0f, fZ);
		glVertex3f(-35.0f,50.0f,fZ);

		// Right Panel
		glVertex3f(50.0f, 50.0f, fZ);
		glVertex3f(35.0f, 50.0f, fZ);
		glVertex3f(35.0f, -50.0f, fZ);
		glVertex3f(50.0f,-50.0f,fZ);

		// Top Panel
		glVertex3f(-35.0f, 50.0f, fZ);
		glVertex3f(-35.0f, 35.0f, fZ);
		glVertex3f(35.0f, 35.0f, fZ);
		glVertex3f(35.0f, 50.0f,fZ);

		// Bottom Panel
		glVertex3f(-35.0f, -35.0f, fZ);
		glVertex3f(-35.0f, -50.0f, fZ);
		glVertex3f(35.0f, -50.0f, fZ);
		glVertex3f(35.0f, -35.0f,fZ);

		// Top length section ////////////////////////////
		// Normal points up Y axis
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-50.0f, 50.0f, fZ);
		glVertex3f(50.0f, 50.0f, fZ);
		glVertex3f(50.0f, 50.0f, bZ);
		glVertex3f(-50.0f,50.0f,bZ);

		// Bottom section
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-50.0f, -50.0f, fZ);
		glVertex3f(-50.0f, -50.0f, bZ);
		glVertex3f(50.0f, -50.0f, bZ);
		glVertex3f(50.0f, -50.0f, fZ);

		// Left section
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(50.0f, 50.0f, fZ);
		glVertex3f(50.0f, -50.0f, fZ);
		glVertex3f(50.0f, -50.0f, bZ);
		glVertex3f(50.0f, 50.0f, bZ);

		// Right Section
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-50.0f, 50.0f, fZ);
		glVertex3f(-50.0f, 50.0f, bZ);
		glVertex3f(-50.0f, -50.0f, bZ);
		glVertex3f(-50.0f, -50.0f, fZ);
	glEnd();


	glFrontFace(GL_CW);		// clock-wise polygons face out

	glBegin(GL_QUADS);
		// Back section
		// Pointing straight out Z
		glNormal3f(0.0f, 0.0f, -1.0f);

		// Left Panel
		glVertex3f(-50.0f, 50.0f, bZ);
		glVertex3f(-50.0f, -50.0f, bZ);
		glVertex3f(-35.0f, -50.0f, bZ);
		glVertex3f(-35.0f,50.0f,bZ);

		// Right Panel
		glVertex3f(50.0f, 50.0f, bZ);
		glVertex3f(35.0f, 50.0f, bZ);
		glVertex3f(35.0f, -50.0f, bZ);
		glVertex3f(50.0f,-50.0f,bZ);

		// Top Panel
		glVertex3f(-35.0f, 50.0f, bZ);
		glVertex3f(-35.0f, 35.0f, bZ);
		glVertex3f(35.0f, 35.0f, bZ);
		glVertex3f(35.0f, 50.0f,bZ);

		// Bottom Panel
		glVertex3f(-35.0f, -35.0f, bZ);
		glVertex3f(-35.0f, -50.0f, bZ);
		glVertex3f(35.0f, -50.0f, bZ);
		glVertex3f(35.0f, -35.0f,bZ);

	// Insides /////////////////////////////
		// Normal points up Y axis
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-35.0f, 35.0f, fZ);
		glVertex3f(35.0f, 35.0f, fZ);
		glVertex3f(35.0f, 35.0f, bZ);
		glVertex3f(-35.0f,35.0f,bZ);

		// Bottom section
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-35.0f, -35.0f, fZ);
		glVertex3f(-35.0f, -35.0f, bZ);
		glVertex3f(35.0f, -35.0f, bZ);
		glVertex3f(35.0f, -35.0f, fZ);

		// Left section
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-35.0f, 35.0f, fZ);
		glVertex3f(-35.0f, 35.0f, bZ);
		glVertex3f(-35.0f, -35.0f, bZ);
		glVertex3f(-35.0f, -35.0f, fZ);

		// Right Section
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(35.0f, 35.0f, fZ);
		glVertex3f(35.0f, -35.0f, fZ);
		glVertex3f(35.0f, -35.0f, bZ);
		glVertex3f(35.0f, 35.0f, bZ);
	glEnd();


	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out

	// Restore the matrix state
	glPopMatrix();	// Modelview matrix

	// Flush drawing commands
	glFlush();

}
//---------------------------------------------------------------------------
void TForm1::resize()
{
	GLfloat fAspect;
    int h = OpenGLPanel1->Height;
    int w = OpenGLPanel1->Width;

	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);

	fAspect = (GLfloat)w/(GLfloat)h;

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Produce the perspective projection
    gluPerspective(angle, fAspect, unknown, depth);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void __fastcall TForm1::OpenGLPanel1Resize(TObject *Sender)
{
    resize();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OpenGLPanel1Init(TObject *Sender)
{
	// Light values and coordinates
	GLfloat  whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
	GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat	 lightPos[] = { -50.f, 25.0f, 250.0f, 0.0f };

	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	// Enable lighting
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
	glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Black blue background
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f );

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    yRot ++;
    OpenGLPanel1->Repaint()  ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
angle  -= 5;
OpenGLPanel1->Repaint()  ;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
angle  += 5 ;
OpenGLPanel1->Repaint()  ;
}
//---------------------------------------------------------------------------

