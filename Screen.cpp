#include "Screen.h"
#include "Bmp.h"
#include <iostream>
#include "BitmapFile.h"
#include "BitmapInfo.h"
#include <stdlib.h>
#include <time.h>
#include "Block.h"
#include "Board.h"
using namespace std;

Screen::Screen() : m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), scoreTab(new int[5]), nextBlockTab(new int[32])
{
    imageSet.readBmp();
    scoreTab[0] = 121;
    scoreTab[1] = 421;
    scoreTab[2] = 461;
    scoreTab[3] = 501;
    scoreTab[4] = 541;

    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            nextBlockTab[((x * 4) + y) * 2] = 421 + x * 40;
            nextBlockTab[((x * 4) + y) * 2 + 1] = 281 + y * 40;
        }
    }
    activeBlock.resize(4);
}
Screen::~Screen()
{
    delete[] nextBlockTab;
    delete[] scoreTab;
}
bool Screen::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return false;
    }
    m_window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_window == NULL)
    {
        SDL_Quit;
        return false;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == NULL)
    {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (m_texture == NULL)
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }
    srand(time(NULL));
    setInterface();
    return true;
}
void Screen::close()
{
    delete[] m_buffer1;
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
void Screen::clear()
{
    memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
    update();
}
void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
{
    if (x < 0 || x > SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
    {
        return;
    }
    Uint32 color = 0;
    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xFF;
    m_buffer1[(y * SCREEN_WIDTH) + x] = color;
}
void Screen::update()
{
    SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
}
void Screen::setInterface()
{
    //set black screen
    m_buffer1 = new Uint32[SCREEN_HEIGHT * SCREEN_WIDTH];
    memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

    //borders & split screen
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        setPixel(x, 0, 0xFF, 0xFF, 0xFF);
        setPixel(x, 1, 0xFF, 0xFF, 0xFF);
        setPixel(x, 602, 0xFF, 0xFF, 0xFF);
        setPixel(x, 603, 0xFF, 0xFF, 0xFF);
    }
    for (int y = 2; y < SCREEN_HEIGHT - 2; y++)
    {
        setPixel(0, y, 0xFF, 0xFF, 0xFF);
        setPixel(1, y, 0xFF, 0xFF, 0xFF);
        setPixel(SCREEN_WIDTH - 1, y, 0xFF, 0xFF, 0xFF);
        setPixel(SCREEN_WIDTH - 2, y, 0xFF, 0xFF, 0xFF);

        setPixel(402, y, 0xFF, 0xFF, 0xFF);
        setPixel(403, y, 0xFF, 0xFF, 0xFF);
    }

    // set score & next block tab
    //horizontal lines
    for (int x = 420; x < 582; x++)
    {
        setPixel(x, 81, 0xFF, 0xFF, 0xFF);
        setPixel(x, 122, 0xFF, 0xFF, 0xFF);

        setPixel(x, 241, 0xFF, 0xFF, 0xFF);
        setPixel(x, 402, 0xFF, 0xFF, 0xFF);
    }
    //vertical lines
    for (int y = 82; y < 122; y++)
    {
        setPixel(420, y, 0xFF, 0xFF, 0xFF);
        setPixel(581, y, 0xFF, 0xFF, 0xFF);
    }
    for (int y = 241; y < 401; y++)
    {
        setPixel(420, y, 0xFF, 0xFF, 0xFF);
        setPixel(581, y, 0xFF, 0xFF, 0xFF);
    }
}
void Screen::start()
{
    int tmpRandom = rand() % 5; //rand() % 5;
    random = rand() % 5;        //rand() % 5;
    updateScore();
    currBlockType = tmpRandom;
    updateNextBlockTab(tmpRandom);
    board.newBlock(tmpRandom);
    countDown();
    updateNextBlockTab(random);
    drawElement();
}
void Screen::drawBlock(int x, int y, int j)
{
    for (int bmpY = 0; bmpY < 40; bmpY++)
    {
        for (int bmpX = 0; bmpX < 40; bmpX++)
        {
            if (j == 11) //black space
            {
                setPixel(x + bmpX, y - bmpY, 0, 0, 0);
            }
            else //draw image
            {
                setPixel(x + bmpX, y - bmpY,                                 // rbg -> gbr
                         imageSet.getBmp((((bmpY * 40) + bmpX) * 3) + 2, j), // blue
                         imageSet.getBmp((((bmpY * 40) + bmpX) * 3) + 1, j), // green
                         imageSet.getBmp(((bmpY * 40) + bmpX) * 3, j));      // red
            }
        }
    }
}
void Screen::updateScore()
{
    int divider = 1000;
    int temp = score;
    if (score > 0)
    {
        for (int i = 1; i < 5; i++)
        {
            drawBlock(scoreTab[i], scoreTab[0], temp / divider);
            temp = temp % divider;
            divider /= 10;
        }
    }
    else
    {
        for (int i = 1; i < 5; i++)
        {
            drawBlock(scoreTab[i], scoreTab[0], 0);
        }
    }
}
void Screen::updateNextBlockTab(int random)
{
    int *rBlock{nullptr};
    switch (random)
    {
    case 0:
        rBlock = blockSet.getBlock(0);
        break;
    case 1:
        rBlock = blockSet.getBlock(1);
        break;
    case 2:
        rBlock = blockSet.getBlock(2);
        break;
    case 3:
        rBlock = blockSet.getBlock(3);
        break;
    case 4:
        rBlock = blockSet.getBlock(4);
        break;
    default:
        cout << "Wrong block set type" << endl;
        break;
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (rBlock[(i * 4) + j] == 1)
            {
                drawBlock(nextBlockTab[((i * 4) + j) * 2], nextBlockTab[((i * 4) + j) * 2 + 1], 10);
            }
            else
            {
                drawBlock(nextBlockTab[((i * 4) + j) * 2], nextBlockTab[((i * 4) + j) * 2 + 1], 11);
            }
        }
    }
}

