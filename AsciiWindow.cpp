#include "AsciiWindow.h"

#include <sstream>
#include <iomanip>

AsciiWindow::AsciiWindow(WINDOW *handle) : Window(handle) {

}

void AsciiWindow::draw() {
    this->clear();

    std::stringstream stream;

    for (int i = 0; i < this->height(); ++i) {
        for (int j = 0; j < 16; ++j) {

            uint8_t byte = buffer[(i * 16) + j];

            std::string display = ".";

            if(byte >= 33) {
                display = static_cast<char>(byte);
            }

            stream << display;
        }
    }

    this->addString(stream.str());
}

void AsciiWindow::setBuffer(uint8_t *buffer, int bufferSize) {
    this->buffer = buffer;
    this->bufferSize = bufferSize;
}
