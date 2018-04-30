#ifndef HEXCURSES_HEXAPPLICATION_H
#define HEXCURSES_HEXAPPLICATION_H

#include <ncurses.h>
#include <fstream>
#include "Window.h"
#include "AddressWindow.h"
#include "HexWindow.h"
#include "AsciiWindow.h"

class HexApplication {

public:
    void create();
    void run();
    ~HexApplication();
    void open(std::string fp);

    const int bufferSize = 1024;

    bool running;

private:
    void fillBuffer();
    void draw();

    Window * window;
    AddressWindow * addressWindow;
    HexWindow * hexWindow;
    AsciiWindow * asciiWindow;

    std::fstream fs;
    uint8_t *  buffer = nullptr;
    int64_t offset = 0;
    int64_t inputSize = 0;
};


#endif //HEXCURSES_HEXAPPLICATION_H
