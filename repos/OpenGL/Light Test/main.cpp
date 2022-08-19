#include <GL/freeglut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>

void MyInit(void);
void MyLightInit(void);
void MyDisplay(void);
void MyIdle(void);
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y);
void MyMouseMove(GLint X, GLint Y);
void MyMouseWheel(GLint Button, GLint dir, GLint X, GLint Y);
void MyKey(unsigned char keyp, int x, int y);
void MyReshape(GLint NewWidth, GLint NewHeight);
void MyCube(float x, float y, float z, float w, float h, float d);

unsigned long my_time = 0;
int angle = 40;
float camR = 25, camXr = 23 * 3.14 / 180., camZr = 68 * 3.14 / 180.; // 거리, rad, rad

GLboolean LmouseON = 0, RmouseON = 0, ShaderMod = true, STOP = true;
int mouseX, mouseY, mod = 0;

GLfloat globalAmbient[] = { 0.4, 0.4, 0.4, 1.0 };
GLfloat ambientLight[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat diffuseLight[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specref[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lightPos[] = { 0, 0, 0, 1.0 };
GLfloat myMaterial[] = { 0.75, 0.75, 0.0, 1.0 };

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("mck system");
	glMatrixMode(GL_MODELVIEW);
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

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1, 0.1, 0.1, 1);
	glLoadIdentity();

	gluPerspective(angle, 1, 0.1, 100);
	gluLookAt(camR * sin(camZr) * cos(camXr), camR * sin(camZr) * sin(camXr), camR * cos(camZr), 0, 0, 0, 0, 0, sin(camZr));

	glPushMatrix();
	glRotatef(my_time, 0, 0, 1);
	glTranslatef(7, 0, 0);
	glutWireSphere(0.2, 10, 10);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glPopMatrix();

	if (mod % 2 == 1) MyCube(0, 0, 0, 3, 3, 3);
	else glutSolidSphere(3, 50, 50);

	glFlush();
	glutSwapBuffers();
}

void MyInit() {
	glViewport(0, -100, 1000, 1000);
	glEnable(GL_CULL_FACE); // 뒷면에 대해서는 계산하지 말라
	glFrontFace(GL_CCW);   // 시계방향이 앞면이다.
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}

void MyLightInit() {
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING); // 빛을 사용한다.

	glEnable(GL_LIGHT0); // 0번빛을 사용한다.
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glMaterialfv(GL_FRONT, GL_AMBIENT, myMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, myMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 1);
}

void MyIdle() {
	if (STOP != true) my_time += 1;
	glutPostRedisplay();
}
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		LmouseON = 1;
		mouseX = X;
		mouseY = Y;
	}
	else if (Button == GLUT_LEFT_BUTTON && State == GLUT_UP) {
		LmouseON = 0;
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

void MyMouseWheel(GLint Button, GLint dir, GLint X, GLint Y) {
	glutPostRedisplay();
}

void MyMouseMove(GLint X, GLint Y) {
	if (RmouseON) {
		camXr += 0.005 * (X - mouseX);
		camZr += 0.005 * (Y - mouseY);
		mouseX = X;
		mouseY = Y;
	}
	glutPostRedisplay();
}

void MyKey(unsigned char keyp, int x, int y) {
	switch (keyp) {
	case 'w':
		camR -= 1;
		printf("camR : %d\n", camR);
		break;
	case 's':
		camR += 1;
		printf("camR : %d\n", camR);
		break;
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
		camR = 35;
		camXr = 45 * 3.14 / 180.;
		camZr = 45 * 3.14 / 180.;
		break;
	case 'f':
		if (ShaderMod == 1) {
			glShadeModel(GL_SMOOTH);
			std::cout << "smooth" << std::endl;
			ShaderMod *= -1;
		}
		else {
			glShadeModel(GL_FLAT);
			std::cout << "flat" << std::endl;
			ShaderMod *= -1;
		}
		break;
	case 'p':
		STOP *= -1;
		break;
	case 'm':
		mod++;
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
	//glColor3ub(255, 100, 100);//x red
	glNormal3f(1, 0, 0);
	glVertex3f(x + 0.5 * w, y + 0.5 * h, z - 0.5 * d);
	glVertex3f(x + 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	glVertex3f(x + 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	glVertex3f(x + 0.5 * w, y - 0.5 * h, z - 0.5 * d);
	//glColor3ub(100, 255, 100);//-x green
	glNormal3f(-1, 0, 0);
	glVertex3f(x - 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y + 0.5 * h, z - 0.5 * d);
	glVertex3f(x - 0.5 * w, y - 0.5 * h, z - 0.5 * d);
	//glColor3ub(100, 100, 255);//y blue
	glNormal3f(0, 1, 0);
	glVertex3f(x + 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	glVertex3f(x + 0.5 * w, y + 0.5 * h, z - 0.5 * d);
	glVertex3f(x - 0.5 * w, y + 0.5 * h, z - 0.5 * d);
	glVertex3f(x - 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	//glColor3ub(255, 100, 255);//-y magenta
	glNormal3f(0, -1, 0);
	glVertex3f(x + 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y - 0.5 * h, z - 0.5 * d);
	glVertex3f(x + 0.5 * w, y - 0.5 * h, z - 0.5 * d);
	//glColor3ub(255, 255, 100);//z yellow
	glNormal3f(0, 0, 1);
	glVertex3f(x + 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y + 0.5 * h, z + 0.5 * d);
	glVertex3f(x - 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	glVertex3f(x + 0.5 * w, y - 0.5 * h, z + 0.5 * d);
	//glColor3ub(100, 255, 255);//-z cyan
	glNormal3f(0, 0, -1);
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
