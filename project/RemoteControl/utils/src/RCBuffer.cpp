
#include "RCBuffer.h"
#include <assert.h>

using namespace std;

RCBuffer::RCBuffer(char* b, int nn)
{
    p = bytes = b;
    nb_bytes = nn;
}

RCBuffer::~RCBuffer()
{
}

RCBuffer* RCBuffer::copy()
{
    RCBuffer* cp = new RCBuffer(bytes, nb_bytes);
    cp->p = p;
    return cp;
}

char* RCBuffer::data()
{
    return bytes;
}

char* RCBuffer::head()
{
    return p;
}

int RCBuffer::size()
{
    return nb_bytes;
}

void RCBuffer::set_size(int v)
{
    nb_bytes = v;
}

int RCBuffer::pos()
{
    return (int)(p - bytes);
}

int RCBuffer::left()
{
    return nb_bytes - (int)(p - bytes);
}

bool RCBuffer::empty()
{
    return !bytes || (p >= bytes + nb_bytes);
}

bool RCBuffer::require(int required_size)
{
    if (required_size < 0) {
        return false;
    }
    
    return required_size <= nb_bytes - (p - bytes);
}

void RCBuffer::skip(int size)
{
    assert(p);
    assert(p + size >= bytes);
    assert(p + size <= bytes + nb_bytes);
    
    p += size;
}

int8_t RCBuffer::read_1bytes()
{
    assert(require(1));
    
    return (int8_t)*p++;
}

int16_t RCBuffer::read_2bytes()
{
    assert(require(2));
    
    int16_t value;
    char* pp = (char*)&value;
    pp[1] = *p++;
    pp[0] = *p++;
    
    return value;
}

int16_t RCBuffer::read_le2bytes()
{
    assert(require(2));

    int16_t value;
    char* pp = (char*)&value;
    pp[0] = *p++;
    pp[1] = *p++;

    return value;
}

int32_t RCBuffer::read_3bytes()
{
    assert(require(3));
    
    int32_t value = 0x00;
    char* pp = (char*)&value;
    pp[2] = *p++;
    pp[1] = *p++;
    pp[0] = *p++;
    
    return value;
}

int32_t RCBuffer::read_le3bytes()
{
    assert(require(3));

    int32_t value = 0x00;
    char* pp = (char*)&value;
    pp[0] = *p++;
    pp[1] = *p++;
    pp[2] = *p++;

    return value;
}

int32_t RCBuffer::read_4bytes()
{
    assert(require(4));
    
    int32_t value;
    char* pp = (char*)&value;
    pp[3] = *p++;
    pp[2] = *p++;
    pp[1] = *p++;
    pp[0] = *p++;
    
    return value;
}

int32_t RCBuffer::read_le4bytes()
{
    assert(require(4));

    int32_t value;
    char* pp = (char*)&value;
    pp[0] = *p++;
    pp[1] = *p++;
    pp[2] = *p++;
    pp[3] = *p++;

    return value;
}

int64_t RCBuffer::read_8bytes()
{
    assert(require(8));
    
    int64_t value;
    char* pp = (char*)&value;
    pp[7] = *p++;
    pp[6] = *p++;
    pp[5] = *p++;
    pp[4] = *p++;
    pp[3] = *p++;
    pp[2] = *p++;
    pp[1] = *p++;
    pp[0] = *p++;
    
    return value;
}

int64_t RCBuffer::read_le8bytes()
{
    assert(require(8));

    int64_t value;
    char* pp = (char*)&value;
    pp[0] = *p++;
    pp[1] = *p++;
    pp[2] = *p++;
    pp[3] = *p++;
    pp[4] = *p++;
    pp[5] = *p++;
    pp[6] = *p++;
    pp[7] = *p++;

    return value;
}

string RCBuffer::read_string(int len)
{
    assert(require(len));
    
    std::string value;
    value.append(p, len);
    
    p += len;
    
    return value;
}

void RCBuffer::read_bytes(char* data, int size)
{
    assert(require(size));
    
    memcpy(data, p, size);
    
    p += size;
}

void RCBuffer::write_1bytes(int8_t value)
{
    assert(require(1));
    
    *p++ = value;
}

void RCBuffer::write_2bytes(int16_t value)
{
    assert(require(2));
    
    char* pp = (char*)&value;
    *p++ = pp[1];
    *p++ = pp[0];
}

void RCBuffer::write_le2bytes(int16_t value)
{
    assert(require(2));

    char* pp = (char*)&value;
    *p++ = pp[0];
    *p++ = pp[1];
}

void RCBuffer::write_4bytes(int32_t value)
{
    assert(require(4));
    
    char* pp = (char*)&value;
    *p++ = pp[3];
    *p++ = pp[2];
    *p++ = pp[1];
    *p++ = pp[0];
}

void RCBuffer::write_le4bytes(int32_t value)
{
    assert(require(4));

    char* pp = (char*)&value;
    *p++ = pp[0];
    *p++ = pp[1];
    *p++ = pp[2];
    *p++ = pp[3];
}

void RCBuffer::write_3bytes(int32_t value)
{
    assert(require(3));
    
    char* pp = (char*)&value;
    *p++ = pp[2];
    *p++ = pp[1];
    *p++ = pp[0];
}

void RCBuffer::write_le3bytes(int32_t value)
{
    assert(require(3));

    char* pp = (char*)&value;
    *p++ = pp[0];
    *p++ = pp[1];
    *p++ = pp[2];
}

void RCBuffer::write_8bytes(int64_t value)
{
    assert(require(8));
    
    char* pp = (char*)&value;
    *p++ = pp[7];
    *p++ = pp[6];
    *p++ = pp[5];
    *p++ = pp[4];
    *p++ = pp[3];
    *p++ = pp[2];
    *p++ = pp[1];
    *p++ = pp[0];
}

void RCBuffer::write_le8bytes(int64_t value)
{
    assert(require(8));

    char* pp = (char*)&value;
    *p++ = pp[0];
    *p++ = pp[1];
    *p++ = pp[2];
    *p++ = pp[3];
    *p++ = pp[4];
    *p++ = pp[5];
    *p++ = pp[6];
    *p++ = pp[7];
}

void RCBuffer::write_string(string value)
{
    assert(require((int)value.length()));
    
    memcpy(p, value.data(), value.length());
    p += value.length();
}

void RCBuffer::write_bytes(char* data, int size)
{
    assert(require(size));
    
    memcpy(p, data, size);
    p += size;
}

RCBitBuffer::RCBitBuffer(RCBuffer* b)
{
    cb = 0;
    cb_left = 0;
    stream = b;
}

RCBitBuffer::~RCBitBuffer()
{
}

bool RCBitBuffer::empty() {
    if (cb_left) {
        return false;
    }
    return stream->empty();
}

int8_t RCBitBuffer::read_bit() {
    if (!cb_left) {
        assert(!stream->empty());
        cb = stream->read_1bytes();
        cb_left = 8;
    }
    
    int8_t v = (cb >> (cb_left - 1)) & 0x01;
    cb_left--;
    return v;
}

