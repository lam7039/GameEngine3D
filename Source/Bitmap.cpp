#include <Windows.h>
#include "Bitmap.h"

namespace se {

	BYTE *Bitmap::LoadBMP(int *width, int *height, long *size, const std::string &bmpfile) {
		BITMAPFILEHEADER bmpheader;
		BITMAPINFOHEADER bmpinfo;
		DWORD bytesRead;
		HANDLE file = CreateFile(bmpfile.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
		if (file == NULL)
			return NULL;

		if (!ReadFile(file, &bmpheader, sizeof(BITMAPFILEHEADER), &bytesRead, NULL) ||
			!ReadFile(file, &bmpinfo, sizeof(BITMAPINFOHEADER), &bytesRead, NULL) ||
			bmpheader.bfType != 'MB' || 
			bmpinfo.biCompression != BI_RGB ||
			bmpinfo.biBitCount != 24) {
			CloseHandle(file);
			return NULL;
		}

		*width = bmpinfo.biWidth;
		*height = abs(bmpinfo.biHeight);
		*size = bmpheader.bfSize - bmpheader.bfOffBits;

		BYTE *Buffer = new BYTE[*size];
		SetFilePointer(file, bmpheader.bfOffBits, NULL, FILE_BEGIN);
		if (!ReadFile(file, Buffer, *size, &bytesRead, NULL))
		{
			delete[] Buffer;
			CloseHandle(file);
			return NULL;
		}

		CloseHandle(file);
		return Buffer;
	}

	//TODO: Niels, implement ConvertBMPToRGBBuffer

	void Bitmap::TestBMPCopy(const std::string &input, const std::string &output)
	{
		int x, y;
		long s;
		BYTE *a = LoadBMP(&x, &y, &s, input);
		//BYTE *b = ConvertBMPToRGBBuffer(a, x, y);
		delete[] a;
		//delete[] b;
	}
	//TestBMPCopy2("test.bmp", "copy.bmp");

}