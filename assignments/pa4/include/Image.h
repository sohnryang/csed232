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

	// Shared array for pixel data.
	SharedArray<PixelType> m_buff;

	// Image width and height.
	size_t m_width, m_height;
	
public:
	////////////////////////////////////////////
	// constructors & destructor
	////////////////////////////////////////////
	
	// ======= ADD CODE HERE IF NEEDED =========
	// Default constructor.
	Image() : m_width(0), m_height(0), m_buff(nullptr) {}

	// Constructor with image size.
	Image(size_t _width, size_t _height)
	: m_width(_width), m_height(_height) {
		int buf_size = _width * _height;
		if (buf_size == 0) { // check if size is zero
			m_buff = SharedArray<PixelType>(nullptr);
			return;
		}
		// Allocate array
		m_buff = SharedArray<PixelType>(new PixelType[buf_size]);
	}

	// Constructor with image size and single pixel.
	Image(size_t _width, size_t _height, const PixelType &val)
	: Image(_width, _height) {
		for (int y = 0; y < _height; y++)
			for (int x = 0; x < _width; x++)
				m_buff[y * _width + x] = val;
	}

	// Copy constructor.
	Image(const Image<PixelType> &img)
	: Image(img.width(), img.height()) {
		int buf_size = m_width * m_height;
		for (int i = 0; i < buf_size; i++)
			m_buff[i] = img.m_buff[i];
	}

	////////////////////////////////////////////
	// assignment operator
	////////////////////////////////////////////
	
	// ======= ADD CODE HERE IF NEEDED =========
	// Assignment operator overload
	Image &operator=(const Image &that) {
		if (this == &that) // check self-assignment
			return *this;

		// Copy width and height.
		m_width = that.m_width;
		m_height = that.m_height;

		int buf_size = m_width * m_height;
		if (buf_size == 0) // check if size is zero
			return *this;

		// Allocate array.
		m_buff = SharedArray<PixelType>(new PixelType[buf_size]);
		for (int i = 0; i < buf_size; i++)
			m_buff[i] = that.m_buff[i]; // copy array
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

	// Getter for width
	size_t width() const { return m_width; }

	// Getter for height
	size_t height() const { return m_height; }

	// Convert pixel type.
	template<typename NewPixelType, typename ConvFunc>
	Image<NewPixelType> convert(const ConvFunc& func) const {
		Image<NewPixelType> converted(m_width, m_height);
		// Iterate over all pixels.
		for (int y = 0; y < m_height; y++)
			for (int x = 0; x < m_width; x++)
				converted[y][x] = func(m_buff[y * m_width + x]); // apply func
		return converted;
	}

	// Inner class for slice range.
	struct SliceRange {
		// Range indicies, analogue to python A[start:stop:step] syntax.
		int start, stop, step;

		// Flag indicating whether the range spans the whole array, analogue to A[:] in python.
		bool whole;

		// Default constructor.
		SliceRange()
		: start(0), step(1), whole(true) {}

		// Constructor with start, stop and step.
		SliceRange(int start, int stop, int step)
		: start(start), stop(stop), step(step), whole(false) {}

		// Constructor with start and stop.
		SliceRange(int start, int stop)
		: SliceRange(start, stop, 1) {}

		// Count indicies spanned by range.
		int count() const {
			if (whole) // if range spans the whole array
				return -1;
			int count, len;
			if (step > 0) // if counting in natural order
				len = stop - start;
			else // if counting in backwards
				len = start - stop;
			if (len <= 0) // check if range spans nothing
				return 0;
			if (step > 0)
				count = len / step + (len % step != 0); // ceil operation
			else
				count = len / -step + (len % -step != 0); // ceil operation
			return count;
		}
	};

	Image<PixelType> slice(const SliceRange &range_x, const SliceRange &range_y) const {
		int x_count, y_count;
		if (range_x.whole)
			x_count = m_width; // the range is whole array, so width is the same as original
		else
			x_count = range_x.count();
		if (range_y.whole)
			y_count = m_height; // the range is whole array, so height is the same as original
		else
			y_count = range_y.count();
		Image<PixelType> sliced(x_count, y_count);
		for (int y = 0; y < y_count; y++)
			for (int x = 0; x < x_count; x++)
				sliced[y][x] = m_buff[(range_y.start + range_y.step * y) * m_width
					+ (range_x.start + range_x.step * x)]; // copy pixel
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
