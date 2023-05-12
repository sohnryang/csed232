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
	: m_width(width), m_height(height) {
		int buf_size = width * height;
		if (buf_size == 0) {
			m_buff = SharedArray<PixelType>(nullptr);
			return;
		}
		m_buff = SharedArray<PixelType>(new PixelType[buf_size]);
	}
	Image(int width, int height, const PixelType &pixel)
	: Image(width, height) {
		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++)
				m_buff[y * width + x] = pixel;
	}
	Image(const Image<PixelType> &that)
	: Image(that.width(), that.height()) {
		int buf_size = m_width * m_height;
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
	
	// ======= ADD CODE HERE IF NEEDED =========
	int width() const { return m_width; }
	int height() const { return m_height; }

	template<typename NewPixelType, typename ConvFunc>
	Image<NewPixelType> convert(const ConvFunc& func) const {
		Image<NewPixelType> converted(m_width, m_height);
		for (int y = 0; y < m_height; y++)
			for (int x = 0; x < m_width; x++)
				converted[y][x] = func(m_buff[y * m_width + x]);
		return converted;
	}

	struct SliceRange {
		int start, stop, step;
		bool whole;

		SliceRange()
		: start(0), step(1), whole(true) {}
		SliceRange(int start, int stop, int step)
		: start(start), stop(stop), step(step), whole(false) {}
		SliceRange(int start, int stop)
		: SliceRange(start, stop, 1) {}

		int count() const {
			if (whole)
				return -1;
			int count, len;
			if (step > 0)
				len = stop - start;
			else
				len = start - stop;
			if (len <= 0)
				return 0;
			if (step > 0)
				count = len / step + (len % step != 0);
			else
				count = len / -step + (len % -step != 0);
			return count;
		}
	};

	Image<PixelType> slice(const SliceRange &range_x, const SliceRange &range_y) const {
		int x_count, y_count;
		if (range_x.whole)
			x_count = m_width;
		else
			x_count = range_x.count();
		if (range_y.whole)
			y_count = m_height;
		else
			y_count = range_y.count();
		Image<PixelType> sliced(x_count, y_count);
		for (int y = 0; y < y_count; y++)
			for (int x = 0; x < x_count; x++)
				sliced[y][x] = m_buff[(range_y.start + range_y.step * y) * m_width
					+ (range_x.start + range_x.step * x)];
		return sliced;
	}
};

// ======= ADD CODE HERE IF NEEDED =========


// Miscellaneous functions
void convert_pixel_type(const Image<RGB8b>& src, Image<RGBf>& dst);
void convert_pixel_type(const Image<RGBf>& src, Image<RGB8b>& dst);

bool load_bmp(const char* path, Image<RGB8b>& img);
bool save_bmp(const char* path, const Image<RGB8b>& img);

#endif
