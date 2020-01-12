#include "Bmp.h"
#include <memory>
#include <fstream>
#include <iostream>
#include "BitmapFile.h"
#include "BitmapInfo.h"

using namespace std;

Bmp::Bmp() : zero(new uint8_t[4800]), one(new uint8_t[4800]), two(new uint8_t[4800]),
             three(new uint8_t[4800]), four(new uint8_t[4800]), five(new uint8_t[4800]), six(new uint8_t[4800]),
             seven(new uint8_t[4800]), eight(new uint8_t[4800]), nine(new uint8_t[4800]), block(new uint8_t[4800])
{
}
Bmp::~Bmp()
{

}
void Bmp::readBmp()
{
    ifstream file;

    // one 
    file.open("Bmps/one.bmp", ios_base::binary);
    if(!file)
    {
        cout << "Cannot open first bmp" << endl;
    }
    else
    {
        file.seekg(sizeof(BitmapFile) + sizeof(BitmapInfo), file.beg);
        file.read((char*)one.get(),4800);
        file.close();
    }
    
    // two
    file.open("Bmps/two.bmp", ios_base::binary);
    if(!file)
    {
        cout << "Cannot open second bmp" << endl;
    }
    else
    {
        file.seekg(sizeof(BitmapFile) + sizeof(BitmapInfo), file.beg);
        file.read((char*)two.get(),4800);
        file.close();
    }

    // three 
    file.open("Bmps/three.bmp", ios_base::binary);
    if(!file)
    {
        cout << "Cannot open third bmp" << endl;
    }
    else
    {
        file.seekg(sizeof(BitmapFile) + sizeof(BitmapInfo), file.beg);
        file.read((char*)three.get(),4800);
        file.close();
    }

    // four
    file.open("Bmps/four.bmp", ios_base::binary);
    if(!file)
    {
        cout << "Cannot open fourth bmp" << endl;
    }
    else
    {
        file.seekg(sizeof(BitmapFile) + sizeof(BitmapInfo), file.beg);
        file.read((char*)four.get(),4800);
        file.close();
    }

    // five
    file.open("Bmps/five.bmp", ios_base::binary);
    if(!file)
    {
        cout << "Cannot open fifth bmp" << endl;
    }
    else
    {
        file.seekg(sizeof(BitmapFile) + sizeof(BitmapInfo), file.beg);
        file.read((char*)five.get(),4800);
        file.close();
    }

    // six
    file.open("Bmps/six.bmp", ios_base::binary);
    if(!file)
    {
        cout << "Cannot open sixth bmp" << endl;
    }
    else
    {
        file.seekg(sizeof(BitmapFile) + sizeof(BitmapInfo), file.beg);
        file.read((char*)six.get(),4800);
        file.close();
    }

    // seven
    file.open("Bmps/seven.bmp", ios_base::binary);
    if(!file)
    {
        cout << "Cannot open seventh bmp" << endl;
    }
    else
    {
        file.seekg(sizeof(BitmapFile) + sizeof(BitmapInfo), file.beg);
        file.read((char*)seven.get(),4800);
        file.close();
    }

    // eight
    file.open("Bmps/eight.bmp", ios_base::binary);
    if(!file)
    {
        cout << "Cannot open eighth bmp" << endl;
    }
    else
    {
        file.seekg(sizeof(BitmapFile) + sizeof(BitmapInfo), file.beg);
        file.read((char*)eight.get(),4800);
        file.close();
    }

    //nine
    file.open("Bmps/nine.bmp", ios_base::binary);
    if(!file)
    {
        cout << "Cannot open ninth bmp" << endl;
    }
    else
    {
        file.seekg(sizeof(BitmapFile) + sizeof(BitmapInfo), file.beg);
        file.read((char*)nine.get(),4800);
        file.close();
    }

    // zero
    file.open("Bmps/zero.bmp", ios_base::binary);
    if(!file)
    {
        cout << "Cannot open zero bmp" << endl;
    }
    else
    {
        file.seekg(sizeof(BitmapFile) + sizeof(BitmapInfo), file.beg);
        file.read((char*)zero.get(),4800);
        file.close();
    }

    //block 
    file.open("Bmps/block.bmp", ios_base::binary);
    if(!file)
    {
        cout << "Cannot open block bmp" << endl;
    }
    else
    {
        file.seekg(sizeof(BitmapFile) + sizeof(BitmapInfo), file.beg);
        file.read((char*)block.get(),4800);
        file.close();
    }
}
uint8_t Bmp::getBmp(int xy, int i)
{
    switch (i)
    {
    case 1:
        return one[xy];
        break;
    case 2:
        return two[xy];
        break;
    case 3:
        return three[xy];
        break;
    case 4:
        return four[xy];
        break;
    case 5:
        return five[xy];
        break;
    case 6:
        return six[xy];
        break;
    case 7:
        return seven[xy];
        break;
    case 8:
        return eight[xy];
        break;
    case 9:
        return nine[xy];
        break;
    case 0:
        return zero[xy];
        break;
    case 10:
        return block[xy];
        break;
    default:
        cout << "wrong block number " << i << endl; // debug purpose
        break;
    }
    return -1;
}