#ifndef BITMAPINFO_H_
#define BITMAPINFO_H_

#include <cstdint>

using namespace std;

#pragma pack(2)

struct BitmapInfo
{
    uint32_t size{0};    
    int32_t width{0};       
    int32_t height{0};               
    uint16_t planes{1};      
    uint16_t bit_count{0};  
    uint32_t compression{0}; 
    uint32_t size_image{0};  
    int32_t x_pixels_per_meter{0};
    int32_t y_pixels_per_meter{0};
    uint32_t colors_used{0};      
    uint32_t colors_important{0}; 
};

#endif /* BITMAPINFO_H_ */