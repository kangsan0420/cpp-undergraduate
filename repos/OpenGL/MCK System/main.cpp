#include <GL/freeglut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <math.h>

void MyInit(void);
void MyLightInit(void);
void MyDisplay(void);
void MyIdle(void);
void unProject(GLint X, GLint Y);
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y);
void MyMouseMove(GLint X, GLint Y);
void MyMouseWheel(GLint Button, GLint dir, GLint X, GLint Y);
void MyKey(unsigned char keyp, int x, int y);
void MyReshape(GLint NewWidth, GLint NewHeight);

void MyCube(float x, float y, float z, float w, float d, float h);
void MyInvCube(float x, float y, float z, float w, float h, float d);
void MyDrawSurface(void);
void MyDrawSphere(void);
void MyDrawLines(void);
void MyInitSphere(void);

void MyPhysics(void);
float MyClamp(float a);
GLfloat* myNormal(GLfloat* a, GLfloat* b, GLfloat* c);

unsigned long int my_time = 0;
int angle = 40;
float camR = 50, camXr = 30 * 3.14 / 180., camZr = 60 * 3.14 / 180.; // 거리, rad, rad
int rangeX = 12, rangeY = 12;

GLfloat zCursor, winX, winY;
GLboolean LmouseON = 0, RmouseON = 0, surface = true, Pause = false, boolLight = true, flat = false;
int mouseX, mouseY;
GLdouble unMouse[3];
GLdouble projection[16];
GLdouble modelView[16];
GLint viewPort[4];
GLint fidxi, fidxj;

GLfloat ambientLight[4] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat diffuseLight[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specular[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specref[4] = { 0.1, 0.1, 0.2, 1.0 };
GLfloat lightPos[4] = { 0, 0, 0, 1.0 };
GLfloat myMaterial[4] = { 0.25, 0.25, 0.45, 1.0 };


const int numi = 20, numj = 20;
#define Cloth // or spring

#define UP 0b00101010	//	0b abcdefgh
#define LU 0b00001010	//	    |
#define LL 0b10001010	//	    V
#define LD 0b10000010	//	  b a h
#define DD 0b10100010	//	  c   g
#define RD 0b10100000	//	  d e f
#define RR 0b10101000   //	    |
#define RU 0b00101000	//	    V
#define CC 0b10101010	//	 a == 1 : connected

const char connected[20][20] = {
	LU, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, RU,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LL, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, RR,
	LD, DD, DD, DD, DD, DD, DD, DD, DD, DD, DD, DD, DD, DD, DD, DD, DD, DD, DD, RD
};

const bool fixed[20][20] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

float MyClamp(float a) {
	if (a >= 255) a = 255;
	else if (a <= 0) a = 0;
	return a;
}

class phy {//=========================================================================
public:
	GLint iter = 30;
	float dt = 0.035 / (float)iter; // s
	float m = 0.0001; // kg
	float c = 0.001; // kg/s
	float c_air = 0.000025; //air damping
	float k = 0.07; // N/m
	float g = 9.81; // m/s^2
	float interval = 1.2;

	float p[3] = {};
	float v[3] = {};
	float a[3] = {};
	float z[3] = {};

	bool Clicked = 0;

	void MyDrawSphere(void) {
		glPushMatrix();
		glTranslatef(p[0], p[1], p[2]);
		if (Clicked) glColor3ub(128, 188, 230);
		glutSolidSphere(0.2, 15, 15);
		glPopMatrix();
	}

	float MyDist(float* a, float* b) {
		return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2) + pow(a[2] - b[2], 2));
	}
	float MyDist(double* a, float* b) {
		return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2) + pow(a[2] - b[2], 2));
	}

	void calVP(void) {
		for (int i = 0; i < 3; i++) {
			v[i] += dt * a[i];
			p[i] += dt * v[i];
		}
	}

	void MyForce(phy pd, float dist) {
		float dp = MyDist(p, pd.p);
		for (int i = 0; i < 3; i++) {
#ifdef Cloth
			if (dp > dist) {
				a[i] += k * (dp - dist) / dp * (pd.p[i] - p[i]) / m; // spring force
				a[i] += c * (pd.v[i] - v[i]) / m; // damping force
			}
#else
			a[i] += k * (dp - dist) / dp * (pd.p[i] - p[i]) / m; // spring force
			a[i] += c * (pd.v[i] - v[i]) / m; // damping force
#endif
			a[i] -= c_air * pd.v[i] / m; // air damping force
		}
		if (Clicked) {
			float dp = MyDist(unMouse, p);
			for (int i = 0; i < 3; i++) {
				a[i] += 0.05 * (unMouse[i] - p[i]) / m; // mouse force
			}
		}
	}
}sp[numi][numj]; // class initalize ==================================================

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1200, 1000);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("mck system");
	glMatrixMode(GL_MODELVIEW);
	MyInitSphere();
	MyInit();
	MyLightInit();
	glutDisplayFunc(MyDisplay);
	glutIdleFunc(MyIdle);
	glutMouseFunc(MyMouseClick);
	glutKeyboardFunc(MyKey);
	glutMotionFunc(MyMouseMove);
	glutMouseWheelFunc(MyMouseWheel);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	return 0;
}

