#include<Windows.h>
#include<GL\glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int Window,fullscreen=1,phasestep=1;
unsigned long int phase=0;
int choice;
int smooth=0;
GLfloat theta[] = {0.0,0.0,0.0};
int r=-50;
float move;
int axis,dir=1;
float z=1;
#define MAX 300
double rpl[MAX][MAX][3];
double nrm[MAX][MAX][3];
double stp=1.0;
void fnc()
{
	int i,j;
	double x,y,z,w;
	w=-MAX*stp/2.0;
	for (i=0;i<MAX;i++)
	{
		y=w+(double)i*stp;
		for (j=0;j<MAX;j++)
		{
			x=w+(double)j*stp;
			z=2.0*sin((x*x+y*y-phase)/100.0);
			rpl[i][j][0]=x;
			rpl[i][j][1]=y;
			rpl[i][j][2]=z;
		}
	}
}
void normal()
{
	int i,j;
	double x,y,w,v;
	w=-MAX*stp/2.0;
	for (i=0;i<MAX;i++)
	{
		y=w+(double)i*stp;
		for (j=0;j<MAX;j++)
		{
			x=w+(double)j*stp;
			v=4.0*cos((x*x+y*y-phase)/100.0)/100.0;
			nrm[i][j][0]=x*v;
			nrm[i][j][1]=y*v;
			nrm[i][j][2]=-1;
		}
	}
}
void output(int x, int y, char *string)      
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
}
void draw1()
{
	int i,j;
	for (i=0;i<MAX-1;i++) for (j=0;j<MAX-1;j++)
	{
		glBegin(GL_QUADS);
		glNormal3dv(nrm[i][j]);
		glVertex3dv(rpl[i][j]);
		glNormal3dv(nrm[i][j+1]);
		glVertex3dv(rpl[i][j+1]);
		glNormal3dv(nrm[i+1][j+1]);
		glVertex3dv(rpl[i+1][j+1]);
		glNormal3dv(nrm[i+1][j]);
		glVertex3dv(rpl[i+1][j]);
		glEnd();
	}
}
void moon()
{
	glRotatef(-20.0, 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(3.0, -25.0, -1.0);
	glutSolidSphere(5, 40, 40);
	glPopMatrix();
}
void stars()
{
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2i(20,-20);
	glVertex2i(-20,-20);
	glVertex2i(-30,-30);
	glVertex2i(-50,-15);
	glVertex2i(15,-35);
	glVertex2i(40,-40);
	glVertex2i(-45,-40);
	glVertex2i(55,-30);
	glVertex2i(-55,-30);
	glVertex2i(0,-30);
	glVertex2i(5,-10);
	glEnd();
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex2i(20,-10);
	glVertex2i(-30,-20);
	glVertex2i(-35,-30);
	glVertex2i(-55,-15);
	glVertex2i(15,-20);
	glVertex2i(40,-45);
	glVertex2i(-40,-40);
	glVertex2i(55,-20);
	glVertex2i(-50,-20);
	glVertex2i(0,-30);
	glVertex2i(5,-10);
	glVertex2i(-30,-30);
	glVertex2i(-22,-40);
	glVertex2i(3,-3);
	glVertex2i(-40,-0);
	glVertex2i(-10,0);
	glEnd();
}


void land()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);
	glColor3f(0.9,0.6,0.0);
	glBegin(GL_QUADS);
	glVertex2i(-5,50);
	glVertex2i(10,28);
	glVertex2i(20,20);
	glVertex2i(20,50);
	glVertex2i(20,50);
	glVertex2i(20,20);
	glVertex2i(40,5);
	glVertex2i(40,50);
	glVertex2i(40,50);
	glVertex2i(40,5);
	glVertex2i(53,0);
	glVertex2i(53,50);
	glVertex2i(53,50);
	glVertex2i(53,0);
	glVertex2i(75,-3);
	glVertex2i(75,50);
	glEnd();
}
void display1()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	land();
	glColor3f(1,1,1);
	stars();
	if(choice==1)
	{
		glColor3f(0,1,1);
		output(-60,-43,"HIGH TIDES");
		output(-60,-38,"The Gravitational Pull of the Moon and Earth");
		output(-60,-33,"causes High Tides (Tidal bulge) in the Ocean!");
		glColor3f(1,1,1);
		moon();
	}
	else if(choice==2)
	{
		glColor3f(0,1,1);
		output(-60,-40,"LOW TIDES");
		output(-60,-35,"The absence of the Moon");
		output(-60,-30,"causes Low Tides in the Ocean!");
		glColor3f(0,0,0);
		moon();
	}
	glColor3f(1,1,1);
	glBegin(GL_POINTS);
	glVertex2i(10,500);
	glVertex2i(10,500);
	glVertex2i(10,500);
	glVertex2i(10,500);
	glVertex2i(10,500);
	glVertex2i(10,500);
	glVertex2i(10,500);
	glVertex2i(10,500);
	glVertex2i(10,500);
	glEnd();
	glTranslatef(move,0,0);
	glTranslatef(0,33,0);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glPopMatrix();
	glPopAttrib();
	GLfloat Unlit[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat Material1Diffuse[] = {0.28, 0.46, 1.0, 1.0};
	GLfloat Material1Specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat Material1Shininess[] = {20.0};
	static GLfloat a=0.0;
	a++;
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,Material1Diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Material1Specular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,Material1Shininess);
	glPushMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glTranslatef(move,0,0);
	fnc();
	normal();
	draw1();
	glDisable(GL_LIGHTING);
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w,int h)
{
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(1.33*(-50.0),1.33*50.0,50.0,-50.0,-100.0,100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void mouse(int btn, int state, int x, int y)
{
	theta[0]=0.0;
	theta[1]=0.0;
	theta[2]=0.0;
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		z++;
		phasestep++;
		move+=1;
	}
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		z=1;
		phasestep=1;
	}
}
void KeyInp(unsigned char key,int x,int y)
{
	if (key==27)
	{
		glutDestroyWindow(Window);
		exit(0);
		}
	if (key=='m')
		move+=1;
	if (key=='n')
		move-=1;
}
void SpKeyInp(int key,int x,int y)
{
}
void Idle()
{
	if( dir==1)
	{
		theta[2] += 0.1*z;
		if(theta[2]>3)
		dir=0;
	}
	if( dir==0)
	{
		theta[2] -= 0.1*z;
		if(theta[2]<-3)
		dir=1;
	 }
	if( theta[2]>3)
		theta[2] -= 0.1*z;
	if( theta[2]<-3)
		theta[2] += 0.1*z;
	if( dir==1)
	{
		theta[0] += 0.1*z;
		if(theta[0]>3)
		dir=0;
	}
	if( dir==0)
	{
		theta[0] -= 0.1*z;
		if(theta[0]<-3)
		dir=1;
	}
	if( theta[0]>3)
		theta[0] -= 0.1*z;
	if( theta[0]<-3)
		theta[0] += 0.1*z;
	phase+=phasestep;
	glutPostRedisplay();
}

