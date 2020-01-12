#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
using namespace std;

class Board{
private:
    vector< vector<int> > board;
    vector< vector<int> > leftInverse;
    vector< vector<int> > rightInverse;
    vector< pair<int,int> > activeBlock;
    int pivotBlock;

public:
    Board();
    ~Board();
    pair<int,int> getBoardCords(int x, int y);
    bool newBlock(int radnom);
    void updateBlock();
    pair<int,int> getElement(int i);
    void moveBlocks(int i);
    bool checkIfMoveable(int dir);
    bool ifSquareFree(int x, int y);
    pair<int,int> activeToPassive();
    void freeSquare(int x, int y);
    void occupySquare(int x, int y);
    void rotateElement(int side);
    };
#endif /* BOARD_H_ */