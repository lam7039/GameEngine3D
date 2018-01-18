#ifndef BITMAP_H
#define BITMAP_H

#include "std.h"
#include "Debug.h"

namespace se {
	///
	/// With this class you can load a bitmap
	///
	class Bitmap {
	public:
		Bitmap();
		~Bitmap();
		///
		/// Load the bitmap with the file path
		///
		int LoadBMP(const std::string &bmpFile);
		///
		/// Get the given bitmap width
		///
		const unsigned int GetWidth() const;
		///
		/// Get the given bitmap height
		///
		const unsigned int GetHeight() const;
		///
		/// Get an array with values of 0-255 loaded from the bitmap from a single channel
		///
		unsigned char *GetData();
		///
		/// Get an array with values of 0-255 loaded from the bitmap from all channels
		///
		unsigned char *GetPixels();
	private:
		unsigned int m_width;
		unsigned int m_height;
		unsigned char *m_pixels;
		unsigned char *m_data;
		Debug m_logger;
	};

}


#endif