#include <vector>
#include "HexApplication.h"
#include "easylogging++.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/disk.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>


HexApplication::HexApplication() {

}

HexApplication::~HexApplication() {
    delete this->window;
    delete this->hexWindow;
    delete this->asciiWindow;
    delete this->addressWindow;

    if(!isendwin()) {
        endwin();
    }

    fs.close();
}


void HexApplication::create() {
    this->window = new Window();

    addressWindow = window->createSubWindow<AddressWindow>(0, 0, 8, 0);
    hexWindow = window->createSubWindow<HexWindow>(addressWindow->width() + 1, 0, this->desiredHexWindowWidth(), 0);
    asciiWindow = window->createSubWindow<AsciiWindow>(hexWindow->x() + hexWindow->width(), 0, 16, 0);

    this->running = true;
}

void HexApplication::openFile(std::string fp) {
    fs.open(fp, std::ios::in | std::ios::binary);

    fs.seekg(0, std::ios::end);
    auto pos = fs.tellg();

    this->streamSize = static_cast<int64_t>(pos);

    this->fillBuffer();
}

void HexApplication::fillBuffer() {
    if (this->buffer == nullptr || this->editorOffset < this->streamOffset || this->editorOffset + this->byteCapacity() > this->streamOffset + this->bufferSize) {
        if (this->buffer == nullptr) {
            buffer = new uint8_t[this->bufferMaxSize];
        }

        this->bufferSize = std::min<int64_t>(this->bufferMaxSize, this->streamSize);

        if(this->bufferSize >= (this->streamSize - this->streamOffset)) {
            this->streamOffset = this->streamSize - this->bufferSize;
        }
        else {
            this->streamOffset = this->editorOffset;
        }

        fs.seekg(this->streamOffset, std::ios_base::seekdir::beg);

        LOG(INFO) << "streamOffset: " << streamOffset;
        LOG(INFO) << "streamSize: " << streamSize;
        LOG(INFO) << "bufferSize: " << bufferSize;
        LOG(INFO) << "read: " << fs.tellg();
        LOG(INFO) << "";


        fs.read(reinterpret_cast<char*>(buffer), this->bufferSize);
    }
}

void HexApplication::run() {
    auto input = window->getInput();

    if(input == 'q') {
        this->running = false;
        return;
    }
    else if(input == KEY_DOWN) {
        this->editorOffset = std::min(this->editorOffset + 16, this->streamSize - this->byteCapacity());

        this->fillBuffer();
    }
    else if(input == KEY_UP) {
        if(this->editorOffset == 0) {
            return;
        }

        this->editorOffset = std::max(this->editorOffset - 16, 0ll);
        this->fillBuffer();
    }
    else if(input == KEY_RESIZE) {
        if(window->width() <= 48) return;
    }

    this->draw();
}

void HexApplication::draw() {
    addressWindow->setStartOffset(this->editorOffset);

    this->fillBuffer();

    hexWindow->setBuffer(&this->buffer[this->editorOffset - this->streamOffset], this->bufferSize);
    asciiWindow->setBuffer(&this->buffer[this->editorOffset - this->streamOffset], this->bufferSize);

    //hexWindow->resize(this->desiredHexWindowWidth(), 0);

    LOG(INFO) << "getmaxx(window->handle): " << window->width();

    addressWindow->draw();
    hexWindow->draw();
    asciiWindow->draw();

    window->refresh();
    addressWindow->refresh();
    hexWindow->refresh();
    asciiWindow->refresh();

    doupdate();
}

int HexApplication::viewWidth() {
    return 16;
}

int HexApplication::viewHeight() {
    return this->window->height();
}

int HexApplication::byteCapacity() {
    return this->viewWidth() * this->viewHeight();
}

int HexApplication::desiredHexWindowWidth() {
    return static_cast<int>((this->viewWidth() * 2) * 1.5);
}
