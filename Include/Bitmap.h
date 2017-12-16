#ifndef BITMAP_H
#define BITMAP_H

#include "std.h"

namespace se {

	class Bitmap {
	public:
		BYTE *LoadBMP(int *width, int *height, long *size, const std::string &bmpfile);
		void TestBMPCopy(const std::string &input, const std::string &output);
		BYTE* ConvertBMPToRGBBuffer(BYTE* Buffer, int width, int height);
		void TestBMPCopy2(LPCTSTR input, LPCTSTR output);
	};

}


#endif