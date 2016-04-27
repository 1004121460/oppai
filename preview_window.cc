#ifdef SLIDERTEST

#include "preview_window.h"
#ifdef _WIN32
#define NEEDS_TO_INSTALL_GENTOO
#include <Windows.h>
#endif
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <string.h>
#include <unistd.h>

namespace {
	// yes this is extremely bad and slow but I don't care, it's just for testin
	const i32 screen_w = 512, screen_h = 384;
	u8 pixels[screen_w * screen_h][3];

	void slider_display() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawPixels(screen_w, screen_h, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		glutSwapBuffers();
	}

	bool showing_slider;
	void slider_keyboard(u8 key, i32 x, i32 y) {
		showing_slider = false;
	}

	u8* get_px(const v2f& pos) {
		i32 int_x = (int)pos.x;
		i32 int_y = (int)pos.y;

		if (int_x < 0 || int_x >= screen_w || int_y < 0 || int_y >= screen_h) {
			return nullptr;
		}

		return (u8*)pixels[(screen_h - (i32)int_y - 1) 
			* screen_w + (i32)int_x];
	}

	void shigeZZZ(u64 ms) {
#ifdef NEEDS_TO_INSTALL_GENTOO
		puts("INSTALL GENTOO");
		Sleep(ms);
#else
		usleep(ms * 1000);
#endif
	}
}

void p_init(int& argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(screen_w, screen_h);
	glutCreateWindow("preview");
	glutDisplayFunc(slider_display);
	glutIdleFunc(slider_display);
	glutKeyboardFunc(slider_keyboard);
					
	glClearColor(0.f, 0.f, 0.f, 1.f);
}

void p_cls() {
	memset(pixels, 0, screen_w * screen_h * sizeof(pixels[0][0]) * 3);
}

u8* p_get_px(const v2f& pos) {
	return get_px(pos);
}

void p_put_px(const v2f& pos, u8 r, u8 g, u8 b) {
	auto px = get_px(pos);
	if (!px) {
		return;
	}
	px[0] = r;
	px[1] = g;
	px[2] = b;
}

void p_show() {
	showing_slider = true;
	while (showing_slider) {
		glutMainLoopEvent();
		glutPostRedisplay();
		shigeZZZ(50);
	}
}
#endif