#include "table_generator.h"

int num = 1;

void saveFile(void) {
	char ran[20];
	sprintf(ran, "./Images/%2d.bmp", num);
	SaveAsBMP(ran);
	num += 1;
}

void myDisplay() {
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	int* winSize = clampWinSize();
	glViewport(int(0.5*PAD_RATIO*winSize[0]), int(0.5*PAD_RATIO*winSize[1]), winSize[0], winSize[1]);
	glOrtho(0, PIX_WIDTH, 0, PIX_HEIGHT, 1, -1);
	drawBackground();

	draw_table();
	fill_table();

	saveFile();

	glFlush();
}

void myKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		glutDestroyWindow(1);
		break;
	case 's':
		//saveFile();
		break;
	default:
		glutPostRedisplay();
	}

}