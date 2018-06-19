#include <Windows.h>
#include <fstream>
#include "Bitmap.h"

namespace se {

	Bitmap::Bitmap() {
		m_data = nullptr;
		m_pixels = nullptr;
		m_logger.SelectLogger("engine.log");
	}

	Bitmap::~Bitmap() {
		delete[] m_data;
		delete[] m_pixels;
	}

	int Bitmap::LoadBMP(const std::string &bmpFile) {
		unsigned char *datBuff[2]{ nullptr, nullptr };

		BITMAPFILEHEADER *bmpHeader = nullptr;
		BITMAPINFOHEADER *bmpInfo = nullptr;

		std::ifstream file(bmpFile, std::ios::binary);
		if (!file) {
			m_logger.Log(ERRORTYPE_ERROR, __FILE__, __LINE__, "Failed to open bitmap file");
			return 1;
		}

		datBuff[0] = new unsigned char[sizeof(BITMAPFILEHEADER)];
		datBuff[1] = new unsigned char[sizeof(BITMAPINFOHEADER)];

		file.read((char*)datBuff[0], sizeof(BITMAPFILEHEADER));
		file.read((char*)datBuff[1], sizeof(BITMAPINFOHEADER));

		bmpHeader = (BITMAPFILEHEADER*)datBuff[0];
		bmpInfo = (BITMAPINFOHEADER*)datBuff[1];

		if (bmpHeader->bfType != 0x4D42) {
			m_logger.Log(ERRORTYPE_ERROR, __FILE__, __LINE__, "File location isn't a bitmap file");
			file.close();
			return 2;
		}

		if (bmpInfo->biBitCount != 24) {
			m_logger.Log(ERRORTYPE_ERROR, __FILE__, __LINE__, "Bitmap is not 24 bit");
			file.close();
			return 3;
		}

		m_size.x = bmpInfo->biWidth;
		m_size.y = bmpInfo->biHeight;

		unsigned long sizeImage = m_size.x * m_size.y * 4;
		m_pixels = new unsigned char[sizeImage];
		m_data = new unsigned char[sizeImage / 4];
		file.seekg(bmpHeader->bfOffBits);
		file.read((char*)m_pixels, sizeImage);

		int padding = 4 - ((m_size.x * bmpInfo->biBitCount / 8) % 4);
		unsigned long i = 0;
		unsigned long j = 0;

		unsigned char tmpRGB = 0;
		for (unsigned long y = 0; y < m_size.y; y++) {
			for (unsigned long x = 0; x < m_size.x; x++) {
				tmpRGB = m_pixels[i];
				m_pixels[i] = m_pixels[i + 2];
				m_pixels[i + 2] = tmpRGB;
				m_data[j] = (m_pixels[i] + m_pixels[i + 1] + m_pixels[i + 2]) / 3;
				i += 3;
				j++;
			}
			i += padding;
		}

		file.close();
		delete[] datBuff[0];
		delete[] datBuff[1];

		return 0;
	}

	const Vector3i Bitmap::GetSize() const {
		return m_size;
	}

	unsigned char *Bitmap::GetData() const {
		return m_data;
	}

	unsigned char *Bitmap::GetPixels() const {
		return m_pixels;
	}
}