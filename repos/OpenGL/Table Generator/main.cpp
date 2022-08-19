#include "table_generator.h"

int save_max = 200;
int save_cur = 0;

int main(int argc, char** argv) {
	myInit(argc, argv);
	float COLOR_PAD = 1;
	glClearColor(COLOR_PAD, COLOR_PAD, COLOR_PAD, 1);
	//glutIdleFunc(myIdle);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}

void myIdle() {
	if (save_cur < save_max-1) {
		glutPostRedisplay();
		save_cur++;
	}
	else {
		glutDestroyWindow(1);
	}
}
