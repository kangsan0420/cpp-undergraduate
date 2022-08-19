
#include <opencv2/opencv.hpp>
#include <GL/freeglut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <math.h>

using namespace cv;
using namespace std;

VideoCapture capture;
CascadeClassifier face_cascade, eyes_cascade;

Mat frame;
Mat gray;

vector<Rect> faces;
vector<Rect> eyes;

void CVInit(void);
void GLInit(void);
void CVwhile(void);
void GLSetting(void);
void MyDisplay(void);
void MyIdle(void);
void MyReshpae(GLint W, GLint H);
void MyMotion(GLint X, GLint Y);
void MyWall(void);
void MyKeyFunc(unsigned char KEY, GLint X, GLint Y);
float dist2(float x, float y, float a, float b);
void printMat(float* m);

unsigned long GLtime = 0;
GLint mouseX, mouseY, mouseON = 0, icam = 0, cvWidth = 240, cvHeight = 180, glWidth, glHeight;
GLfloat tcamX, tcamY, camX = 0, camY = 0, sens = 0.5;
GLfloat icamX[10] = {}, icamY[10] = {};
GLboolean fullscreen = false, antialiasing = true, facedetected = false;
float shearZ = -0.1;
float shearTrans[16] = { 
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};
float cur[16];

class pingpong {
public:
	float pP[3] = { 0,0,-2 }, pMaxV = 0.2, pSize = 1; //user
	float cP[3] = { 0,0,0 }, cMaxV = 0.02, cSize = 2; //computer
	float bP[3] = { 0,0,-5 }, bV[3] = { 0,0,0.1f }, bSize = 1; //ball

	void pongCalCom() {
		cP[0] += cMaxV * (bP[0] - cP[0]);
		cP[1] += cMaxV * (bP[1] - cP[1]);
	}

	void pongCalBall() {
		if (bV[0] > 0 && 10 - bP[0] < bSize) bV[0] *= -1;
		if (bV[0] < 0 && 10 + bP[0] < bSize) bV[0] *= -1;
		if (bV[1] > 0 && 10 - bP[1] < bSize) bV[1] *= -1;
		if (bV[1] < 0 && 10 + bP[1] < bSize) bV[1] *= -1;

		if (bP[2] > -bSize && bV[2] > 0 && dist2(bP[0], bP[1], pP[0], pP[1]) < bSize) bV[2] *= -1;
		if (10 + bP[2] < bSize) bV[2] *= -1;

		for (int i = 0; i < 3; i++)	bP[i] += bV[i];
	}

	void pongCalPla() {
		Ping.pP[0] -= Ping.pMaxV * (Ping.pP[0] - (-10 + 20 * mouseX / (float)glWidth));
		Ping.pP[1] -= Ping.pMaxV * (Ping.pP[1] - (10 - 20 * mouseY / (float)glHeight));
	}
	void pongDraw() {
		glBegin(GL_TRIANGLE_FAN); // player
		glColor4ub(120, 100, 255, 150);
		glVertex3fv(pP);
		for (int i = 0; i <= 20; i++) glVertex3f(pP[0] + pSize * cos(2 * 3.14159 * i / 20), pP[1] + pSize * sin(2 * 3.14159 * i / 20), -2);
		glEnd();

		glPushMatrix();// ball
		glTranslatef(bP[0], bP[1], bP[2]);
		glColor3f(100, 200, 100);
		glutWireSphere(bSize, 30, 30);
		glPopMatrix();


	}
}Ping;

