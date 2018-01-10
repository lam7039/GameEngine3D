#include <Windows.h>
#include <fstream>
#include "Bitmap.h"

namespace se {

	Bitmap::Bitmap() {
		m_logger.SelectLogger("engine.log");
	}

	Bitmap::~Bitmap() {
		delete[] m_pixels;
	}

	//TODO: bmp loads upside down
	//TODO: bmp loads spike (255) from file for some reason
	int Bitmap::LoadBMP(const std::string &bmpFile) {
		unsigned char *datBuff[2]{ nullptr, nullptr };
		m_pixels = nullptr;

		BITMAPFILEHEADER *bmpHeader = nullptr;
		BITMAPINFOHEADER *bmpInfo = nullptr;

		std::ifstream file(bmpFile, std::ios::binary);
		if (!file) {
			m_logger.Log(2, __FILE__, __LINE__, "Failed to open bitmap file");
			return 1;
		}

		datBuff[0] = new unsigned char[sizeof(BITMAPFILEHEADER)];
		datBuff[1] = new unsigned char[sizeof(BITMAPINFOHEADER)];

		file.read((char*)datBuff[0], sizeof(BITMAPFILEHEADER));
		file.read((char*)datBuff[1], sizeof(BITMAPINFOHEADER));

		bmpHeader = (BITMAPFILEHEADER*)datBuff[0];
		bmpInfo = (BITMAPINFOHEADER*)datBuff[1];

		if (bmpHeader->bfType != 0x4D42) {
			m_logger.Log(2, __FILE__, __LINE__, "File location isn't a bitmap file");
			return 2;
		}

		unsigned long sizeImage = bmpInfo->biWidth * bmpInfo->biHeight * bmpInfo->biBitCount;
		m_pixels = new unsigned char[sizeImage];

		file.seekg(bmpHeader->bfOffBits);
		file.read((char*)m_pixels, sizeImage);

		//Convert BGR to RGB
		unsigned char tmpRGB = 0;
		for (unsigned long i = 0; i < sizeImage; i += 3) {
			tmpRGB = m_pixels[i];
			m_pixels[i] = m_pixels[i + 2];
			m_pixels[i + 2] = tmpRGB;
		}

		m_width = bmpInfo->biWidth;
		m_height = bmpInfo->biHeight;

		file.close();

		delete[] datBuff[0];
		delete[] datBuff[1];

		return 0;
	}

	const unsigned int Bitmap::GetWidth() const {
		return m_width;
	}

	const unsigned int Bitmap::GetHeight() const {
		return m_height;
	}

	unsigned char *Bitmap::GetPixels() {
		return m_pixels;
	}
}