#ifndef BITMAP_H
#define BITMAP_H

#include "std.h"
#include "Debug.h"

namespace se {

	class Bitmap {
	public:
		Bitmap();
		~Bitmap();
		int LoadBMP(const std::string &bmpFile);
		const unsigned int GetWidth() const;
		const unsigned int GetHeight() const;
		unsigned char *GetData();
	private:
		unsigned int m_width;
		unsigned int m_height;
		unsigned char *m_data;
		Debug m_logger;
	};

}


#endif