void MyInit() {
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void MyLightInit() {
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING); // 빛을 사용한다.

	glEnable(GL_LIGHT0); // 0번빛을 사용한다.
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glMaterialfv(GL_FRONT, GL_AMBIENT, myMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, myMaterial);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	//glMateriali(GL_FRONT, GL_SHININESS, 128);
}

void MyDisplay() {
	glLoadIdentity();
	gluPerspective(angle, 1, 0.1, 1000);
	gluLookAt(camR * sin(camZr) * cos(camXr), camR * sin(camZr) * sin(camXr), camR * cos(camZr), 0, 0, 0, 0, 0, sin(camZr));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1, 0.1, 0.15, 1);
	for (int it = 0; it < sp[0][0].iter; it++) {
		MyPhysics();
	}
	//MyInvCube(0, 0, 0, 50, 50, 50);
	glPushMatrix();
	glTranslatef(25, -25, 25);
	glutWireSphere(0.5, 5, 5);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glPopMatrix();
	if (surface) {
		MyDrawSurface();
	}
	else {
		MyDrawSphere();
	}
	if (boolLight == false) MyDrawLines();
	glFlush();
	glutSwapBuffers();
}

void MyIdle() {
	my_time += 1;
	glutPostRedisplay();
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		LmouseON = 1;
		mouseX = X;
		mouseY = Y;
		unProject(mouseX, mouseY);
		printf("%.2f\t%.2f\t%.2f\n", unMouse[0], unMouse[1], unMouse[2]);
		for (int i = 0; i < numi; i++)
			for (int j = 0; j < numj; j++)
				if (sp[i][j].MyDist(unMouse, sp[i][j].p) < 0.6) {
					sp[i][j].Clicked = 1;
					fidxi = i;
					fidxj = j;
				}
	}
	else if (Button == GLUT_LEFT_BUTTON && State == GLUT_UP) {
		LmouseON = 0;
		for (int i = 0; i < numi; i++)
			for (int j = 0; j < numj; j++)
				sp[i][j].Clicked = 0;
	}
	if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN) {
		RmouseON = 1;
		mouseX = X;
		mouseY = Y;
	}
	if (Button == GLUT_RIGHT_BUTTON && State == GLUT_UP) {
		RmouseON = 0;
	}
	glutPostRedisplay();
}
void MyMouseMove(GLint X, GLint Y) {
	if (LmouseON && (!RmouseON)) {
		glGetDoublev(GL_PROJECTION_MATRIX, projection);
		glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
		glGetIntegerv(GL_VIEWPORT, viewPort);

		winX = (float)X;
		winY = (float)viewPort[3] - (float)Y;
		gluUnProject(winX, winY, zCursor, modelView, projection, viewPort, &unMouse[0], &unMouse[1], &unMouse[2]);
	}
	if (RmouseON) {
		camXr += 0.004 * (X - mouseX);
		camZr += 0.004 * (Y - mouseY);
		mouseX = X;
		mouseY = Y;
	}
	glutPostRedisplay();
}

void MyMouseWheel(GLint Button, GLint dir, GLint X, GLint Y) {
	if (dir > 0) {
		camR -= 2;
	}
	else {
		camR += 2;
	}
}

void unProject(GLint X, GLint Y)
{
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetIntegerv(GL_VIEWPORT, viewPort);

	winX = (float)X;
	winY = (float)viewPort[3] - (float)Y;
	glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor);
	gluUnProject(winX, winY, zCursor, modelView, projection, viewPort, &unMouse[0], &unMouse[1], &unMouse[2]);
}

