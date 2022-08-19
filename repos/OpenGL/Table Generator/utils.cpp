#include "table_generator.h"

float randf(float max) {
	return max * rand() / (float)RAND_MAX;
}

float randrange(float min, float max) {
	return (max - min) * rand() / (float)RAND_MAX + min;
}

int *clampWinSize(void) {
	int show_width = PIX_WIDTH;
	int show_height = PIX_HEIGHT;
	float aspect = PIX_HEIGHT / PIX_WIDTH;
	if (show_height > 800) {
		show_height = 800;
		show_width = 800 / aspect;
	}
	if (show_width > 1500) {
		show_width = 1500;
		show_height = 1500 * aspect;
	}
	int a[2] = { show_width, show_height };
	return a;
}
void SaveAsBMP(const char *fileName)
{
	FILE *file;
	unsigned long imageSize;
	GLbyte *data = NULL;
	GLint viewPort[4];
	GLenum lastBuffer;
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	bmfh.bfType = 'MB';
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = 54;
	//glGetIntegerv(GL_VIEWPORT, viewPort);
	int *winSize = clampWinSize();
	viewPort[0] = 0;
	viewPort[1] = 0;
	viewPort[2] = int((1 + PAD_RATIO)*winSize[0]);
	viewPort[3] = int((1 + PAD_RATIO)*winSize[1]);
	imageSize = ((viewPort[2] + ((4 - (viewPort[2] % 4)) % 4))*viewPort[3] * 3) + 2;
	bmfh.bfSize = imageSize + sizeof(bmfh) + sizeof(bmih);
	data = (GLbyte*)malloc(imageSize);
	glPixelStorei(GL_PACK_ALIGNMENT, 4);
	glPixelStorei(GL_PACK_ROW_LENGTH, 0);
	glPixelStorei(GL_PACK_SKIP_ROWS, 0);
	glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_PACK_SWAP_BYTES, 1);
	glGetIntegerv(GL_READ_BUFFER, (GLint*)&lastBuffer);
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, viewPort[2], viewPort[3], GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	data[imageSize - 1] = 0;
	data[imageSize - 2] = 0;
	glReadBuffer(lastBuffer);
	file = fopen(fileName, "wb");
	bmih.biSize = 40;
	bmih.biWidth = viewPort[2];
	bmih.biHeight = viewPort[3];
	bmih.biPlanes = 1;
	bmih.biBitCount = 24;
	bmih.biCompression = 0;
	bmih.biSizeImage = imageSize;
	bmih.biXPelsPerMeter = 45089;
	bmih.biYPelsPerMeter = 45089;
	bmih.biClrUsed = 0;
	bmih.biClrImportant = 0;
	fwrite(&bmfh, sizeof(bmfh), 1, file);
	fwrite(&bmih, sizeof(bmih), 1, file);
	fwrite(data, imageSize, 1, file);
	free(data);
	fclose(file);
}