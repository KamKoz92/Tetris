#ifndef BITMAPFILE_H_
#define BITMAPFILE_H_

#include <cstdint>

#pragma pack(push, 1)
struct BitmapFile
{
    uint16_t file_type{0x4D42}; // File type always BM which is 0x4D42
    uint32_t file_size{0};      // Size of the file (in bytes)
    uint16_t reserved1{0};      // Reserved, always 0
    uint16_t reserved2{0};      // Reserved, always 0
    uint32_t offset_data{0};
};
#pragma pack(pop)
#endif /* BITMAPFILE_H_ */