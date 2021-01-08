#include<stdio.h>
#include<tchar.h>
#include<Windows.h>
#include<GL/glut.h>
#include<math.h>
#include<iostream>
#include<stdlib.h>
#include <vector>
#include"GameManager.h"

#define PI 3.14159265

/* Baþlangýç gösterim penceresi boyutu */
GLsizei pencereEni = 800, pencereBoyu = 700;

GameManager gameManager;

static void init(void)
{
	Renk arkaPlan(26, 23, 23);
	glClearColor(arkaPlan.getRed(), arkaPlan.getGreen(), arkaPlan.getBlue(), arkaPlan.getAlpha());		// siyah renkte gösterim penceresi
	glMatrixMode(GL_PROJECTION);		// projeksiyon parametrelerini ayarla
	glLoadIdentity();
	gluOrtho2D(0, 200, 0, 200);

	gameManager.setup();
}

void hexagon() {
	// ekrana altýgen  çizer
	int angle = 0;
	float x, y, r = GameManager::CELL_SIZE * 5.5;

	Renk altigenRengi(95, 47, 49);
	glColor3f(altigenRengi.getRed(), altigenRengi.getGreen(), altigenRengi.getBlue());

	glBegin(GL_POLYGON);
	for (int i = 0; i < 6; i++) {
		x = cos(angle * PI / 180) * r + GameManager::CELL_SIZE * 5.5 + GameManager::OFFSETX;
		y = sin(angle * PI / 180) * r + pencereBoyu / 2;
		angle += 60;
		glVertex2f(x, y);
	}
	glEnd();
}
void gosterimFonk() {
	glClear(GL_COLOR_BUFFER_BIT);

	hexagon();

	gameManager.drawCells();

	glutSwapBuffers();
	glFlush();
}
void pencereYenidenSekillendir(int yeniEn, int yeniBoy) {
	//Bakýþ güvertesi (view port) ve projeksiyon parametrelerini ayarla
	glViewport(0, 0, yeniEn, yeniBoy);
	glMatrixMode(GL_PROJECTION);		// projeksiyon parametrelerini ayarla
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble)yeniEn, 0, (GLdouble)yeniBoy);
	// Mevcut pencere eni ve boyunu güncelle
	pencereEni = yeniEn;
	pencereBoyu = yeniBoy;
}
void mousePressed(GLint button, GLint action, GLint xMouse, GLint yMouse)
{

	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		gameManager.mousePressed(xMouse, pencereBoyu - yMouse);
	}
	else if (button == GLUT_RIGHT_BUTTON) //Programdan çýk
		exit(0);

	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, (char**)argv);  // GLUT'u baþlat
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //gösterim modunu ayarla
	glutInitWindowPosition(100, 100); // Pencerenin sol üst ekran köþesinden uzaklýðýný ayarla
	glutInitWindowSize(pencereEni, pencereBoyu);   // Pencere boyunu ayarla
	glutCreateWindow("Abalone");	// Verilen baþlýkla pencereyi oluþtur
	init();							//Ýlklendirmeyi çalýþtýr
	glutDisplayFunc(gosterimFonk); // Yeniden pencere çizimleri için gösterim geri bildirim fonksiyonunu kayýtla
	glutReshapeFunc(pencereYenidenSekillendir);
	glutMouseFunc(mousePressed);

	glutMainLoop();           // Sonsuz bir þekilde süreç iþlem döngüsüne gir

	return 0;
}