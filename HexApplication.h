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
    HexApplication();
    ~HexApplication();
    void create();
    void run();
    void openFile(std::string fp);
    int viewWidth();
    int viewHeight();
    int byteCapacity();
    int desiredHexWindowWidth();

    const int bufferMaxSize = 1024*1024*2; // 2mb

    bool running;

private:
    void fillBuffer();
    void draw();

    Window * window;
    AddressWindow * addressWindow;
    HexWindow * hexWindow;
    AsciiWindow * asciiWindow;

    /**
     * Current offset of the stream in the hex editor
     */
    int64_t editorOffset = 0;

    /**
     * Input stream we're presenting in the hex editor
     */
    std::fstream fs;

    /**
     * Total size of the input stream HexApplication::fs
     */
    int64_t streamSize = 0;

    /**
     * Offset in stream where buffer was read from
     */
    int64_t streamOffset = 0;

    /**
     * Temp buffer to hold data from stream
     */
    uint8_t * buffer = nullptr;

    /**
     * Size of above buffer
     */
    int64_t bufferSize = 0;

};


#endif //HEXCURSES_HEXAPPLICATION_H
