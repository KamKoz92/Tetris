#ifndef SCREEN_H_
#define SCREEN_H_
#include <SDL2/SDL.h>
#include "Bmp.h"
#include <memory>
#include "Block.h"
#include "Board.h"

class Screen
{
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;
    Uint32 *m_buffer1;
    Uint32 *m_buffer2;
    Bmp imageSet;
    int score{0000};
    int *scoreTab{nullptr};
    int *nextBlockTab{nullptr};
    Block blockSet;
    Board board;
    vector< pair<int,int> > activeBlock;
    int random{0};


public:
    const static int SCREEN_HEIGHT = 604;
    const static int SCREEN_WIDTH = 600;
    Screen();
    ~Screen();
    bool init();
    void close();
    void update();
    void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
    void clear();
    void setInterface();
    void drawBlock(int x, int y, int j);
    void updateScore();
    void updateNextBlockTab(int random);
    void drawElement();
    void countDown();
    bool moveElement(int dir);
    void rotateElement();
    void start();
    void hideOldElement();
    void redrawBoard(int row, int length);
};

#endif /* SCREEN_H */