void init(void)
{
	int a;
	char *c2,c[]=".\\";
	GLfloat Light1Position[] = {0, 0, 290.0, 1.0};
	GLfloat Light2Position[] = {0, 0, -290.0, 1.0};
	GLfloat LightAmbient[] = {0.1, 0.1, 0.1, 1.0};
	GLfloat LightDiffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat LightSpecular[] = {1, 1, 1, 1.0};
	GLfloat Light1Shininess[] = {90.0};
	GLfloat Light2Shininess[] = {90.0};
	a=1;
	c2=c;
	glutInit(&a,&c2);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Tides");
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	Window=glutGetWindow();
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT,GL_DONT_CARE);
	glLineWidth(1.1);
	reshape(640,480);
	glLightfv(GL_LIGHT0, GL_POSITION, Light1Position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_SHININESS, Light1Shininess);
	glLightfv(GL_LIGHT1, GL_POSITION, Light2Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT1, GL_SHININESS, Light2Shininess);
	if(choice==1)
		glTranslatef(0,32,0);
	else if (choice==2)
		glTranslatef(0,45,0);
	glRotatef(80, 1.0, 0.0, 0.0);
	glRotatef(0, 0.0, 1.0, 0.0);
	glRotatef(0, 0.0, 0.0, 1.0);
	glutDisplayFunc(display1);
	glutMouseFunc(mouse);
	glutKeyboardFunc(KeyInp);
	glutSpecialFunc(SpKeyInp);
	glutIdleFunc(Idle);
}

void display()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	output(300,650,"OpenGl");
	output(250,550,"MINI PROJECT ON");
	output(230,500,"Simulation Of Ocean Tides");
	output(400,450,"By:");
	output(400,420,"Zainab Noorain");
	glColor3f(0,0,1);
	output(50,300,"RIGHT CLICK TO VIEW THE ANIMATION OF TIDES!");
	output(150,260,"SELECT EXIT OPTION TO EXIT");
	glFlush();
	glutSwapBuffers();
}

void menu(int ch)
{
	choice=ch;
	switch(ch)
	{
	case 1:
		init();
		break;
	case 2:
		init();
		break;
	case 3:
		exit(0);
		break;

	}

}

int main(int argc, char **argv)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700,700);
	glutCreateWindow("Simulation of Ocean Tides");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,700,0,700);
	glutCreateMenu(menu);
	glutAddMenuEntry("High Tides",1);	
	glutAddMenuEntry("Low Tides",2);
	glutAddMenuEntry("Exit",3);
	glutDisplayFunc(display);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}




