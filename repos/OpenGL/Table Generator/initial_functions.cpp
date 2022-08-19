#include "table_generator.h"

void myEnables() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}

void myInit(int argc, char** argv) {
	std::srand((unsigned int)time(0));
	glutInit(&argc, argv);
	int *winSize = clampWinSize();
	glutInitWindowSize(int((1 + PAD_RATIO)*winSize[0]), int((1 + PAD_RATIO)*winSize[1]));
	glutInitWindowPosition(500, 20);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutCreateWindow("Table Generator");
	glutKeyboardFunc(myKeyboard);
	glMatrixMode(GL_PROJECTION);
	myEnables();
}