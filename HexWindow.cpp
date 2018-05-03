#include "HexWindow.h"

#include <sstream>
#include <iomanip>

HexWindow::HexWindow(WINDOW *handle) : Window(handle) {

}

void HexWindow::draw() {
    this->erase();

    std::stringstream stream;

    for (int i = 0; i < this->height(); ++i) {
        for (int j = 0; j < 16; ++j) {

            uint8_t byte = buffer[(i * 16) + j];

            stream << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint32_t>(byte);

            stream << ' ';
        }
    }

    this->addString(stream.str());
}

void HexWindow::setBuffer(uint8_t *buffer, int64_t bufferSize) {
    this->buffer = buffer;
    this->bufferSize = bufferSize;
}
