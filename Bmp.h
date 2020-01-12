#ifndef BMP_H_
#define BMP_H_
#include <memory>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;
class Bmp
{
private:
    unique_ptr<uint8_t[]> zero{nullptr};
    unique_ptr<uint8_t[]> one{nullptr};
    unique_ptr<uint8_t[]> two{nullptr};
    unique_ptr<uint8_t[]> three{nullptr};
    unique_ptr<uint8_t[]> four{nullptr};
    unique_ptr<uint8_t[]> five{nullptr};
    unique_ptr<uint8_t[]> six{nullptr};
    unique_ptr<uint8_t[]> seven{nullptr};
    unique_ptr<uint8_t[]> eight{nullptr};
    unique_ptr<uint8_t[]> nine{nullptr};
    unique_ptr<uint8_t[]> block{nullptr}; 
public:
    Bmp();
    ~Bmp();
    void readBmp();
    uint8_t getBmp(int xy, int i);
};
#endif /* BMP_H_ */