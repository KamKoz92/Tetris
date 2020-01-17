#include "Board.h"
#include <iostream>
#include <tuple>
using namespace std;
Board::Board() : pivotBlock(1)
{
    activeBlock.resize(4);
    vector<int> temp(15, 0);
    for (int i = 0; i < 10; i++)
    {
        board.push_back(temp);
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            board[i][j] = ((i * 40 + 2) * 1000) + (j * 40 + 41);
        }
    }
    temp.resize(2);
    for (int i = 0; i < 2; i++)
    {
        leftInverse.push_back(temp);
        rightInverse.push_back(temp);
    }

    leftInverse[0][0] = 0;
    leftInverse[0][1] = -1;
    leftInverse[1][0] = 1;
    leftInverse[1][1] = 0;

    rightInverse[0][0] = 0;
    rightInverse[0][1] = 1;
    rightInverse[1][0] = -1;
    rightInverse[1][1] = 0;
}
Board::~Board()
{
}

pair<int, int> Board::getBoardCords(int x, int y)
{
    if (x > 9 || x < 0 || y > 14 || y < 0)
    {
        cout << "Out of bounds" << endl;
        return pair<int, int>(0, 0);
    }
    else
    {
        if (ifSquareFree(x, y))
        {
            return pair<int, int>(board[x][y] / 1000, board[x][y] % 1000);
        }
        else
        {
            return pair<int, int>((board[x][y] / 1000) - 1000, board[x][y] % 1000);
        }
    }
}

pair<int, int> Board::getElement(int i)
{
    if (i < 4)
    {
        return getBoardCords(activeBlock[i].first, activeBlock[i].second);
    }
    else
    {
        cout << " bad element" << endl;
        return pair<int, int>(0, 0);
    }
}

bool Board::newBlock(int random)
{
    switch (random)
    {
    case 0:
        //     00
        //     00
        activeBlock[0].first = 4;
        activeBlock[0].second = 0;
        activeBlock[1].first = 5;
        activeBlock[1].second = 0;
        activeBlock[2].first = 4;
        activeBlock[2].second = 1;
        activeBlock[3].first = 5;
        activeBlock[3].second = 1;
        break;
    case 1:
        //  000
        //  0
        activeBlock[0].first = 4;
        activeBlock[0].second = 0;
        activeBlock[1].first = 5;
        activeBlock[1].second = 0;
        activeBlock[2].first = 6;
        activeBlock[2].second = 0;
        activeBlock[3].first = 4;
        activeBlock[3].second = 1;
        break;
    case 2:
        // 0000
        activeBlock[0].first = 3;
        activeBlock[0].second = 0;
        activeBlock[1].first = 4;
        activeBlock[1].second = 0;
        activeBlock[2].first = 5;
        activeBlock[2].second = 0;
        activeBlock[3].first = 6;
        activeBlock[3].second = 0;
        break;
    case 3:
        // 00
        //  00
        activeBlock[0].first = 3;
        activeBlock[0].second = 0;
        activeBlock[1].first = 4;
        activeBlock[1].second = 0;
        activeBlock[2].first = 4;
        activeBlock[2].second = 1;
        activeBlock[3].first = 5;
        activeBlock[3].second = 1;
        break;
    case 4:
        // 000
        //  0
        activeBlock[0].first = 3;
        activeBlock[0].second = 0;
        activeBlock[1].first = 4;
        activeBlock[1].second = 0;
        activeBlock[2].first = 5;
        activeBlock[2].second = 0;
        activeBlock[3].first = 4;
        activeBlock[3].second = 1;
        break;
    default:
        cout << "Wrong block set type" << endl;
        break;
    }
    for (int i = 0; i < 4; i++)
    {
        if (!ifSquareFree(activeBlock[i].first, activeBlock[i].second))
        {
            return 0;
        }
    }
    return 1;
}
void Board::moveBlocks(int i)
{
    switch (i)
    {
    case 2:
        for (int i = 0; i < 4; i++)
        {
            activeBlock[i].second++;
        }
        break;
    case 3:
        for (int i = 0; i < 4; i++)
        {
            activeBlock[i].first++;
        }
        break;
    case 1:
        for (int i = 0; i < 4; i++)
        {
            activeBlock[i].first--;
        }
        break;
    default:
        cout << "Bad element move input" << endl;
        break;
    }
}

