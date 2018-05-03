#ifndef HEXCURSES_HEXWINDOW_H
#define HEXCURSES_HEXWINDOW_H

#include "Window.h"

class HexWindow : public Window {
public:
    HexWindow(WINDOW * handle);
    void draw() override;
    void setBuffer(uint8_t * buffer, int64_t bufferSize);

private:
    uint8_t * buffer = nullptr;
    int64_t bufferSize = 0;
};


#endif //HEXCURSES_HEXWINDOW_H