int main(int argc, char** argv) {
	CVInit();
	GLInit();
	//while(1){
	//	CVwhile();
	//	if (waitKey(30) >= 0) break;
	//}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("GL_test01");
	glutSetCursor(GLUT_CURSOR_NONE);
	glMatrixMode(GL_MODELVIEW);
	glutIdleFunc(MyIdle);
	glutPassiveMotionFunc(MyMotion);
	glutKeyboardFunc(MyKeyFunc);
	glutReshapeFunc(MyReshpae);
	glMatrixMode(GL_MODELVIEW);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1, 0.1, 0.1, 1);
	GLSetting();
	CVwhile();
	camX = tcamX * sens;
	camY = -1.0 * tcamY * sens;

	//cali----------------------------
	icamX[icam] = camX;
	icamY[icam] = camY;
	icam++;
	if (icam >= 3) icam = 0;
	camX = 0;
	camY = 0;
	for (int i = 0; i < 3; i++) {
		camX += 0.1 * icamX[i];
		camY += 0.1 * icamY[i];
	}
	//--------------------------------
	camY += 5;//offset

	glLoadIdentity();
	glFrustum(-10 - camX, 10 - camX, -10 - camY, 10 - camY, 10, 100);
	glGetFloatv(GL_MODELVIEW_MATRIX, cur);
	printMat(cur);
	gluLookAt(camX, camY, 10, camX, camY, 0, 0, 1, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, cur);
	printMat(cur);
	glMultMatrixf(shearTrans);
	glGetFloatv(GL_MODELVIEW_MATRIX, cur);
	printMat(cur);
	MyWall();
	//Ping.pongCalPla();
	//Ping.pongCalBall();
	//Ping.pongDraw();
	glFlush();
	glutSwapBuffers();
}

void CVwhile(void) {
	int maxSize = 0;
	int i;
	capture.read(frame);
	flip(frame, frame, 1);
	resize(frame, frame, Size(cvWidth, cvHeight));
	cvtColor(frame, gray, COLOR_BGR2GRAY);

	face_cascade.detectMultiScale(frame, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE);
	facedetected = false;
	if (faces.size() != 0) {
		facedetected = true;
		for (int k = 0; k < faces.size(); k++) {
			if (faces[k].width * faces[k].height > maxSize) {
				maxSize = faces[k].width * faces[k].height;
				i = k;
			}
		}
		rectangle(frame, faces[i], Scalar(0, 255, 255), 1);
		Point C(faces[i].x + (faces[i].width) / 2., faces[i].y + (faces[i].height) / 2.);
		circle(frame, C, 1, Scalar(255, 0, 0), 2, LINE_AA, 0);
		if (faces[i].x != 0) {
			tcamX = faces[i].x + (faces[i].width) * 0.5 - cvWidth * 0.5;
			tcamY = faces[i].y + (faces[i].height) * 0.5 - cvHeight * 0.5;
		}
	}
	//imshow("a", frame);
}

void CVInit(void) {
	capture = VideoCapture(0);
	if (!capture.isOpened()) {
		cout << "카메라 없음" << endl;
		exit(1);
	}
	face_cascade.load("../../../libraries/opencv/cascades/haarcascades/haarcascade_frontalface_alt2.xml");
	//face_cascade.load("../../../libraries/opencv/cascades/lbpcascades/lbpcascade_frontalface.xml");
}

void GLInit(void) {
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH);
}

void GLSetting(void) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (antialiasing) {
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
	}
	else {
		glDisable(GL_POINT_SMOOTH);
		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_POLYGON_SMOOTH);

	}
}

void MyMotion(GLint X, GLint Y) {
	if (X > 0 && X < glWidth && Y>0 && Y < glHeight) {
		mouseX = X;
		mouseY = Y;
	}
}

void MyKeyFunc(unsigned char KEY, GLint X, GLint Y) {
	switch (KEY) {
	case 27:
		glutDestroyWindow(1);
		exit(0);
		break;
	case 'f':
		if (!fullscreen) {
			glutFullScreen();
			fullscreen = true;
		}
		else {
			glutReshapeWindow(600, 600);
			glutPositionWindow(500, 0);
			fullscreen = false;
		}
		break;
	case 'g':
		if (!antialiasing) {
			antialiasing = true;
		}
		else {
			antialiasing = false;
		}
	}
}

