#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <cstdint>
#include <cassert>
#include "SharedPtr.h"

///////////////////////////////////////////////////////////////////////////
// RGB pixel type
//    Usage:
//      - RGB<float> rgb(0.5f, 0.1f, 0.3f);
//        rgb[0] = 0.2f; // or equivalently, rgb.r = 0.2f;
template<typename ValType>
struct RGB
{
	union {
		ValType data[3];
		struct {
			ValType r, g, b;
		};
	};

	RGB() {}
	RGB(ValType r_, ValType g_, ValType b_) : r(r_), g(g_), b(b_) {}

	ValType operator[](int idx) const { return data[idx]; }
	ValType& operator[](int idx) { return data[idx]; }
};

typedef RGB<uint8_t>	RGB8b;
typedef RGB<float>		RGBf;


///////////////////////////////////////////////////////////////////////////
// Image class template
//
template<typename PixelType>
class Image
{
private:
	// ======= ADD CODE HERE IF NEEDED =========
	SharedArray<PixelType> m_buff;
	int m_width, m_height;
	
public:
	////////////////////////////////////////////
	// constructors & destructor
	////////////////////////////////////////////
	
	// ======= ADD CODE HERE IF NEEDED =========
	Image() : m_width(0), m_height(0), m_buff(nullptr) {}
	Image(int width, int height)
	: m_width(width), m_height(height),
		m_buff(new PixelType[width * height]) {}
	Image(int width, int height, const PixelType &pixel)
	: m_width(width), m_height(height),
		m_buff(new PixelType[width * height]) {
		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++)
				m_buff[y * width + x] = pixel;
	}
	Image(const Image<PixelType> &that)
	: m_width(that.m_width), m_height(that.m_height) {
		int buf_size = m_width * m_height;
		if (buf_size == 0)
			return;
		m_buff = SharedArray<PixelType>(new PixelType[buf_size]);
		for (int i = 0; i < buf_size; i++)
			m_buff[i] = that.m_buff[i];
	}

	////////////////////////////////////////////
	// assignment operator
	////////////////////////////////////////////
	
	// ======= ADD CODE HERE IF NEEDED =========
	Image &operator=(const Image &that) {
		if (this == &that)
			return *this;
		m_width = that.m_width;
		m_height = that.m_height;
		int buf_size = m_width * m_height;
		if (buf_size == 0)
			return *this;
		m_buff = SharedArray<PixelType>(new PixelType[buf_size]);
		for (int i = 0; i < buf_size; i++)
			m_buff[i] = that.m_buff[i];
		return *this;
	}

	////////////////////////////////////////////
	// element access operators
	////////////////////////////////////////////
	PixelType* operator[](int y) { return &m_buff[y * m_width]; }
	const PixelType* operator[](int y) const { return &m_buff[y * m_width]; }

	////////////////////////////////////////////
	// other methods
	////////////////////////////////////////////
	//   - width(), height()
	int width() const { return m_width; }
	int height() const { return m_height; }
	
	// ======= ADD CODE HERE IF NEEDED =========
};

// ======= ADD CODE HERE IF NEEDED =========


// Miscellaneous functions
void convert_pixel_type(const Image<RGB8b>& src, Image<RGBf>& dst);
void convert_pixel_type(const Image<RGBf>& src, Image<RGB8b>& dst);

bool load_bmp(const char* path, Image<RGB8b>& img);
bool save_bmp(const char* path, const Image<RGB8b>& img);

#endif
