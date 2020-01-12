#ifndef BLOCK_H_
#define BLOCK_H_
#include <memory>
#include <map>
using namespace std;

class Block
{
private:
    map<int,unique_ptr<int[]>> blocks;
public:
    Block();
    int* getBlock(int i);
};
#endif /* BLOCK_H_ */