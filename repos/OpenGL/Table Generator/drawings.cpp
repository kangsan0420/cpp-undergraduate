#include "table_generator.h"

float offset_factor = 1.5;

void drawBackground(void) {
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(PIX_WIDTH, 0, 0);
	glVertex3f(PIX_WIDTH, PIX_HEIGHT, 0);
	glVertex3f(0, PIX_HEIGHT, 0);
	glEnd();
}

void drawCircle(float centerX, float centerY, float radious) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < 50; i++) {
		float rad = 2 * M_PI * i / (float)50;
		glVertex2f(centerX + radious * cosf(rad), centerY + radious * sinf(rad));
	}
	glEnd();

}

void draw_o(void) {
	int iter = 40;
	float line_width = 0.08;
	float std = line_width * 0.1;
	float scale_mag = randrange(0.6, 0.9);
	float scale_x = scale_mag * randrange(0.6, 1.0);
	float scale_y = scale_mag * randrange(0.8, 1.0);
	float offset_x = (randf(1 - scale_x) - (1 - scale_x))*1*offset_factor;
	float offset_y = (randf(1 - scale_y) - (1 - scale_x))*0.8*offset_factor;
	float rad = 2 * M_PI*randf(1);
	drawCircle(scale_x*cosf(rad) + offset_x, scale_y*sinf(rad) + offset_y, line_width*0.5);
	float x_back_inner = (scale_x - 0.5*line_width)*cosf(rad) + offset_x;
	float x_back_outer = (scale_x + 0.5*line_width)*cosf(rad) + offset_x;
	float y_back_inner = (scale_y - 0.5*line_width)*sinf(rad) + offset_y;
	float y_back_outer = (scale_y + 0.5*line_width)*sinf(rad) + offset_y;
	float x_noise = randf(0.03);
	float y_noise = randf(0.03);
	for (int i = 1; i <= iter + 1; i++) {
		line_width += randf(2 * std) - std;
		rad += 2 * M_PI / (float)iter;
		float x_front_inner = (scale_x - 0.5*line_width)*cosf(rad) + offset_x;
		float x_front_outer = (scale_x + 0.5*line_width)*cosf(rad) + offset_x;
		float y_front_inner = (scale_y - 0.5*line_width)*sinf(rad) + offset_y;
		float y_front_outer = (scale_y + 0.5*line_width)*sinf(rad) + offset_y;
		x_noise += randf(0.01);
		y_noise += randf(0.01);
		x_front_inner += x_noise;
		x_front_outer += x_noise;
		y_front_inner += y_noise;
		y_front_outer += y_noise;
		glColor3ub(0, 0, 0);
		glBegin(GL_QUADS);
		glVertex2f(x_front_outer, y_front_outer);
		glVertex2f(x_front_inner, y_front_inner);
		glVertex2f(x_back_inner, y_back_inner);
		glVertex2f(x_back_outer, y_back_outer);
		glEnd();
		x_back_inner = x_front_inner;
		x_back_outer = x_front_outer;
		y_back_inner = y_front_inner;
		y_back_outer = y_front_outer;
	}
	drawCircle(0.5*(x_back_inner + x_back_outer), 0.5*(y_back_inner + y_back_outer), line_width*0.5);
}

