#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

void resizeImage(char *inputfilename, char *outputFilename, char *resizeNumber);
void findNewWidthAndHeight(unsigned char header[54]);
int findPadding(int width);
void imageColor();
void getColor(char &blue, char &green, char &red);
void putColor(char blue, char green, char red);
void readHeader(unsigned char header[54]);
void findOldHeightAndWidth(unsigned char header[54]);

using namespace std;

int resize = 0;
int height = 0;
int width = 0;
int newHeight = 0;
int newWidth = 0;
char ch;
ifstream inputFile;
ofstream outputFile;


int main(int argc, char* argv[])
{
	resizeImage(argv[1], argv[2], argv[3]);

	return 0;
}

void resizeImage(char *inputfilename, char *outputFilename, char *resizeNumber)
{
	unsigned char header[54];
	inputFile.open(inputfilename, ios::binary);
	outputFile.open(outputFilename, ios::binary);
	resize = atoi(resizeNumber);
	if (inputFile.is_open() && outputFile.is_open()) {
		for (int i = 0; i < 54; i++) {
			inputFile.get(ch);
			header[i] = ch;
		}
		findNewWidthAndHeight(header);
		imageColor();
	}
	else
	{
		cout << "File is not open";
	}
	inputFile.close();
	outputFile.close();

}

void findNewWidthAndHeight(unsigned char header[54]) {
	readHeader(header);
	findOldHeightAndWidth(header);
	for (int j = 0; j < 4; j++) {
		newWidth = width * resize;
		int newW = newWidth / pow(256, j);
		outputFile.put(newW);
	}
	for (int j = 0; j < 4; j++) {
		newHeight = height * resize;
		int newH = newHeight / pow(256, j);
		outputFile.put(newH);
	}
	for (int i = 26; i < 54; i++) {
		ch = header[i];
		outputFile.put(ch);
	}
}

int findPadding(int width) {
	int padding = 0;
	while ((width * 3 + padding) % 4 != 0) {
		padding++;
	};
	return padding;
}

void putColor(char blue, char green, char red) {
	outputFile.put(blue);
	outputFile.put(green);
	outputFile.put(red);
}

void getColor(char &blue, char &green, char &red) {
	inputFile.get(blue);
	inputFile.get(green);
	inputFile.get(red);
}

void imageColor() {
	char blue, green, red;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < resize; j++) {
			for (int k = 0; k < width; k++) {
				getColor(blue, green, red);
				for (int l = 0; l < resize; l++) {
					putColor(blue, green, red);
				}
			}
			int oldPadding, newPadding;
			oldPadding = findPadding(width);
			newPadding = findPadding(newWidth);
			for (int k = 0; k < oldPadding; k++) {
				inputFile.get(ch);
			}
			for (int k = 0; k < newPadding; k++) {
				outputFile.put(ch);
			}
			inputFile.seekg(54 + i * (width * 3 + oldPadding));
		}
	}
}

void readHeader(unsigned char header[54]) {
	for (int i = 0; i < 18; i++) {
		ch = header[i];
		outputFile.put(ch);
	}
}

void findOldHeightAndWidth(unsigned char header[54]) {
	for (int i = 0; i < 4; i++) {
		ch = header[18 + j];
		width += ch * pow(256, j);
		ch = header[22 + j];
		height += ch * pow(256, j);
	}
}
