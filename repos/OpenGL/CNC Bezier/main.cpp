#include <GL/freeglut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

GLint width = 800, height = 800;
GLfloat ortho = 15.0;
GLint n = 3;  //점의 갯수nxn, 차수는 n-1
GLint num = 10;  //내분점의 갯수
GLfloat psize = 4; //베지에 점 크기
GLfloat stroke = 1;
double toola = 1, toolR = 2; //공구 치수
double u[3] = { 0,0,1 }; //공구 단위벡터

						 //[n][n][4]
GLdouble pi[3][3][4] = { { { 0.,-10.,0.,1. },{ -7.071,-7.071,0.,0.7071 },{ -10.,0.,0.,1. } },
{ { 7.071,-7.071,0.,.7071 },{ 0.,0.,30.,1. },{ -7.071,7.071,0.,0.7071 } },
{ { 10.,0.,0.,1. },{ 7.071,7.071,0.,0.7071 },{ 0.,10.,0.,1. } } };

double*** p, *** bzp, *** bzu, *** bzv, *** bzn, *** toolp;
double time = 0, stop = 1, zoomFactor = 1;
int MovingX, MovingY, mouse_dx, mouse_dy, key[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };

double*** make_points3(int m) {
	double*** b;
	b = (double***)malloc((unsigned long)m * sizeof(double**));
	for (int mi = 0; mi < m; mi++) {
		b[mi] = (double**)malloc((unsigned long)m * sizeof(double*));
		for (int mj = 0; mj < m; mj++) {
			b[mi][mj] = (double*)malloc((unsigned long)4 * sizeof(double));
		}
	}
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			for (int k = 0; k < 4; k++)
				b[i][j][k] = 0;
	return b;
}
void free_points3(double*** b, int m) {
	for (int mi = 0; mi < m; mi++) {
		for (int mj = 0; mj < m; mj++)
			free(b[mi][mj]);
		free(b[mi]);
	}
	free(b);
}
void crossProduct(double* a, double* b, double* c) {
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

double norm(double* n) {
	double a;
	a = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
	n[0] /= a;
	n[1] /= a;
	n[2] /= a;
	return a;
}

void bezier2(double* p0, double* p1, double* p2, double u, double* ph, double* p, double* pu)
{
	double phu[4], norm;
	int i;
	for (i = 0; i < 4; i++) {
		ph[i] = (1 - u) * (1 - u) * p0[i] + 2.0 * u * (1 - u) * p1[i] + u * u * p2[i];  // Ph
		phu[i] = 2.0 * ((u - 1) * p0[i] + (1 - 2.0 * u) * p1[i] + u * p2[i]);  // Ph'
	}
	for (i = 0; i < 3; i++) {
		p[i] = ph[i] / ph[3]; // P 일반좌표계 값
		pu[i] = (phu[i] * ph[3] - ph[i] * phu[3]) / (ph[3] * ph[3]);  // P'
	}
	norm = sqrt(pu[0] * pu[0] + pu[1] * pu[1] + pu[2] * pu[2]);
	p[3] = pu[3] = 1;
	for (i = 0; i < 3; i++)
		pu[i] /= norm;
}
void bezier_surface_2(double*** p, double u, double v, double* pa, double* pau, double* pav)
{
	double*** pu;
	pu = make_points3(3);
	double puu0[4], pc[4], ph[4];
	for (int i = 0; i < 3; i++)
		bezier2(p[0][i], p[1][i], p[2][i], u, pu[0][i], pc, puu0);
	bezier2(pu[0][0], pu[0][1], pu[0][2], v, ph, pa, pav);
	for (int i = 0; i < 3; i++)
		bezier2(p[i][0], p[i][1], p[i][2], v, pu[0][i], pc, puu0);
	bezier2(pu[0][0], pu[0][1], pu[0][2], u, ph, pa, pau);
	free_points3(pu, 3);
}
void bezier_init(double(*pi)[3][4], double*** p, double*** bzp, double*** bzu, double*** bzv, double*** bzn, int num) {
	double pa[4], pau[4], pav[4];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < 4; k++)
				p[i][j][k] = pi[i][j][k];
	for (int u = 0; u < num + 2; u++) {
		for (int v = 0; v < num + 2; v++) {
			bezier_surface_2(p, u / double(num + 1), v / double(num + 1), pa, pau, pav);
			for (int c = 0; c < 4; c++) {
				bzp[u][v][c] = pa[c];
				bzu[u][v][c] = pau[c];  //p, u, v 벡터 생성
				bzv[u][v][c] = pav[c];
			}
		}
	}
	for (int u = 0; u < num + 2; u++) {
		for (int v = 0; v < num + 2; v++) {
			crossProduct(bzu[u][v], bzv[u][v], bzn[u][v]); //n 벡터 생성
		}
	}

	for (int u = 0; u < num + 2; u++) {
		for (int v = 0; v < num + 2; v++) {
			norm(bzu[u][v]);
			norm(bzv[u][v]);  //u,v,n 정규화
			norm(bzn[u][v]);
		}
	}


	for (int i = 0; i < 3; i++) {
		bzn[0][0][i] = bzn[1][0][i] + bzn[0][1][i] - bzn[1][1][i];
		bzn[num + 1][num + 1][i] = bzn[num][num + 1][i] + bzn[num + 1][num][i] - bzn[num][num][i];
		bzn[0][num + 1][i] = bzn[1][num + 1][i] + bzn[0][num][i] - bzn[1][num][i];
		bzn[num + 1][0][i] = bzn[num + 1][1][i] + bzn[num][0][i] - bzn[num][1][i];
	}

	norm(bzn[0][0]);
	norm(bzn[num + 1][num + 1]);
	norm(bzn[0][num + 1]);
	norm(bzn[num + 1][0]);

	/*
	for (int u = 0; u < num + 2; u++) {
	for (int v = 0; v < num + 2; v++) {
	printf("(u,v) = (%d,%d)\n", u, v);//(u,v)
	printf("P : %.4f %.4f %.4f\n", bzp[u][v][0], bzp[u][v][1], bzp[u][v][2]);//x,y,z
	printf("Pu: %.4f %.4f %.4f\n", bzu[u][v][0], bzu[u][v][1], bzu[u][v][2]);//u방향벡터
	printf("Pv: %.4f %.4f %.4f\n", bzu[u][v][0], bzv[u][v][1], bzv[u][v][2]);//v방향벡터
	printf("Pn: %.4f %.4f %.4f\n\n", bzn[u][v][0], bzn[u][v][1], bzn[u][v][2]);//n방향벡터
	}
	}
	*/
}
void tool_init(double* u, double*** bzn, double*** bzp, double*** toolp) {
	double un[3], *** t;
	t = make_points3(num + 2);
	for (int i = 0; i < num + 2; i++)
		for (int j = 0; j < num + 2; j++) {
			crossProduct(u, bzn[i][j], un);
			crossProduct(un, u, t[i][j]);    //t벡터 생성
			norm(t[i][j]);
		}
	for (int i = 0; i < num + 2; i++)
		for (int j = 0; j < num + 2; j++) {
			for (int k = 0; k < 3; k++)
				toolp[i][j][k] = bzp[i][j][k] + toola * bzn[i][j][k] - toola * u[k] + (toolR - toola) * t[i][j][k]; //툴점 생성
		}
	free_points3(t, num + 2);
}

