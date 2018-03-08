// fbc_cv is free software and uses the same licence as OpenCV
// Email: fengbingchun@163.com

#ifndef FBC_CV_CORE_MAT_HPP_
#define FBC_CV_CORE_MAT_HPP_

/* reference: include/opencv2/core/mat.hpp
	      core/src/alloc.cpp
	      include/opencv2/core/utility.hpp
	      include/opencv2/core/cvstd.hpp
	      include/opencv2/core/mat.inl.hpp
*/

#ifndef __cplusplus
	#error mat.hpp header must be compiled as C++
#endif

#include <typeinfo>
#include <math.h>
#include <algorithm>
#include <stdio.h>
namespace fbc {
#define  FBC_MALLOC_ALIGN    16
#define CHAR_BIT      8         // number of bits in a char
#define SCHAR_MIN   (-128)      // minimum signed char value
#define SCHAR_MAX     127       // maximum signed char value
#define UCHAR_MAX     0xff      // maximum unsigned char value
#define SHRT_MIN    (-32768)        // minimum (signed) short value
#define SHRT_MAX      32767         // maximum (signed) short value
#define USHRT_MAX     0xffff        // maximum unsigned short value
#define INT_MIN     (-2147483647 - 1) // minimum (signed) int value
#define INT_MAX       2147483647    // maximum (signed) int value
#define UINT_MAX      0xffffffff    // maximum unsigned int value
#define LONG_MIN    (-2147483647L - 1) // minimum (signed) long value
#define LONG_MAX      2147483647L   // maximum (signed) long value
#define ULONG_MAX     0xffffffffUL  // maximum unsigned long value
#define LLONG_MAX     9223372036854775807i64       // maximum signed long long int value
#define LLONG_MIN   (-9223372036854775807i64 - 1)  // minimum signed long long int value
#define ULLONG_MAX    0xffffffffffffffffui64       // maximum unsigned long long int value
// Rounds floating-point number to the nearest integer
static inline int fbcRound(double value)
{
    return (int)(value + (value >= 0 ? 0.5 : -0.5));
}

static inline int fbcRound(float value)
{
    return (int)(value + (value >= 0 ? 0.5f : -0.5f));
}
template<typename _Tp> static inline _Tp saturate_cast(unsigned char v)    { return _Tp(v); }
template<typename _Tp> static inline _Tp saturate_cast(signed char v)    { return _Tp(v); }
template<typename _Tp> static inline _Tp saturate_cast(unsigned short v)   { return _Tp(v); }
template<typename _Tp> static inline _Tp saturate_cast(short v)    { return _Tp(v); }
template<typename _Tp> static inline _Tp saturate_cast(unsigned int v) { return _Tp(v); }
template<typename _Tp> static inline _Tp saturate_cast(int v)      { return _Tp(v); }
template<typename _Tp> static inline _Tp saturate_cast(float v)    { return _Tp(v); }
template<typename _Tp> static inline _Tp saturate_cast(double v)   { return _Tp(v); }

template<> inline unsigned char saturate_cast<unsigned char>(signed char v)        { return (unsigned char)std::max((int)v, 0); }
template<> inline unsigned char saturate_cast<unsigned char>(unsigned short v)       { return (unsigned char)std::min((unsigned)v, (unsigned)UCHAR_MAX); }
template<> inline unsigned char saturate_cast<unsigned char>(int v)          { return (unsigned char)((unsigned)v <= UCHAR_MAX ? v : v > 0 ? UCHAR_MAX : 0); }
template<> inline unsigned char saturate_cast<unsigned char>(short v)        { return saturate_cast<unsigned char>((int)v); }
template<> inline unsigned char saturate_cast<unsigned char>(unsigned int v) { return (unsigned char)std::min(v, (unsigned)UCHAR_MAX); }
template<> inline unsigned char saturate_cast<unsigned char>(float v)        { int iv = fbcRound(v); return saturate_cast<unsigned char>(iv); }
template<> inline unsigned char saturate_cast<unsigned char>(double v)       { int iv = fbcRound(v); return saturate_cast<unsigned char>(iv); }

template<> inline signed char saturate_cast<signed char>(unsigned char v)        { return (signed char)std::min((int)v, SCHAR_MAX); }
template<> inline signed char saturate_cast<signed char>(unsigned short v)       { return (signed char)std::min((unsigned)v, (unsigned)SCHAR_MAX); }
template<> inline signed char saturate_cast<signed char>(int v)          { return (signed char)((unsigned)(v-SCHAR_MIN) <= (unsigned)UCHAR_MAX ? v : v > 0 ? SCHAR_MAX : SCHAR_MIN); }
template<> inline signed char saturate_cast<signed char>(short v)        { return saturate_cast<signed char>((int)v); }
template<> inline signed char saturate_cast<signed char>(unsigned v)     { return (signed char)std::min(v, (unsigned)SCHAR_MAX); }
template<> inline signed char saturate_cast<signed char>(float v)        { int iv = fbcRound(v); return saturate_cast<signed char>(iv); }
template<> inline signed char saturate_cast<signed char>(double v)       { int iv = fbcRound(v); return saturate_cast<signed char>(iv); }

template<> inline unsigned short saturate_cast<unsigned short>(signed char v)      { return (unsigned short)std::max((int)v, 0); }
template<> inline unsigned short saturate_cast<unsigned short>(short v)      { return (unsigned short)std::max((int)v, 0); }
template<> inline unsigned short saturate_cast<unsigned short>(int v)        { return (unsigned short)((unsigned)v <= (unsigned)USHRT_MAX ? v : v > 0 ? USHRT_MAX : 0); }
template<> inline unsigned short saturate_cast<unsigned short>(unsigned v)   { return (unsigned short)std::min(v, (unsigned)USHRT_MAX); }
template<> inline unsigned short saturate_cast<unsigned short>(float v)      { int iv = fbcRound(v); return saturate_cast<unsigned short>(iv); }
template<> inline unsigned short saturate_cast<unsigned short>(double v)     { int iv = fbcRound(v); return saturate_cast<unsigned short>(iv); }

template<> inline short saturate_cast<short>(unsigned short v)       { return (short)std::min((int)v, SHRT_MAX); }
template<> inline short saturate_cast<short>(int v)          { return (short)((unsigned)(v - SHRT_MIN) <= (unsigned)USHRT_MAX ? v : v > 0 ? SHRT_MAX : SHRT_MIN); }
template<> inline short saturate_cast<short>(unsigned v)     { return (short)std::min(v, (unsigned)SHRT_MAX); }
template<> inline short saturate_cast<short>(float v)        { int iv = fbcRound(v); return saturate_cast<short>(iv); }
template<> inline short saturate_cast<short>(double v)       { int iv = fbcRound(v); return saturate_cast<short>(iv); }

template<> inline int saturate_cast<int>(float v)            { return fbcRound(v); }
template<> inline int saturate_cast<int>(double v)           { return fbcRound(v); }

template<> inline unsigned saturate_cast<unsigned>(float v)  { return fbcRound(v); }
template<> inline unsigned saturate_cast<unsigned>(double v) { return fbcRound(v); }

// Allocates an aligned memory buffer
//void* fastMalloc(size_t size);
//// Deallocates a memory buffer
//void fastFree(void* ptr);

void* fastMalloc(size_t size)
{
    unsigned char* udata = (unsigned char*)malloc(size + sizeof(void*) + FBC_MALLOC_ALIGN);
    if (!udata) {
        fprintf(stderr, "failed to allocate %lu bytes\n", (unsigned long)size);
        return NULL;
    }
    int n = FBC_MALLOC_ALIGN;
    unsigned char** adata = ( unsigned char** ) ( ( ( size_t ) ((unsigned char**)udata +1) + n - 1)& -n) ;
    //uchar** adata = alignPtr((uchar**)udata + 1, FBC_MALLOC_ALIGN);
    adata[-1] = udata;
    return adata;
}

// Deallocates a memory buffer
void fastFree(void* ptr)
{
    if (ptr) {
        unsigned char* udata = ((unsigned char**)ptr)[-1];
        assert(udata < (unsigned char*)ptr && ((unsigned char*)ptr - udata) <= (int)(sizeof(void*) + FBC_MALLOC_ALIGN));
        free(udata);
    }
}

// The class Mat_ represents an n-dimensional dense numerical single-channel or multi-channel array
template<typename _Tp, int chs> class Mat_ {
public:
	typedef _Tp value_type;

	// constructs 2D matrix of the specified size
    Mat_(int _rows, int _cols);
	// constructor for matrix headers pointing to user-allocated data, no data is copied
    Mat_(int _rows, int _cols, void* _data);
	// copy constructor, NOTE: deep copy
    //Mat_(const Mat_<_Tp, chs>& _m);
	Mat_& operator = (const Mat_& _m);

	// reports whether the matrix is continuous or not
	bool isContinuous() const;

	// return typed pointer to the specified matrix row,i0, A 0-based row index
    const unsigned char* ptr(int i0 = 0) const;
    unsigned char* ptr(int i0 = 0);

	// returns true if Mat_::total() is 0 or if Mat_::data is NULL
	bool empty() const;

	// returns the total number of array elements
	size_t total() const;

	// release memory
	inline void release();
	// destructor - calls release()
    ~Mat_() { release();}

public:
	// the number of rows and columns
	int rows, cols;
	// channel num
	int channels;
	// pointer to the data
    unsigned char* data;
	// bytes per row
	int step; // stride
	// memory allocation flag
	bool allocated;
	// helper fields used in locateROI and adjustROI
    const unsigned char* datastart;
    const unsigned char* dataend;
}; // Mat_

typedef Mat_<unsigned char, 1> Mat1Gray;
typedef Mat_<unsigned char, 3> Mat3BGR;
typedef Mat_<unsigned char, 4> Mat4BGRA;

template<typename _Tp, int chs> inline
void Mat_<_Tp, chs>::release()
{
	if (this->data && this->allocated) {
		fastFree(this->data);
	}

	this->data = NULL;
	this->datastart = NULL;
	this->dataend = NULL;
	this->allocated = false;
	this->rows = this->cols = this->step = this->channels = 0;
}

template<typename _Tp, int chs>
Mat_<_Tp, chs>::Mat_(int _rows, int _cols)
{
    assert(_rows > 0 && _cols > 0 && chs > 0);

    this->rows = _rows;
    this->cols = _cols;
    this->channels = chs;
    this->step = sizeof(_Tp) * _cols * chs;
    this->allocated = true;

    size_t size_ = this->rows * this->step;
    unsigned char* p = (unsigned char*)fastMalloc(size_);
    assert(p != NULL);

    this->data = p;
    this->datastart = this->data;
    this->dataend = this->data + size_;
}


template<typename _Tp, int chs>
Mat_<_Tp, chs>::Mat_(int _rows, int _cols, void* _data)
{
	assert(_rows > 0 && _cols > 0 && chs > 0);

	this->rows = _rows;
	this->cols = _cols;
	this->channels = chs;
	this->step = sizeof(_Tp) * _cols * chs;
	this->allocated = false;
    this->data = (unsigned char*)_data;
	this->datastart = this->data;
	this->dataend = this->data + this->step * this->rows;
}

template<typename _Tp, int chs>
Mat_<_Tp, chs>& Mat_<_Tp, chs>::operator = (const Mat_& _m)
{
    size_t size1 = this->rows * this->step;
    size_t size2 = _m.rows * _m.step;

    this->rows = _m.rows;
    this->cols = _m.cols;
    this->channels = _m.channels;
    this->step = sizeof(_Tp) * this->cols * this->channels;

    if ((size1 == size2) && (this->allocated == true) && (this->data != _m.data)) {
        memcpy(this->data, _m.data, size2);
    } else if (size2 > 0){
        if (this->allocated == true) {
            fastFree(this->data);
        }

        this->allocated = true;
        unsigned char* p = (unsigned char*)fastMalloc(size2);
        assert(p != NULL);
        memcpy(p, _m.data, size2);
        this->data = p;
    } else {
        this->allocated = false;
        this->data = NULL;
    }

    this->datastart = this->data;
    this->dataend = this->data + size2;

    return *this;
}

template<typename _Tp, int chs>
bool Mat_<_Tp, chs>::isContinuous() const
{
    return this->rows == 1 || this->step == this->cols * (this->channels * sizeof(_Tp));
}

template<typename _Tp, int chs>
const unsigned char* Mat_<_Tp, chs>::ptr(int i0) const
{
	assert(i0 < this->rows);

	return this->data + i0 * this->step;
}

template<typename _Tp, int chs>
unsigned char* Mat_<_Tp, chs>::ptr(int i0)
{
	assert(i0 < this->rows);

	return this->data + i0 * this->step;
}


template<typename _Tp, int chs>
size_t Mat_<_Tp, chs>::total() const
{
	return (size_t)rows * cols;
}

template<typename _Tp, int chs>
bool Mat_<_Tp, chs>::empty() const
{
	return total() == 0 || this->data == NULL;
}
} // fbc

#endif // FBC_CV_CORE_MAT_HPP_
