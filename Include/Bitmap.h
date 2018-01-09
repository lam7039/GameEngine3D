#ifndef BITMAP_H
#define BITMAP_H

#include "std.h"

namespace se {

	class Bitmap {
	public:
		~Bitmap();
		int LoadBMP(const std::string &bmpFile);
		const unsigned int GetWidth() const;
		const unsigned int GetHeight() const;
		unsigned char *GetPixels();
	private:
		unsigned int m_width;
		unsigned int m_height;
		unsigned char *m_pixels;
	};

}


#endif