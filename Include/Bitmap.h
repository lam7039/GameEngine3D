#ifndef BITMAP_H
#define BITMAP_H

#include "std.h"

namespace se {

	class Bitmap {
	public:
		BYTE* LoadBMP(int* width, int* height, long* size, LPCTSTR bmpfile);
		void TestBMPCopy(LPCTSTR input, LPCTSTR output);
		void TestBMPCopy2(LPCTSTR input, LPCTSTR output);


	};


}


#endif