// return 1 if is free
bool Board::ifSquareFree(int x, int y)
{
    if (x >= 0 && x < 10 && y >= 0 && y < 15)
    {
        if (board[x][y] > 1000000)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
}
bool Board::checkIfMoveable(int dir)
{
    for (int i = 0; i < 4; i++)
    {
        if (dir == 1 && !(ifSquareFree(activeBlock[i].first - 1, activeBlock[i].second)))
        {
            return 0;
        }
        else if (dir == 2 && (!(ifSquareFree(activeBlock[i].first, activeBlock[i].second + 1)) || activeBlock[i].second + 1 > 14))
        {
            return 0;
        }
        else if (dir == 3 && !(ifSquareFree(activeBlock[i].first + 1, activeBlock[i].second)))
        {
            return 0;
        }
    }
    return 1;
}
pair<int, int> Board::activeToPassive()
{
    int row = 0;
    int length = 0;
    int temp = 0;

    for (int i = 0; i < 4; i++)
    {
        board[activeBlock[i].first][activeBlock[i].second] += 1000000;
        for (int j = 0; j < 10; j++)
        {
            if (board[j][activeBlock[i].second] < 1000000)
            {
                break;
            }
            else
            {
                temp++;
            }
        }
        if (temp == 10)
        {
            if (row < activeBlock[i].second)
            {
                row = activeBlock[i].second;
            }
            length++;
        }
        temp = 0;
    }

    return pair<int, int>(row, length);
}
void Board::freeSquare(int x, int y)
{
    if (board[x][y] > 1000000)
    {
        board[x][y] -= 1000000;
    }
    else
    {
        cout << "Square (" << x << ", " << y << ") aready free!" << endl;
    }
}
void Board::occupySquare(int x, int y)
{
    if (board[x][y] < 1000000)
    {
        board[x][y] += 1000000;
    }
    else
    {
        cout << "Square (" << x << ", " << y << ") aready claimed!" << endl;
    }
}
void Board::rotateElement(int side)
{
    pair<int,int> newBlock[4];
    int Vr[2];
    int Vt[2];

    for (int i = 0; i < 4; i++)
    {
        if (i != pivotBlock)
        {
            Vr[0] = activeBlock[i].first - activeBlock[pivotBlock].first; //-1
            Vr[1] = activeBlock[i].second - activeBlock[pivotBlock].second; //0

            if(side == 0) // possible error with left and right inverse tables // sise is always 1 atm;
            {
                Vt[0] = leftInverse[0][0] * Vr[0] + leftInverse[0][1] * Vr[0];
                Vt[1] = leftInverse[1][0] * Vr[1] + leftInverse[1][1] * Vr[1];
            }
            else
            {
                Vt[0] = rightInverse[0][0] * Vr[0] + rightInverse[0][1] * Vr[0];
                Vt[1] = rightInverse[1][0] * Vr[1] + rightInverse[1][1] * Vr[1];
            }  

            newBlock[i].first = activeBlock[pivotBlock].first + Vt[1];
            newBlock[i].second = activeBlock[pivotBlock].second + Vt[0]; 
        }
        else
        {
            newBlock[i].first = activeBlock[pivotBlock].first;
            newBlock[i].second = activeBlock[pivotBlock].second;
        }
    }

    int noPossibleRotation = 0;
    // int rotationOffset = 0;
    // for(int i = 0; i < 4; i++)
    // {
    //     if(!ifSquareFree(newBlock[i].first, newBlock[i].second))
    //     {
    //         rotationOffset = -1;
    //         for(int k = 0; k < 4; k++)
    //         {
    //             if(!ifSquareFree(newBlock[i].first-1, newBlock[i].second))
    //             {   
    //                 rotationOffset = 1;
    //                 for(int l = 0; l < 4; l++)
    //                 {
    //                     if(!ifSquareFree(newBlock[i].first+1, newBlock[i].second))
    //                     {
    //                         rotationOffset = 0;
    //                         noPossibleRotation = 1;
    //                         break;   
    //                     }
    //                 }
    //                 break;
    //             }
    //         }
    //         break;
    //     }
    // }
    for (int i = 0; i < 4; i++)
    {
        if (!ifSquareFree(newBlock[i].first, newBlock[i].second))
        {
            noPossibleRotation = 1;
            break;
        }
    }

    if(!noPossibleRotation)
    {
        for(int i = 0; i < 4; i++)
        {
            // activeBlock[i].first += rotationOffset;
            // activeBlock[i].second += rotationOffset;
            activeBlock[i] = newBlock[i];
        }
    } 
    //return !noPossibleRotation; possible improvment
}