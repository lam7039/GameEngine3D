#ifndef BITMAP_H
#define BITMAP_H

SE_BEGIN_NAMESPACE

class Bitmap {
public:
	BYTE* LoadBMP(int* width, int* height, long* size, LPCTSTR bmpfile);
	void TestBMPCopy(LPCTSTR input, LPCTSTR output);
	void TestBMPCopy2(LPCTSTR input, LPCTSTR output);


};


SE_END_NAMESPACE


#endif