void MyReshpae(GLint W, GLint H) {
	glWidth = W;
	glHeight = H;
	glViewport(0, 0, W, H);
}

void MyIdle() {
	GLtime += 1;
	glutPostRedisplay();
}

void MyWall() {
	GLint wn = 12, hn = 8, zn = 10;
	GLfloat wd = 0.05, hd = 0.05, zd = 0.05;
	GLfloat zdep = 15;

	glColor3f(0.9, 0.9, 0.9);
	glLineWidth(3);
	for (int i = 1; i < wn; i++) {
		glBegin(GL_POLYGON); //bottom
		glVertex3f(-10 + wd + 20 / (float)wn * i, -10, 0);
		glVertex3f(-10 + wd + 20 / (float)wn * i, -10, -zdep);
		glVertex3f(-10 - wd + 20 / (float)wn * i, -10, -zdep);
		glVertex3f(-10 - wd + 20 / (float)wn * i, -10, 0);
		glEnd();
		glBegin(GL_POLYGON); //top
		glVertex3f(-10 + wd + 20 / (float)wn * i, 10, 0);
		glVertex3f(-10 - wd + 20 / (float)wn * i, 10, 0);
		glVertex3f(-10 - wd + 20 / (float)wn * i, 10, -zdep);
		glVertex3f(-10 + wd + 20 / (float)wn * i, 10, -zdep);
		glEnd();
	}
	for (int i = 0; i < hn + 1; i++) {
		glBegin(GL_POLYGON); //left
		glVertex3f(-10, -10 + hd + 20 / (float)hn * i, 0);
		glVertex3f(-10, -10 + hd + 20 / (float)hn * i, -zdep);
		glVertex3f(-10, -10 - hd + 20 / (float)hn * i, -zdep);
		glVertex3f(-10, -10 - hd + 20 / (float)hn * i, 0);
		glEnd();
		glBegin(GL_POLYGON); //right
		glVertex3f(10, -10 + hd + 20 / (float)hn * i, 0);
		glVertex3f(10, -10 - hd + 20 / (float)hn * i, 0);
		glVertex3f(10, -10 - hd + 20 / (float)hn * i, -zdep);
		glVertex3f(10, -10 + hd + 20 / (float)hn * i, -zdep);
		glEnd();
	}
	for (int i = 0; i < zn + 1; i++) { // depth
		if (i == 0 && facedetected == false) glColor3ub(255, 100, 100);
		else glColor3f(0.9, 0.9, 0.9);
		glBegin(GL_POLYGON);
		glVertex3f(-10, -10, -zdep * i / (float)zn + zd);
		glVertex3f(-10, -10, -zdep * i / (float)zn - zd);
		glVertex3f(-10, 10, -zdep * i / (float)zn - zd);
		glVertex3f(-10, 10, -zdep * i / (float)zn + zd);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-10, 10, -zdep * i / (float)zn + zd);
		glVertex3f(-10, 10, -zdep * i / (float)zn - zd);
		glVertex3f(10, 10, -zdep * i / (float)zn - zd);
		glVertex3f(10, 10, -zdep * i / (float)zn + zd);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(10, 10, -zdep * i / (float)zn + zd);
		glVertex3f(10, 10, -zdep * i / (float)zn - zd);
		glVertex3f(10, -10, -zdep * i / (float)zn - zd);
		glVertex3f(10, -10, -zdep * i / (float)zn + zd);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(10, -10, -zdep * i / (float)zn + zd);
		glVertex3f(10, -10, -zdep * i / (float)zn - zd);
		glVertex3f(-10, -10, -zdep * i / (float)zn - zd);
		glVertex3f(-10, -10, -zdep * i / (float)zn + zd);
		glEnd();
	}
}

float dist2(float x, float y, float a, float b) {
	return sqrt((x - a) * (x - a) + (y - b) * (y - b));
}

void printMat(float* m) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%.2f\t", m[4 * i + j]);
		}
		printf("\n");
	}
	printf("\n");
}