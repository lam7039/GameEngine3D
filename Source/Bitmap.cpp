#include <Windows.h>
#include <fstream>
#include <iostream>
#include "Bitmap.h"

namespace se {

	Bitmap::Bitmap() {
		m_logger.SelectLogger("engine.log");
	}

	Bitmap::~Bitmap() {
		delete[] m_data;
	}

	//int Bitmap::LoadBMP(const std::string &bmpFile) {
	//	BITMAPFILEHEADER bmpHeader;
	//	BITMAPINFOHEADER bmpInfo;
	//	DWORD bytesRead;

	//	HANDLE file = CreateFile(bmpFile.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	//	if (file == NULL) {
	//		m_logger.Log(2, __FILE__, __LINE__, "Failed to load file");
	//		return 1;
	//	}

	//	if (!ReadFile(file, &bmpHeader, sizeof(BITMAPFILEHEADER), &bytesRead, NULL)) {
	//		CloseHandle(file);
	//		m_logger.Log(2, __FILE__, __LINE__, "Failed to read file header");
	//		return 2;
	//	}

	//	if (!ReadFile(file, &bmpInfo, sizeof(BITMAPINFOHEADER), &bytesRead, NULL)) {
	//		CloseHandle(file);
	//		m_logger.Log(2, __FILE__, __LINE__, "Failed to read file info");
	//		return 3;
	//	}

	//	if (bmpHeader.bfType != 0x4D42) {
	//		m_logger.Log(2, __FILE__, __LINE__, "File is not of bitmap type");
	//		CloseHandle(file);
	//		return 4;
	//	}

	//	if (bmpInfo.biBitCount != 24) {
	//		m_logger.Log(2, __FILE__, __LINE__, "Bitmap is not 24 bit");
	//		CloseHandle(file);
	//		return 5;
	//	}

	//	m_width = bmpInfo.biWidth;
	//	m_height = bmpInfo.biHeight;
	//	unsigned long sizeImage = bmpHeader.bfSize - bmpHeader.bfOffBits;

	//	unsigned char *buffer = new unsigned char[sizeImage];

	//	if (!ReadFile(file, &buffer, bytesRead, &sizeImage, NULL)) {
	//		delete[] buffer;
	//		CloseHandle(file);
	//		return 6;
	//	}

	//	m_pixels = buffer;

	//	int x = 0;
	//	for (unsigned long i = 0; i < sizeImage; i += 4) {
	//		std::cout << x << ": " << "R: " << (int)m_pixels[i] << " G: " << (int)m_pixels[i + 1] << " B: " << (int)m_pixels[i + 2] << std::endl;
	//		x++;
	//	}

	//	CloseHandle(file);
	//	return 0;
	//}

	int Bitmap::LoadBMP(const std::string &bmpFile) {
		unsigned char *datBuff[2]{ nullptr, nullptr };
		unsigned char *pixels = nullptr;

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
			file.close();
			return 2;
		}

		if (bmpInfo->biBitCount != 24) {
			m_logger.Log(2, __FILE__, __LINE__, "Bitmap is not 24 bit");
			file.close();
			return 3;
		}

		m_width = bmpInfo->biWidth;
		m_height = bmpInfo->biHeight;

		file.seekg(0, file.end);
		std::cout << "length: " << file.tellg() << std::endl;
		file.seekg(0, file.beg);

		unsigned long sizeImage = m_width * m_height * 4;
		pixels = new unsigned char[sizeImage];
		m_data = new unsigned char[sizeImage / 4];
		file.seekg(bmpHeader->bfOffBits);
		file.read((char*)pixels, sizeImage);

		std::cout << bmpHeader->bfOffBits << std::endl;
		int padding = 4 - ((m_width * bmpInfo->biBitCount / 8) % 4);
		unsigned long i = 0;
		unsigned long j = 0;

		/*unsigned char tmpRGB = 0;
		for (unsigned long i = 0; i < sizeImage; i += 4) {
		tmpRGB = m_pixels[i];
		m_pixels[i] = m_pixels[i + 2];
		m_pixels[i + 2] = tmpRGB;
		}*/
		unsigned char tmpRGB = 0;
		for (unsigned long y = 0; y < m_height; y++) {
			for (unsigned long x = 0; x < m_width; x++) {
				tmpRGB = pixels[i];
				pixels[i] = pixels[i + 2];
				pixels[i + 2] = tmpRGB;
				m_data[j] = pixels[i];
				//std::cout << x << ": " << "R: " << (int)pixels[i] << " G: " << (int)pixels[i + 1] << " B: " << (int)pixels[i + 2] << std::endl;
				i += 3;
				j++;
			}
			i += padding;
		}
		//std::cout << "__________________________________" << std::endl;

		//for (unsigned long k = 0; k < m_width * m_height; k++) {
		//	std::cout << (int)m_data[k] << std::endl;
		//}

		//std::cout << "__________________________________" << std::endl;

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

	unsigned char *Bitmap::GetData() {
		return m_data;
	}
}