void MyKey(unsigned char keyp, int x, int y) {
	switch (keyp) {
	case 'a':
		angle -= 5;
		printf("angle : %d\n", angle);
		break;
	case 'd':
		angle += 5;
		printf("angle : %d\n", angle);
		break;
	case 'r':
		angle = 40;
		camR = 50;
		camXr = 30 * 3.14 / 180.;
		camZr = 60 * 3.14 / 180.;
		break;
	case 'g':
		surface = !surface;
		break;
	case 'p':
		Pause = !Pause;
		break;
	case 'f':
		if (flat == true) {
			glEnable(GL_SMOOTH);
			flat = false;
		}
		else {
			glEnable(GL_FLAT);
			flat = true;
		}
		break;
	case '1':
		if (boolLight == true) {
			glDisable(GL_LIGHTING);
			boolLight = false;
		}
		else {
			glEnable(GL_LIGHTING);
			boolLight = true;
		}
		break;
	case 27:
		glutDestroyWindow(glutGetWindow());
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void MyReshape(GLint NewWidth, GLint NewHeight) {
}

void MyCube(float x, float y, float z, float w, float h, float d) {
	glBegin(GL_QUADS);
	glColor3ub(255, 100, 100);//x red
	glVertex3f(x + 0.5 * w, y + 0.5 * h, z - 0.5 * d);
	glVertex3f(x + 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	glVertex3f(x + 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	glVertex3f(x + 0.5 * w, y - 0.5 * h, z - 0.5 * d);
	glColor3ub(100, 255, 100);//-x green
	glVertex3f(x - 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y + 0.5 * h, z - 0.5 * d);
	glVertex3f(x - 0.5 * w, y - 0.5 * h, z - 0.5 * d);
	glColor3ub(100, 100, 255);//y blue
	glVertex3f(x + 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	glVertex3f(x + 0.5 * w, y + 0.5 * h, z - 0.5 * d);
	glVertex3f(x - 0.5 * w, y + 0.5 * h, z - 0.5 * d);
	glVertex3f(x - 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	glColor3ub(255, 100, 255);//-y magenta
	glVertex3f(x + 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y - 0.5 * h, z - 0.5 * d);
	glVertex3f(x + 0.5 * w, y - 0.5 * h, z - 0.5 * d);
	glColor3ub(255, 255, 100);//z yellow
	glVertex3f(x + 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	glVertex3f(x + 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	glColor3ub(100, 255, 255);//-z cyan
	glVertex3f(x + 0.5 * w, y + 0.5 * h, z - 0.5 * d);
	glVertex3f(x + 0.5 * w, y - 0.5 * h, z - 0.5 * d);
	glVertex3f(x - 0.5 * w, y - 0.5 * h, z - 0.5 * d);
	glVertex3f(x - 0.5 * w, y + 0.5 * h, z - 0.5 * d);
	glEnd();
}
void MyInvCube(float x, float y, float z, float w, float h, float d) {
	glBegin(GL_QUADS);
	glColor3ub(230, 230, 230);//x red
	glVertex3f(x + 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	glVertex3f(x + 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	glVertex3f(x + 0.5 * w, y + 0.5 * h, z - 0.5 * d);
	glVertex3f(x + 0.5 * w, y - 0.5 * h, z - 0.5 * d);
	glColor3ub(230, 230, 230);//-x green
	glVertex3f(x - 0.5 * w, y + 0.5 * h, z - 0.5 * d);
	glVertex3f(x - 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y - 0.5 * h, z - 0.5 * d);
	glColor3ub(200, 200, 200);//y blue
	glVertex3f(x + 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y + 0.5 * h, z - 0.5 * d);
	glVertex3f(x + 0.5 * w, y + 0.5 * h, z - 0.5 * d);
	glColor3ub(200, 200, 200);//-y magenta
	glVertex3f(x + 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	glVertex3f(x + 0.5 * w, y - 0.5 * h, z - 0.5 * d);
	glVertex3f(x - 0.5 * w, y - 0.5 * h, z - 0.5 * d);
	glVertex3f(x - 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	glColor3ub(255, 255, 255);//z yellow
	glVertex3f(x + 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	glVertex3f(x + 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	glColor3ub(255, 255, 255);//-z cyan
	glVertex3f(x + 0.5 * w, y + 0.5 * h, z - 0.5 * d);
	glVertex3f(x - 0.5 * w, y + 0.5 * h, z - 0.5 * d);
	glVertex3f(x - 0.5 * w, y - 0.5 * h, z - 0.5 * d);
	glVertex3f(x + 0.5 * w, y - 0.5 * h, z - 0.5 * d);
	glEnd();
}

void MyInitSphere(void) {
	for (int i = 0; i < numi; i++) {
		for (int j = 0; j < numj; j++) {
			sp[i][j].p[2] = rangeX - 2 * rangeX * j / (float)(numj - 1);
			sp[i][j].p[1] = -rangeY + 2 * rangeY * i / (float)(numi - 1);
		}
	}
	for (int i = 0; i < numi; i++) {
		sp[i][0].p[0] += (i % 2) * 0.3 * pow(-1, i);
	}
}

void MyDrawSurface() {
	for (int i = 0; i < numi - 1; i++)
		for (int j = 0; j < numj - 1; j++) {
			glColor3ub(150, 150, 200);
			glBegin(GL_TRIANGLES);
			glNormal3fv(myNormal(sp[i][j].p, sp[i][j + 1].p, sp[i + 1][j + 1].p));
			glVertex3fv(sp[i][j].p);
			glVertex3fv(sp[i][j + 1].p);
			glVertex3fv(sp[i + 1][j + 1].p);
			glNormal3fv(myNormal(sp[i][j].p, sp[i + 1][j + 1].p, sp[i + 1][j].p));
			glVertex3fv(sp[i][j].p);
			glVertex3fv(sp[i + 1][j + 1].p);
			glVertex3fv(sp[i + 1][j].p);

			glNormal3fv(myNormal(sp[i + 1][j + 1].p, sp[i][j + 1].p, sp[i][j].p));
			glVertex3fv(sp[i + 1][j + 1].p);
			glVertex3fv(sp[i][j + 1].p);
			glVertex3fv(sp[i][j].p);
			glNormal3fv(myNormal(sp[i + 1][j].p, sp[i + 1][j + 1].p, sp[i][j].p));
			glVertex3fv(sp[i + 1][j].p);
			glVertex3fv(sp[i + 1][j + 1].p);
			glVertex3fv(sp[i][j].p);
			glEnd();
		}
}

void MyDrawSphere() {
	for (int i = 0; i < numi; i++)
		for (int j = 0; j < numj; j++) {
			glColor3ub(100, 100, 100);
			sp[i][j].MyDrawSphere();
		}
}

void MyDrawLines() { //힘에 대응해여 색 변화
	glLineWidth(2);
	for (int j = 0; j < numj; j++) {
		for (int i = 0; i < numi; i++) {
			glBegin(GL_LINES);
			if ((connected[j][i] >> 7) & 1) {
				glColor3ub(MyClamp(50 + 300 * (sp[i][j].MyDist(sp[i][j].p, sp[i][j - 1].p) - sp[i][j].interval)),
					50,
					MyClamp(50 - 350 * (sp[i][j].MyDist(sp[i][j].p, sp[i][j - 1].p) - sp[i][j].interval)));
				glVertex3fv(sp[i][j].p);
				glVertex3fv(sp[i][j - 1].p);
			}
			if ((connected[j][i] >> 6) & 1) {
				glColor3ub(MyClamp(50 + 300 * (sp[i][j].MyDist(sp[i][j].p, sp[i - 1][j - 1].p) - sp[i][j].interval)),
					50,
					MyClamp(50 - 350 * (sp[i][j].MyDist(sp[i][j].p, sp[i - 1][j - 1].p) - sp[i][j].interval)));
				glVertex3fv(sp[i][j].p);
				glVertex3fv(sp[i - 1][j - 1].p);
			}
			if ((connected[j][i] >> 5) & 1) {
				glColor3ub(MyClamp(50 + 300 * (sp[i][j].MyDist(sp[i][j].p, sp[i - 1][j].p) - sp[i][j].interval)),
					50,
					MyClamp(50 - 350 * (sp[i][j].MyDist(sp[i][j].p, sp[i - 1][j].p) - sp[i][j].interval)));
				glVertex3fv(sp[i][j].p);
				glVertex3fv(sp[i - 1][j].p);
			}
			if ((connected[j][i] >> 4) & 1) {
				glColor3ub(MyClamp(50 + 300 * (sp[i][j].MyDist(sp[i][j].p, sp[i - 1][j + 1].p) - sp[i][j].interval)),
					50,
					MyClamp(50 - 350 * (sp[i][j].MyDist(sp[i][j].p, sp[i - 1][j + 1].p) - sp[i][j].interval)));
				glVertex3fv(sp[i][j].p);
				glVertex3fv(sp[i - 1][j + 1].p);
			}
			if ((connected[j][i] >> 3) & 1) {
				glColor3ub(MyClamp(50 + 300 * (sp[i][j].MyDist(sp[i][j].p, sp[i][j + 1].p) - sp[i][j].interval)),
					50,
					MyClamp(50 - 350 * (sp[i][j].MyDist(sp[i][j].p, sp[i][j + 1].p) - sp[i][j].interval)));
				glVertex3fv(sp[i][j].p);
				glVertex3fv(sp[i][j + 1].p);
			}
			if ((connected[j][i] >> 2) & 1) {
				glColor3ub(MyClamp(50 + 300 * (sp[i][j].MyDist(sp[i][j].p, sp[i + 1][j + 1].p) - sp[i][j].interval)),
					50,
					MyClamp(50 - 350 * (sp[i][j].MyDist(sp[i][j].p, sp[i + 1][j + 1].p) - sp[i][j].interval)));
				glVertex3fv(sp[i][j].p);
				glVertex3fv(sp[i + 1][j + 1].p);
			}
			if ((connected[j][i] >> 1) & 1) {
				glColor3ub(MyClamp(50 + 300 * (sp[i][j].MyDist(sp[i][j].p, sp[i + 1][j].p) - sp[i][j].interval)),
					50,
					MyClamp(50 - 350 * (sp[i][j].MyDist(sp[i][j].p, sp[i + 1][j].p) - sp[i][j].interval)));
				glVertex3fv(sp[i][j].p);
				glVertex3fv(sp[i + 1][j].p);
			}
			if ((connected[j][i] >> 0) & 1) {
				glColor3ub(MyClamp(50 + 300 * (sp[i][j].MyDist(sp[i][j].p, sp[i + 1][j - 1].p) - sp[i][j].interval)),
					50,
					MyClamp(50 - 350 * (sp[i][j].MyDist(sp[i][j].p, sp[i + 1][j - 1].p) - sp[i][j].interval)));
				glVertex3fv(sp[i][j].p);
				glVertex3fv(sp[i + 1][j - 1].p);
			}
			glEnd();
		}
	}
}

void MyPhysics(void) {
	for (int j = 0; j < numj; j++)
		for (int i = 0; i < numi; i++) {
			for (int a = 0; a < 3; a++)	sp[i][j].a[a] = 0;
			sp[i][j].a[2] += -1 * sp[0][0].g;
		} // acc init
	if (Pause != 1) {
		for (int j = 0; j < numj; j++) { // i : L->R
			for (int i = 0; i < numi; i++) { // j : U->D
				if ((connected[j][i] >> 7) & 1)	sp[i][j].MyForce(sp[i][j - 1], sp[0][0].interval);				// UU
				if ((connected[j][i] >> 6) & 1)	sp[i][j].MyForce(sp[i - 1][j - 1], sp[0][0].interval * sqrt(2));	// LU
				if ((connected[j][i] >> 5) & 1)	sp[i][j].MyForce(sp[i - 1][j], sp[0][0].interval);				// LL
				if ((connected[j][i] >> 4) & 1)	sp[i][j].MyForce(sp[i - 1][j + 1], sp[0][0].interval * sqrt(2));	// LD
				if ((connected[j][i] >> 3) & 1)	sp[i][j].MyForce(sp[i][j + 1], sp[0][0].interval);				// DD
				if ((connected[j][i] >> 2) & 1)	sp[i][j].MyForce(sp[i + 1][j + 1], sp[0][0].interval * sqrt(2));	// RD
				if ((connected[j][i] >> 1) & 1)	sp[i][j].MyForce(sp[i + 1][j], sp[0][0].interval);				// RR
				if ((connected[j][i] >> 0) & 1)	sp[i][j].MyForce(sp[i + 1][j - 1], sp[0][0].interval * sqrt(2));	// RU
				if (!fixed[j][i]) sp[i][j].calVP();
			}
		}
	}
}

GLfloat* myNormal(GLfloat* a, GLfloat* b, GLfloat* c) {
	GLfloat ab[3], ac[3], p[3];
	for (int i = 0; i < 3; i++) {
		ab[i] = b[i] - a[i];
		ac[i] = c[i] - a[i];
	}
	p[0] = ab[1] * ac[2] - ab[2] * ac[1];
	p[1] = ab[2] * ac[0] - ab[0] * ac[2];
	p[2] = ab[0] * ac[1] - ab[1] * ac[0];
	return p;
}

// 충돌, 조명, 장력 색, 장력 제한