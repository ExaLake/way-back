#include <GL/glut.h>
#include <stdlib.h>

const int numPoints = 10;

//make sure that knot vector is updated !!!
const int numKnots = numPoints + 4; 

GLUnurbsObj *theHead;

void *font = GLUT_BITMAP_8_BY_13;
GLfloat raster[2];
GLfloat position[2];
const int WINDOW_WIDTH = 500;

GLfloat white[3] = {1.0, 1.0, 1.0};
GLfloat red[3] = {1.0, 0.0, 0.0};
GLfloat green[3] = {0.0, 1.0, 0.0};
GLfloat blue[3] = {0.0, 0.0, 1.0};
GLfloat grey[3] = {0.5, 0.5, 0.5};

GLfloat points[numPoints][3] = {
		{0.0, 1.0, 0.0},	//1
		{-0.5, 0.3, 0.0},	//2
		{-1.0, -0.2, 0.0},	//3
		{-1.0, -0.5, 0.0},	//4
		{-0.5, -0.4, 0.0},	//5
		{-0.2, 0.2, 0.0},	//6

		{0.15, -0.3, 0.0},	//7
		{0.2, -0.4, 0.0},	//8
		{0.17, -0.65, 0.0},	//9
		{0.2, -0.75, 0.0}	//10
	};
	
GLfloat knots[numKnots] = {0, 1, 2, 3, 4, 5, 5, 5, 5,
						6 ,7, 8, 9, 10};

void
printString(GLfloat *position, char *string)
{
  int len, i;

  glRasterPos2fv(position);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}

void init(void)	{
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_POINT_SMOOTH_HINT, 10);
}

void drawHull(void)	{
	int i;
	
	glDisable(GL_LINE_SMOOTH);
	glLineWidth(1.2);
	glColor3f(0.9, 0.9, 0.1); //hull color
	glBegin(GL_LINE_STRIP);
	for (i=0; i<numPoints; i++)	{
		glVertex3fv(&points[i][0]);
	}
	glEnd();

	glColor3f(0.5, 0.7, 0.5); // points color
	glPointSize(5.0);
	glBegin(GL_POINTS);
	for (i=0; i<numPoints; i++)	{
		glVertex3fv(&points[i][0]);
	}
	glEnd();
}

void drawHead(void)	{
	glEnable(GL_LINE_SMOOTH);

	theHead = gluNewNurbsRenderer();
	gluNurbsProperty(theHead, GLU_DISPLAY_MODE, GLU_FILL);
	gluNurbsProperty(theHead, GLU_SAMPLING_TOLERANCE, 1.0);
	glLineWidth(2.0);
	glColor3f(0.0, 0.0, 1.0);
	gluBeginCurve(theHead);
	gluNurbsCurve(theHead, numKnots, knots, 3, &points[0][0], 4, GL_MAP1_VERTEX_3);
	gluEndCurve(theHead);
	gluDeleteNurbsRenderer(theHead);

}

void drawAxes(void)	{
	int i;
	glDisable(GL_LINE_SMOOTH);
	glLineWidth(1.0);

	glColor3fv(grey);
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
		glVertex3f(-1.2, 0.0, 0.0);
		glVertex3f(1.2, 0.0, 0.0);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
		glVertex3f(0.0, -0.8, 0.0);
		glVertex3f(0.0, 1.2, 0.0);
	glEnd();

	//draw grid marks
	for (i=-12; i<=12; i++)	{
		glBegin(GL_LINE_STRIP);
		glVertex3f((float) i/10, 0.0, 0.0);
		glVertex3f((float)i/10, 0.01, 0.0);
		glEnd();
	}
	for (i=-8; i<=12; i++)	{
		glBegin(GL_LINE_STRIP);
		glVertex3f(0.0, (float)i/10, 0.0);
		glVertex3f(0.01, (float)i/10 , 0.0);
		glEnd();
	}
	
	// draw axes related text
	glPopMatrix();
	position[0] = raster[0] + 1.15;
	position[1] = raster[1] - 0.05;
	glColor3fv(white);
	printString(position, "x");

	position[0] = raster[0] + 0.95;
	position[1] = raster[1] + 0.02;
	glColor3fv(grey);
	printString(position, "1.0");

	position[0] = raster[0] + 0.02;
	position[1] = raster[1] + 1.0;
	glColor3fv(grey);
	printString(position, "1.0");

	position[0] = raster[0] + 0.45;
	position[1] = raster[1] + 0.02;
	glColor3fv(grey);
	printString(position, "0.5");

	position[0] = raster[0] + 0.02;
	position[1] = raster[1] + 0.5;
	glColor3fv(grey);
	printString(position, "0.5");

	position[0] = raster[0] + 0.02;
	position[1] = raster[1] + 1.15;
	glColor3fv(white);
	printString(position, "y");

	position[0] = raster[0] -0.22;
	position[1] = raster[1] + 0.22;
	glColor3fv(red);
	printString(position, "P5");

	glPopMatrix();
	glEnable(GL_LINE_SMOOTH);

}

void display(void)
{
 
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glGetFloatv(GL_CURRENT_RASTER_POSITION, raster);


  glPushMatrix();

  
  
  glPushMatrix();

  glColor3fv(white);
  position[0] = raster[0] - 1.0;
  position[1] = raster[1] + 1.0;
  printString(position, "Quadruple knot t5");

  position[0] = raster[0] -1.0;
  position[1] = raster[1] - 1.0;
  glColor3fv(blue);
  printString(position, "KNOT VECTOR: [0,1,2,3,4,5,5,5,5,6,7,8,9,10]");

  glPopMatrix();
   
  drawHull();
  drawHead();
  drawAxes();
  
  glPopMatrix();
  
  
  glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   //glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
   gluPerspective(45.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 0.0, -3.0);
}

int main()
{
   //glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
   glutInitWindowSize (WINDOW_WIDTH,WINDOW_WIDTH); 
   glutInitWindowPosition (100, 50);
   glutCreateWindow ("B-Splines");

	init();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}
