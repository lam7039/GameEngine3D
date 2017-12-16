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

	BYTE* ConvertBMPToRGBBuffer(BYTE* Buffer, int width, int height)
	{
		if ((NULL == Buffer) || (width == 0) || (height == 0))
			return NULL;

		int padding = 0;
		int scanlinebytes = width * 3;
		while ((scanlinebytes + padding) % 4 != 0)  
			padding++;
		int psw = scanlinebytes + padding;

		BYTE* newbuf = new BYTE[width*height * 3];

		long bufpos = 0;
		long newpos = 0;
		for (int y = 0; y < height; y++)
			for (int x = 0; x < 3 * width; x += 3)
			{
				newpos = y * 3 * width + x;
				bufpos = (height - y - 1) * psw + x;

				newbuf[newpos] = Buffer[bufpos + 2];
				newbuf[newpos + 1] = Buffer[bufpos + 1];
				newbuf[newpos + 2] = Buffer[bufpos];
			}

		return newbuf;
	}


	void Bitmap::TestBMPCopy(const std::string &input, const std::string &output)
	{
		int x, y;
		long s;
		BYTE *a = LoadBMP(&x, &y, &s, input);
		BYTE *b = ConvertBMPToRGBBuffer(a, x, y);
		delete[] a;
		//delete[] b;
	}
	//TestBMPCopy2("test.bmp", "copy.bmp");
	void TestBMPCopy2(LPCTSTR input, LPCTSTR output)
	{
		int x, y;
		long s, s2;
		BYTE* a = LoadBMP(&x, &y, &s, input);
		BYTE* b = ConvertBMPToRGBBuffer(a, x, y);
		//BYTE* c = ConvertRGBToBMPBuffer(b, x, y, &s2);
		SaveBMP(c, x, y, s2, output);
		delete[] a;
		delete[] b;
		//delete[] c;
	}

	void main()
	{
		TestBMPCopy2("lena_gray.bmp", "copy.bmp");
	}
}