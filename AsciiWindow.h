#ifndef HEXCURSES_ASCIIWINDOW_H
#define HEXCURSES_ASCIIWINDOW_H

#include "Window.h"

class AsciiWindow : public Window {
public:
    AsciiWindow(WINDOW * handle);
    void draw() override;
    void setBuffer(uint8_t * buffer, int64_t bufferSize);

private:
    uint8_t * buffer = nullptr;
    int64_t bufferSize = 0;
};


#endif //HEXCURSES_ASCIIWINDOW_H