void MyAxisDraw() {
	if (key[8] == 1) {
		glLineWidth(2);
		glPointSize(3);
		for (int i = -ortho - 1; i < ortho; i++) {
			glColor3f(0.5, 0.5, 0.5);
			glBegin(GL_LINES);
			glVertex3i(0, 0, i);
			glVertex3i(0, 0, i + 1);
			glVertex3f(0, i, 0);
			glVertex3f(0, i + 1, 0);
			glVertex3i(i, 0, 0);
			glVertex3i(i + 1, 0, 0);
			glEnd();
			glColor3f(1, 1, 1);
			glBegin(GL_POINTS);
			glVertex3i(0, 0, i);
			glVertex3i(0, i, 0);
			glVertex3i(i, 0, 0);
			glEnd();
		}
		glLineWidth(stroke);
	}
}
void MyBezierDraw(double*** p, double*** bzp, double*** bzu, double*** bzv, double*** bzn) {
	if (key[8] == 1) {
		glColor3f(0, 0, 0);
		glPointSize(6);
		glBegin(GL_POINTS); //q점 검정색
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				glVertex3dv(p[i][j]);
		glEnd();
		glPointSize(15);
		glColor3f(0, 0, 0.);
		glBegin(GL_POINTS); //u,v 원점
		glVertex3dv(bzp[0][0]);
		glEnd();
	}
	if (key[0] != 1) {
		glPointSize(psize);
		glBegin(GL_POINTS); //베지에점 빨강
		glColor3ub(255, 100, 100);
		for (int u = 0; u < num + 2; u++) {
			for (int v = 0; v < num + 2; v++) {
				glVertex3dv(bzp[u][v]);
			}
		}
		glEnd();
	}

	if (key[1] == 1) {
		glColor3ub(255, 150, 150); //베지에 라인 분홍
		for (int u = 0; u < num + 1; u++) {
			for (int v = 0; v < num + 1; v++) {
				glBegin(GL_LINE_STRIP);//ㄴ자로
				glVertex3dv(bzp[u + 1][v]);
				glVertex3dv(bzp[u][v]);
				glVertex3dv(bzp[u][v + 1]);
				glEnd();
			}
			glBegin(GL_LINES);//나머지
			glVertex3dv(bzp[u][num + 1]);
			glVertex3dv(bzp[u + 1][num + 1]);
			glVertex3dv(bzp[num + 1][u]);
			glVertex3dv(bzp[num + 1][u + 1]);
			glEnd();
		}
	}
	if (key[2] == 1) {
		glColor4ub(255, 200, 200, 150); //베지에면 연분홍
		for (int u = 0; u < num + 1; u++) {
			glBegin(GL_QUAD_STRIP);
			for (int v = 0; v < num + 2; v++) {
				glVertex3dv(bzp[u][v]);
				glVertex3dv(bzp[u + 1][v]);
			}
			glEnd();
		}
	}

	if (key[3] == 1) {
		glLineWidth(1.3);
		for (int u = 0; u < num + 2; u++) {  //u,v 벡터
			for (int v = 0; v < num + 2; v++) {
				glBegin(GL_LINES);
				glColor3f(0., 0., 1); //u벡터 
				glVertex3d(bzp[u][v][0], bzp[u][v][1], bzp[u][v][2]);
				glVertex3d(bzp[u][v][0] + bzu[u][v][0] / double(0.1 * num), bzp[u][v][1] + bzu[u][v][1] / double(0.1 * num), bzp[u][v][2] + bzu[u][v][2] / double(0.1 * num));
				glColor3f(0, 1, 0); //v벡터
				glVertex3d(bzp[u][v][0], bzp[u][v][1], bzp[u][v][2]);
				glVertex3d(bzp[u][v][0] + bzv[u][v][0] / double(0.1 * num), bzp[u][v][1] + bzv[u][v][1] / double(0.1 * num), bzp[u][v][2] + bzv[u][v][2] / double(0.1 * num));
				glEnd();
			}
		}
	}
	if (key[4] == 1) {
		glLineWidth(1.3);
		glColor3f(1., 0., 0.);
		for (int u = 0; u < num + 2; u++) {  //n 벡터
			for (int v = 0; v < num + 2; v++) {
				glBegin(GL_LINES);
				for (int c = 0; c < 3; c++) {
					glVertex3d(bzp[u][v][0], bzp[u][v][1], bzp[u][v][2]);
					glVertex3d(bzp[u][v][0] + bzn[u][v][0] / double(0.1 * num),
						bzp[u][v][1] + bzn[u][v][1] / double(0.1 * num), bzp[u][v][2] + bzn[u][v][2] / double(0.1 * num));
				}
				glEnd();
			}
		}
	}
}
void MyToolDraw(double*** toolp) {
	if (key[5] != 1) {
		glPointSize(psize);
		glBegin(GL_POINTS); //툴점 파랑
		glColor3ub(100, 100, 255);
		for (int u = 0; u < num + 2; u++) {
			for (int v = 0; v < num + 2; v++) {
				glVertex3dv(toolp[u][v]);
			}
		}
		glEnd();
	}

	if (key[6] == 1) {
		glColor3ub(150, 150, 255); //툴 라인 하늘
		for (int u = 0; u < num + 1; u++) {
			for (int v = 0; v < num + 1; v++) {
				glBegin(GL_LINE_STRIP);//ㄴ자로
				glVertex3dv(toolp[u + 1][v]);
				glVertex3dv(toolp[u][v]);
				glVertex3dv(toolp[u][v + 1]);
				glEnd();
			}
			glBegin(GL_LINES);//나머지
			glVertex3dv(toolp[u][num + 1]);
			glVertex3dv(toolp[u + 1][num + 1]);
			glVertex3dv(toolp[num + 1][u]);
			glVertex3dv(toolp[num + 1][u + 1]);
			glEnd();
		}
	}
	if (key[7] == 1) {
		glColor4ub(200, 200, 255, 150); //툴 면 연하늘
		for (int u = 0; u < num + 1; u++) {
			glBegin(GL_QUAD_STRIP);
			for (int v = 0; v < num + 2; v++) {
				glVertex3dv(toolp[u][v]);
				glVertex3dv(toolp[u + 1][v]);
			}
			glEnd();
		}
	}

}

