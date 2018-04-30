#include "HexApplication.h"


HexApplication::~HexApplication() {
    if(!isendwin()) {
        endwin();
    }
}

void HexApplication::create() {
    this->window = new Window();

    addressWindow = window->createSubWindow<AddressWindow>(0, 0, 8, 0);
    hexWindow = window->createSubWindow<HexWindow>(addressWindow->width() + 1, 0, static_cast<int>((16 * 2) * 1.5), 0);
    asciiWindow = window->createSubWindow<AsciiWindow>(hexWindow->x() + hexWindow->width(), 0, 16, 0);

    buffer = new uint8_t[this->bufferSize];

    this->running = true;
}

void HexApplication::open(std::string fp) {
    fs.open(fp, std::ios::in | std::ios::binary);

    fs.seekg(0, std::ios::end);
    auto pos = fs.tellg();

    this->inputSize = static_cast<int64_t>(pos);

    this->fillBuffer();
}

void HexApplication::fillBuffer() {
    fs.seekg(this->offset);
    fs.read(reinterpret_cast<char*>(buffer), this->bufferSize);
}

void HexApplication::run() {
    this->draw();

    auto input = window->getInput();
    if(input == 'q') {
        this->running = false;
        return;
    }
    else if(input == KEY_DOWN) {
        this->offset = std::min(this->offset + 16, this->inputSize - 1);
        this->fillBuffer();
    }
    else if(input == KEY_UP) {
        this->offset = std::max(this->offset - 16, 0ll);
        this->fillBuffer();
    }
}

void HexApplication::draw() {
    addressWindow->setStartOffset(this->offset);
    hexWindow->setBuffer(this->buffer, this->bufferSize);
    asciiWindow->setBuffer(this->buffer, this->bufferSize);

    addressWindow->draw();
    hexWindow->draw();
    asciiWindow->draw();

    addressWindow->refresh();
    hexWindow->refresh();
    asciiWindow->refresh();
    window->refresh();
}