#include <string>
#include "HexApplication.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main() {
    setlocale(LC_ALL, "");

    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.set(el::Level::Global, el::ConfigurationType::ToStandardOutput, "false");
    el::Loggers::reconfigureLogger("default", defaultConf);

    LOG(INFO) << "Start";

    HexApplication application;

    application.create();

    application.openFile("/Users/oscar/VirtualBox VMs/sitesetVM/box-disk001.vmdk");

    while(application.running) {
        application.run();
    }

    return EXIT_SUCCESS;
}