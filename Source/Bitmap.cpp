//bitmap source

#include <Windows.h>
#include "Bitmap.h"

namespace se {

	BYTE* Bitmap::LoadBMP(int* width, int* height, long* size, const std::string &bmpfile) {
		BITMAPFILEHEADER bmpheader;
		BITMAPINFOHEADER bmpinfo;
		DWORD bytesread;
		HANDLE file = CreateFile(bmpfile.c_str(), GENERIC_READ, FILE_SHARE_READ,
			NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
		if (NULL == file)
			return NULL;

		if (ReadFile(file, &bmpheader, sizeof(BITMAPFILEHEADER), &bytesread, NULL) == false)
		{
			CloseHandle(file);
			return NULL;
		}

		if (ReadFile(file, &bmpinfo, sizeof(BITMAPINFOHEADER), &bytesread, NULL) == false)
		{
			CloseHandle(file);
			return NULL;
		}

		if (bmpheader.bfType != 'MB')
		{
			CloseHandle(file);
			return NULL;
		}

		*width = bmpinfo.biWidth;
		*height = abs(bmpinfo.biHeight);

		if (bmpinfo.biCompression != BI_RGB)
		{
			CloseHandle(file);
			return NULL;
		}

		if (bmpinfo.biBitCount != 24)
		{
			CloseHandle(file);
			return NULL;
		}

		*size = bmpheader.bfSize - bmpheader.bfOffBits;
		BYTE* Buffer = new BYTE[*size];
		SetFilePointer(file, bmpheader.bfOffBits, NULL, FILE_BEGIN);
		if (ReadFile(file, Buffer, *size, &bytesread, NULL) == false)
		{
			delete[] Buffer;
			CloseHandle(file);
			return NULL;
		}

		CloseHandle(file);

		return Buffer;
	}

	//TODO: Niels, implement SaveBMP and ConvertBMPToRGBBuffer

	void Bitmap::TestBMPCopy(const std::string &input, const std::string &output)
	{
		int x, y;
		long s;
		BYTE* b = LoadBMP(&x, &y, &s, input);
		//SaveBMP(b, x, y, s, output); 
		delete[] b;
	}

	void Bitmap::TestBMPCopy2(const std::string &input, const std::string &output)
	{
		int x, y;
		long s, s2;
		BYTE* a = LoadBMP(&x, &y, &s, input);
		//BYTE* b = ConvertBMPToRGBBuffer(a, x, y);
		//BYTE* c = ConvertRGBToBMPBuffer(b, x, y, &s2);
		//SaveBMP(c, x, y, s2, output.c_str());
		delete[] a;
		//delete[] b;
		//delete[] c;
	}
	//TestBMPCopy2(L"test.bmp", L"copy.bmp");

}