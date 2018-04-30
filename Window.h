#ifndef HEXCURSES_WINDOW_H
#define HEXCURSES_WINDOW_H

#include <string>
#include <ncurses.h>


class Window {

public:
    Window();
    Window(WINDOW * handle);
    ~Window();
    void addString(std::string str);
    void refresh();
    int getInput();
    int width();
    int height();
    int x();
    int y();
    int cursorX();
    int cursorY();
    void moveCursor(int x, int y);
    void clear();
    virtual void draw();

    template <class T>
    T * createSubWindow(int x, int y, int width, int height);

protected:
    WINDOW* handle;

};

template<class T>
T * Window::createSubWindow(int x, int y, int width, int height) {
    auto subHandle = newwin(height, width, y, x);
    return new T(subHandle);
}

#endif //HEXCURSES_WINDOW_H