void draw_x(void) {
	float line_width = 0.04;
	float std = line_width * 0.1;
	float scale_mag = randrange(0.85, 1.1);
	float scale_x = scale_mag * randrange(0.8, 1.0);
	float scale_y = scale_mag * randrange(0.8, 1.0);
	float offset_x = 2.2*(randf(1 - scale_x) - 0.5 * (1 - scale_x))*offset_factor;
	float offset_y = 1.8*(randf(1 - scale_x) - 0.5 * (1 - scale_y))*offset_factor;
	float band = randrange(0.5, 1.0);
	float slash_top_x = offset_x - band * scale_x;
	float slash_bot_x = offset_x + band * scale_x;
	float slash_top_y = offset_y - band * scale_y;
	float slash_bot_y = offset_y + band * scale_y;
	float ilash_top_x = offset_x - band * scale_x;
	float ilash_bot_x = offset_x + band * scale_x;
	float ilash_bot_y = offset_y - band * scale_y;
	float ilash_top_y = offset_y + band * scale_y;

	float pre_x_t = slash_top_x - line_width;
	float pre_y_t = slash_top_y + line_width;
	float pre_x_b = slash_top_x + line_width;
	float pre_y_b = slash_top_y - line_width;
	float offset = 0.2;
	float slash_offset_x = randf(offset) - offset * 0.5;
	float slash_offset_y = randf(offset) - offset * 0.5;
	glColor3f(0, 0, 0);
	drawCircle(slash_top_x + slash_offset_x, slash_top_y + slash_offset_y, line_width*sqrt(2));
	for (int i = 1; i <= 10; i++) {
		line_width += randf(2 * std) - std;
		float x = slash_top_x + (slash_bot_x - slash_top_x)*i / (float)10;
		float y = slash_top_y + (slash_bot_y - slash_top_y)*i / (float)10;
		float noise_x = randf(0.02);
		float noise_y = randf(0.02);
		x += noise_x;
		y += noise_y;
		float x_t = x - line_width;
		float y_t = y + line_width;
		float x_b = x + line_width;
		float y_b = y - line_width;
		glBegin(GL_POLYGON);
		glVertex2f(pre_x_t + slash_offset_x, pre_y_t + slash_offset_y);
		glVertex2f(x_t + slash_offset_x, y_t + slash_offset_y);
		glVertex2f(x_b + slash_offset_x, y_b + slash_offset_y);
		glVertex2f(pre_x_b + slash_offset_x, pre_y_b + slash_offset_y);
		glEnd();
		pre_x_t = x_t;
		pre_y_t = y_t;
		pre_x_b = x_b;
		pre_y_b = y_b;
	}
	drawCircle(0.5*(pre_x_t + pre_x_b) + slash_offset_x, 0.5*(pre_y_t + pre_y_b) + slash_offset_y, line_width*sqrt(2));

	line_width = 0.02;
	pre_x_t = ilash_top_x + line_width;
	pre_y_t = ilash_top_y + line_width;
	pre_x_b = ilash_top_x - line_width;
	pre_y_b = ilash_top_y - line_width;
	float ilash_offset_x = randf(offset) - offset * 0.5;
	float ilash_offset_y = randf(offset) - offset * 0.5;
	drawCircle(ilash_top_x + ilash_offset_x, ilash_top_y + ilash_offset_y, line_width*sqrt(2));
	int iter = 5;
	for (int i = 1; i <= 5; i++) {
		line_width += randf(2 * std) - std;
		float x = ilash_top_x + (ilash_bot_x - ilash_top_x)*i / (float)5;
		float y = ilash_top_y + (ilash_bot_y - ilash_top_y)*i / (float)5;
		float noise_x = randf(0.02);
		float noise_y = randf(0.02);
		x += noise_x;
		y += noise_y;
		float x_t = x + line_width;
		float y_t = y + line_width;
		float x_b = x - line_width;
		float y_b = y - line_width;
		glBegin(GL_POLYGON);
		glVertex2f(pre_x_t + ilash_offset_x, pre_y_t + ilash_offset_y);
		glVertex2f(x_t + ilash_offset_x, y_t + ilash_offset_y);
		glVertex2f(x_b + ilash_offset_x, y_b + ilash_offset_y);
		glVertex2f(pre_x_b + ilash_offset_x, pre_y_b + ilash_offset_y);
		glEnd();
		pre_x_t = x_t;
		pre_y_t = y_t;
		pre_x_b = x_b;
		pre_y_b = y_b;
	}
	drawCircle(0.5*(pre_x_t + pre_x_b) + ilash_offset_x, 0.5*(pre_y_t + pre_y_b) + ilash_offset_y, line_width*sqrt(2));
}

