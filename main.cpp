#include <string>
#include "HexApplication.h"

int main() {
    setlocale(LC_ALL, "en_US.ISO8859-1");

    HexApplication application;

    application.create();

    application.open("hexcurses");

    while(application.running) {
        application.run();
    }

    return EXIT_SUCCESS;
}