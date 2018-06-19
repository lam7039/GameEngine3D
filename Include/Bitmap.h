#ifndef BITMAP_H
#define BITMAP_H

#include <string>
#include "Debug.h"
#include "Vector3.h"

namespace se {
	///
	/// With this class you can load a bitmap.
	///
	class Bitmap {
	public:
		Bitmap();
		~Bitmap();
		///
		/// Load the bitmap with the file path.
		///
		int LoadBMP(const std::string &bmpFile);
		///
		/// Get the given bitmap size.
		///
		const Vector3i GetSize() const;
		///
		/// Get an array with values of 0-255 loaded from the bitmap from a single channel.
		///
		unsigned char *GetData() const;
		///
		/// Get an array with values of 0-255 loaded from the bitmap from all channels.
		///
		unsigned char *GetPixels() const;
	private:
		Vector3i m_size;
		unsigned char *m_pixels;
		unsigned char *m_data;
		Debug m_logger;
	};

}


#endif