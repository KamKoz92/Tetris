#include "Block.h"
#include <iostream>
using namespace std;

Block::Block()
{
    blocks[0] = unique_ptr<int[]>(new int[16]
    {0, 0, 0, 0, 
    0, 1, 1, 0, 
    0, 1, 1, 0,
    0, 0, 0, 0}); 

    blocks[1] = unique_ptr<int[]>(new int[16]
    {0, 1, 1, 0, 
    0, 1, 0, 0, 
    0, 1, 0, 0,
    0, 0, 0, 0});

    blocks[2] = unique_ptr<int[]>(new int[16]
    {0, 1, 0, 0, 
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0});

    blocks[3] = unique_ptr<int[]>(new int[16]
    {0, 1, 0, 0, 
    0, 1, 1, 0, 
    0, 0, 1, 0,
    0, 0, 0, 0});
}
int* Block::getBlock(int i)
{
    if(i < 4 && i >=0)
    {
        return blocks[i].get();
    }
    else
    {
        cout << "Bad block number" << endl;
        return nullptr;
    }

}