void draw_tri(void) {
	float line_width = 0.02;
	float std = line_width * 0.1;
	float scale_mag = randrange(0.9, 1.1);
	float scale_x = scale_mag * randrange(0.9, 1.2);
	float scale_y = scale_mag * randrange(0.9, 1.2);
	float offset_x = 2.2*(randf(1 - scale_x) - 0.5 * (1 - scale_x))*offset_factor;
	float offset_y = 1.4*(randf(1 - scale_x) - 0.5 * (1 - scale_y) - 0.05)*offset_factor;
	glColor3f(0, 0, 0);
	int inert = 4;
	float deg1 = randf(1) + inert;
	float deg2 = randf(1) + inert;
	float deg3 = randf(1) + inert;
	float tot = deg1 + deg2 + deg3;
	deg1 /= tot;
	deg2 /= tot;
	deg3 /= tot;
	float len1 = 2 * scale_mag * deg1;
	float len2 = 2 * scale_mag * deg2;
	float len3 = 2 * scale_mag * deg3;
	deg1 *= 2 * M_PI;
	deg2 *= 2 * M_PI;
	deg3 *= 2 * M_PI;
	float deg_offset = randf(0.3) + M_PI_2 - 0.15;
	float pts[3][2] = { { offset_x + scale_x * len1 * cosf(deg_offset + 0), offset_y + scale_y * len1 * sinf(deg_offset + 0) },
						{ offset_x + scale_x * len2 * cosf(deg_offset + deg1), offset_y + scale_y * len2 * sinf(deg_offset + deg1) },
						{ offset_x + scale_x * len3 * cosf(deg_offset + deg1 + deg2), offset_y + scale_y * len3 * sinf(deg_offset + deg1 + deg2) } };
	glColor3f(0, 0, 0);
	float pos[2] = { pts[0][0], pts[0][1] };
	float noise[2] = { 0, 0 };
	float radious = 0.03;
	for (int j = 0; j < 3; j++) {
		int iter = 50;
		float noiseMag = 0.005;
		for (int i = 1; i <= iter; i++) {
			noise[0] += randf(noiseMag) - 0.5*noiseMag;
			noise[1] += randf(noiseMag) - 0.5*noiseMag;
			pos[0] = pts[j][0] + (pts[(j + 1) % 3][0] - pts[j][0]) * i / (float)iter;
			pos[1] = pts[j][1] + (pts[(j + 1) % 3][1] - pts[j][1]) * i / (float)iter;
			drawCircle(pos[0] + noise[0], pos[1] + noise[1], radious);
			radious += randf(0.003) - 0.0014;
		}
	}
}

void draw_table(void) {
	float line_width = PIX_WIDTH / NUM_ROWS / 30;
	if (line_width < 1) {
		line_width = 1;
	}
	glColor4f(0, 0, 0, 1);
	for (int i = 0; i <= NUM_ROWS; i++) {
		float y = PIX_HEIGHT * i / (float)NUM_ROWS;
		glBegin(GL_POLYGON);
		glVertex2f(0, y - line_width);
		glVertex2f(PIX_WIDTH, y - line_width);
		glVertex2f(PIX_WIDTH, y + line_width);
		glVertex2f(0, y + line_width);
		glEnd();
		for (int j = 0; j <= NUM_COLS; j++) {
			float x = PIX_WIDTH * j / (float)NUM_COLS;
			glBegin(GL_POLYGON);
			glVertex2f(x + line_width, 0);
			glVertex2f(x + line_width, PIX_HEIGHT);
			glVertex2f(x - line_width, PIX_HEIGHT);
			glVertex2f(x - line_width, 0);
			glEnd();
		}
	}
}

void fill_table(void) {
	float pad = 1.1;
	glColor4f(0, 0, 0, 1);
	float half_x = PIX_WIDTH / NUM_COLS;
	float half_y = PIX_HEIGHT / NUM_ROWS;
	for (int i = 0; i < NUM_COLS; i++) {
		for (int j = 0; j < NUM_ROWS; j++) {
			glPushMatrix();
			glTranslatef(half_x*0.5 + PIX_WIDTH * i / NUM_COLS, half_y*0.5 + PIX_HEIGHT * j / NUM_ROWS, 0);
			glScalef(PIX_WIDTH / NUM_COLS / 2 / (PAD_RATIO+1) / pad, PIX_HEIGHT / NUM_ROWS / 2 / (PAD_RATIO+1) / pad, 1);
			int r = int(rand() / (float)RAND_MAX * 4);
			switch (r) {
			case 0:
				draw_o();
				break;
			case 1:
				draw_x();
				break;
			case 2:
				draw_tri();
				break;
			case 3:
				break;
			}
			glPopMatrix();
		}
	}
}