void Screen::drawElement()
{
    for (int i = 0; i < 4; i++)
    {
        int x, y;
        tie(x, y) = board.getElement(i);
        drawBlock(x, y, 10);
    }
    update();
}
void Screen::countDown()
{
    int i = 2;
    int time = SDL_GetTicks();
    int elapsed = 0;
    drawBlock(177, 277, i + 1);
    update();
    while (i > -1)
    {
        elapsed = SDL_GetTicks();
        if ((elapsed - time) > 199)
        {
            time = elapsed;
            if (i > 0)
            {
                drawBlock(177, 277, i);
            }
            else
            {
                drawBlock(177, 277, 11);
            }
            update();
            i--;
        }
    }
}
bool Screen::moveElement(int dir)
{
    if (dir < 4)
    {
        if (dir == 2)
        {
            if (board.checkIfMoveable(dir))
            {
                hideOldElement();
                board.moveBlocks(dir);
                drawElement();
            }
            else
            {
                int row, length;
                tie(row, length) = board.activeToPassive();
                if (row != 0 && length != 0)
                {
                    redrawBoard(row, length);
                }
                score++;
                updateScore();
                if (board.newBlock(random))
                {
                    currBlockType = random;
                    random = rand() % 5; //rand() % 5;
                    updateNextBlockTab(random);
                    drawElement();
                }
                else
                {
                    return 0;
                }
            }
        }
        else
        {
            if (board.checkIfMoveable(dir))
            {
                hideOldElement();
                board.moveBlocks(dir);
                drawElement();
            }
        }
    }
    else
    {
        //possible improvmnt of not drawing again if noPossibleRotation
        if(currBlockType != 0)
        {
            hideOldElement();
            board.rotateElement(dir-4);
            drawElement(); 
        }     
    }
    return 1;
}
void Screen::hideOldElement()
{
    for (int i = 0; i < 4; i++)
    {
        int x, y;
        tie(x, y) = board.getElement(i);
        drawBlock(x, y, 11);
    }
}

void Screen::redrawBoard(int row, int length)
{
    int tempx{0}, tempy{0};
    for (int y = row; y > row - length; y--)
    {
        for (int x = 0; x < 10; x++)
        {
            board.freeSquare(x, y);
            tie(tempx, tempy) = board.getBoardCords(x, y);
            drawBlock(tempx, tempy, 11);
        }
    }
    for (int y = row - length; y > 0; y--)
    {
        for (int x = 0; x < 10; x++)
        {
            if (!board.ifSquareFree(x, y))
            {
                board.freeSquare(x, y);
                tie(tempx, tempy) = board.getBoardCords(x, y);
                drawBlock(tempx, tempy, 11);

                board.occupySquare(x, y + length);
                tie(tempx, tempy) = board.getBoardCords(x, y + length);
                drawBlock(tempx, tempy, 10);
            }
        }
    }
    update();
    score += 100 * length;
}
