#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdint.h>
#include <windows.h>

using namespace std;

//Variant: 5

void hide_byte_into_pixel(RGBQUAD *pixel, uint8_t hide_byte)
{
	pixel->rgbBlue &= (0xFC);
	pixel->rgbBlue |= (hide_byte >> 6) & 0x3;
	pixel->rgbGreen &= (0xFC);
	pixel->rgbGreen |= (hide_byte >> 4) & 0x3;
	pixel->rgbRed &= (0xFC);
	pixel->rgbRed |= (hide_byte >> 2) & 0x3;
	pixel->rgbReserved &= (0xFC);
	pixel->rgbReserved |= (hide_byte) & 0x3;
}

uint8_t get_byte_from_pixel(RGBQUAD *pixel)
{
	uint8_t hide_byte;
	hide_byte = pixel->rgbBlue & 0x3;
	hide_byte = hide_byte << 2;
	hide_byte |= pixel->rgbGreen & 0x3;
	hide_byte = hide_byte << 2;
	hide_byte |= pixel->rgbRed & 0x3;
	hide_byte = hide_byte << 2;
	hide_byte |= pixel->rgbReserved & 0x3;
	return hide_byte;
}

void hiding(string inputfile, string secret_text_file, string outputfile)
{
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBQUAD pixel;
	uint8_t byte_to_hide;

	FILE *picture = fopen(inputfile.c_str(), "rb");
	fread(&fileheader, sizeof(fileheader), 1, picture);
	fread(&infoheader, sizeof(infoheader), 1, picture);

	FILE *secret_text = fopen(secret_text_file.c_str(), "rb");

	FILE *newPicture = fopen(outputfile.c_str(), "wb");
	fwrite(&fileheader, sizeof(fileheader), 1, newPicture);
	fwrite(&infoheader, sizeof(infoheader), 1, newPicture);

	int picture_size = infoheader.biWidth * infoheader.biHeight;
	for (int i = 0; i < picture_size; i++)
	{
		if (fread(&byte_to_hide, 1, 1, secret_text) != 1)
		{
			byte_to_hide = 0xFF;
		}
		fread(&pixel, sizeof(pixel), 1, picture);
		hide_byte_into_pixel(&pixel, byte_to_hide);
		fwrite(&pixel, sizeof(pixel), 1, newPicture);
	}

	fclose(secret_text);
	fclose(newPicture);
	cout << "Information hiding completed" << endl;
}

void extraction(string inputfile, string outputfile)
{
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBQUAD pixel;
	uint8_t hide_byte = 0x00;

	FILE *picture = fopen(inputfile.c_str(), "rb");
	fread(&fileheader, sizeof(fileheader), 1, picture);
	fread(&infoheader, sizeof(infoheader), 1, picture);

	FILE *secret_text = fopen(outputfile.c_str(), "wb");
	
	while (hide_byte != 0xFF)
	{
		fread(&pixel, sizeof(pixel), 1, picture);
		hide_byte = get_byte_from_pixel(&pixel);
		if (hide_byte != 0xFF)
		{
			fwrite(&hide_byte, 1, 1, secret_text);
		}
	}

	fclose(secret_text);
	fclose(picture);
	cout << "Information extraction completed" << endl;
}

int main()
{
	hiding("5.bmp", "some_text.txt", "my_5.bmp");
	extraction("my_5.bmp", "text_from_my_picture.txt");
	extraction("5.bmp", "text_from_picture.txt");
	system("pause");
	return 0;
}