#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <GL/freeglut.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>
#include <string>


void myInit(int argc, char** argv);
//============= GLOBAL VARIABLES ==f===========
#define NUM_ROWS 15
#define NUM_COLS 20

#define PIX_WIDTH 6000
#define PIX_HEIGHT 8000
#define PAD_RATIO 0.2 //float

//============== callback functions ===========
void myDisplay();
void myKeyboard(unsigned char key, int x, int y);
void myIdle(void);


//============== draw functions ===============
void drawBackground(void);
void draw_table(void);
void fill_table(void);

//============== utils =======================
float randf(float max);
float randrange(float min, float max);
int *clampWinSize(void);
void SaveAsBMP(const char *fileName);
void saveFile(void);