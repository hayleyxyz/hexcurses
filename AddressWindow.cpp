#include "AddressWindow.h"

#include <sstream>
#include <iomanip>

AddressWindow::AddressWindow(WINDOW * handle) : Window(handle) {

}

void AddressWindow::draw() {
    this->erase();

    for (int i = 0; i < this->height(); ++i) {
        uint32_t address = this->startOffset + (i * 16);

        std::stringstream stream;
        stream << std::hex << std::setfill(' ') << std::setw(8) << address;

        this->addString(stream.str());
    }
}

void AddressWindow::setStartOffset(int64_t offset) {
    this->startOffset = offset;
}
