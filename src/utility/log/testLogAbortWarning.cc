#include "Log.h"

void test() {
    int x = 10;
    LOG_HANDLER_SET_ABORT_LEVEL_WARNING();
    LOG(INFO) << "sdad" << x << "asda" << ")\n";
    LOG(WARNING) << "OOASkdpadk ";
    LOG(ERROR) << "Hello " << (2 + 3);
    LOG(FATAL) << "Go home\n";
}

int main() {
    test();
    return 0;
}

