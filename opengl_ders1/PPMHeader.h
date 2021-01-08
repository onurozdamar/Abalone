
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include <GL/glut.h>

using namespace std;

#define OFF_MODEL "m1779/m1779.off"
#define TEXTURE_FILE "texture2.ppm"

GLint noktaSayisi = 0, yuzeySayisi = 0;
class wrldPtf {
public:
	GLfloat x, y, z;
};
class wrldFci {
public:
	GLint n1, n2, n3;
};

wrldPtf* noktalar;
wrldFci* yuzeyler;
GLubyte* texArray;
int width, height, color;

void loadOFFModel(char* fileName) {
	int const satirUzunluk = 200;
	char satir[satirUzunluk];
	ifstream modelFile;
	modelFile.open(fileName, ios::in);
	modelFile.getline(satir, satirUzunluk);

	if (strcmp(satir, "OFF") == 0) {
		//Gecerli bir OFF dosyasi alindi...
		modelFile.getline(satir, satirUzunluk);
		const char bosluk = ' ';
		char* next;
		noktaSayisi = atoi(strtok_s(satir, &bosluk, &next));
		yuzeySayisi = atoi(strtok_s(NULL, &bosluk, &next));
		noktalar = new wrldPtf[noktaSayisi];
		yuzeyler = new wrldFci[yuzeySayisi];
		//Noktalar okunuyor...
		for (int nokta = 0; nokta < noktaSayisi; nokta++) {
			modelFile.getline(satir, satirUzunluk);
			wrldPtf n;
			char* temp1 = strtok_s(satir, &bosluk, &next);
			char* temp2 = strtok_s(NULL, &bosluk, &next);
			char* temp3 = strtok_s(NULL, &bosluk, &next);

			n.x = atof((const char*)temp1);
			n.y = atof((const char*)temp2);
			n.z = atof((const char*)temp3);
			noktalar[nokta] = n;
		}
		//Yuzeyler okunuyor...
		for (int yuzey = 0; yuzey < yuzeySayisi; yuzey++) {
			modelFile.getline(satir, satirUzunluk);
			wrldFci n;

			char* temp = strtok_s(satir, &bosluk, &next);
			char* temp1 = strtok_s(NULL, &bosluk, &next);
			char* temp2 = strtok_s(NULL, &bosluk, &next);
			char* temp3 = strtok_s(NULL, &bosluk, &next);

			n.n1 = atoi((const char*)temp1);
			n.n2 = atoi((const char*)temp2);
			n.n3 = atoi((const char*)temp3);
			yuzeyler[yuzey] = n;
		}
	}
	modelFile.close();
}

void readTex(char* fileName) {
	ifstream texFile;
	texFile.open(fileName, ios::in);
	int const satirUzunluk = 500;
	char satir[satirUzunluk];
	char* next;
	char* token;
	texFile.getline(satir, satirUzunluk);
	char* imgType = strtok_s(satir, " ", &next);

	const char bosluk = ' ';
	texFile.getline(satir, satirUzunluk);
	token = strtok_s(satir, &bosluk, &next);

	if (token != 0)
		width = atoi(token);
	token = strtok_s(NULL, &bosluk, &next);
	if (token != 0)
		height = atoi(token);
	texFile.getline(satir, satirUzunluk);
	token = strtok_s(satir, &bosluk, &next);
	if (token != 0)
		color = atoi(token);
	int i = 0, j = 0, k = 0;
	int array_size = width * height * color;
	texArray = new GLubyte[array_size];

	unsigned int temp;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			for (k = 0; k < 3; k++) {
				texFile.getline(satir, satirUzunluk);
				token = strtok_s(satir, &bosluk, &next);
				if (token != NULL) {
					unsigned char value = atoi(token);
					texArray[i * width * 3 + j * 3 + k] = (GLubyte)value;
				}
			}
			//texArray[j][i][3]= (unsigned char) 120;  //ALPHA DEÐERÝ ÝÇÝN
		}
	}

	texFile.close();
}