void MyInit() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POLYGON_SMOOTH | GL_LINE_SMOOTH | GL_POINT_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.95, 0.95, 0.95, 1.0);
	glPushMatrix();
	glRotatef(-80, 1, 0, 0);
	glRotatef(-80, 0, 0, 1);
	glRotatef((float)mouse_dx * 0.3f, 0, 0, 1);
	glRotatef((float)mouse_dy * 0.3f, 0, 1, 0);
	glRotatef(0.25 * time, 0.1, 0.05, 1.0);
	glScalef(zoomFactor, zoomFactor, zoomFactor);
	MyAxisDraw();
	MyBezierDraw(p, bzp, bzu, bzv, bzn);
	MyToolDraw(toolp);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void MyIdle() {
	if (stop == 1)
		time += 1;
	glutPostRedisplay();
}
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		MovingX = X;
		MovingY = Y;
		stop = 0;
	}
	else
		stop = 1;

	if (Button == 3 || Button == 4)
	{
		if (State == GLUT_UP) zoomFactor += 0.05;
		else zoomFactor -= 0.05;
	}
}
void MyMouseMove(GLint X, GLint Y) {
	mouse_dx += X - MovingX;
	mouse_dy += Y - MovingY;
	MovingX = X;
	MovingY = Y;
	glutPostRedisplay();
}
void MyReshape(GLint NewWidth, GLint NewHeight) {
}
void MyKey(unsigned char keyp, int x, int y) {
	switch (keyp) {
	case '1':
		key[0] *= -1;
		break;
	case '2':
		key[1] *= -1;
		break;
	case '3':
		key[2] *= -1;
		break;
	case '4':
		key[3] *= -1;
		break;
	case '5':
		key[4] *= -1;
		break;
	case '6':
		key[5] *= -1;
		break;
	case '7':
		key[6] *= -1;
		break;
	case '8':
		key[7] *= -1;
		break;
	case '9':
		key[8] *= -1;
		break;
	case 'w':
		zoomFactor += 0.05;
		break;
	case 's':
		zoomFactor -= 0.05;
		break;
	case 'q':
		if (stop == 1)
			stop = 0;
		else
			stop = 1;
		break;
	}
}

int main(int argc, char** argv) {
	p = make_points3(3);
	bzp = make_points3(num + 2);
	bzu = make_points3(num + 2);
	bzv = make_points3(num + 2);
	bzn = make_points3(num + 2);
	toolp = make_points3(num + 2);

	bezier_init(pi, p, bzp, bzu, bzv, bzn, num);
	tool_init(u, bzn, bzp, toolp);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Bezier Surface");
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-ortho, ortho, -ortho, ortho, -ortho, ortho);
	MyInit();

	gluLookAt(0.0, 0.0, 5, 0.0, 0.0, -30, 0.0, 1.0, 0.0);

	glutDisplayFunc(MyDisplay);
	glutIdleFunc(MyIdle);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	glutKeyboardFunc(MyKey);
	glutReshapeFunc(MyReshape);
	glutMainLoop();

	free_points3(bzp, num + 2);
	free_points3(bzu, num + 2);
	free_points3(bzv, num + 2);
	free_points3(bzn, num + 2);
	free_points3(toolp, num + 2);
	free_points3(p, 3);
	return 0;
}
