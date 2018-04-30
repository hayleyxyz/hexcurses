#ifndef HEXCURSES_ADDRESSWINDOW_H
#define HEXCURSES_ADDRESSWINDOW_H

#include "Window.h"

class AddressWindow : public Window {
public:
    AddressWindow(WINDOW * handle);
    void draw() override;

    void setStartOffset(int64_t i);

private:
    int64_t startOffset;
};


#endif //HEXCURSES_ADDRESSWINDOW_H
