#include "Window.h"
#include "easylogging++.h"

Window::Window() {
    if((handle = initscr()) == nullptr) {
        throw "Failed to instantiate ncurses";
    }

    // Suppress stdout
    noecho();

    // Enable keypad
    keypad(handle, true);

    // interrupt, quit, suspend, and flow control characters are all passed through uninterpreted
    raw();

    //cbreak();
    //wtimeout(handle, 500);
}

Window::Window(WINDOW *handle) {
    this->handle = handle;
    idlok(this->handle, true);
}

Window::~Window() {
    delwin(this->handle);
}

void Window::addString(std::string str) {
    waddstr(handle, str.c_str());
    //waddnstr()
    //waddchstr(handle, reinterpret_cast<const chtype*>(str.c_str()));
}

void Window::refresh() {
    //wrefresh(handle);
    wnoutrefresh(handle);
}

int Window::getInput() {
    return wgetch(handle);
}

int Window::width() {
    return getmaxx(handle);
}

int Window::height() {
    return getmaxy(handle);
}

int Window::x() {
    return getbegx(handle);
}

int Window::y() {
    return getbegy(handle);
}

void Window::moveCursor(int x, int y) {
    wmove(handle, y, x);
}

int Window::cursorX() {
    return getcurx(handle);
}

int Window::cursorY() {
    return getcury(handle);
}

void Window::erase() {
    werase(handle);
}

void Window::draw() {

}

int Window::resize(int width, int height) {
    return wresize(this->handle, height, width);
}
