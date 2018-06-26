#include "server_warnings.h"

#include "../util/print_manager.h"

using namespace std;
using namespace util;

void net::printEndPointWarning(const string& addrAndPort) {
    string message = "failed to initialize endpoint \"" + addrAndPort + "\"";
    PrintManager::instance().printWarning(message);
}

void net::printRunWarning(const string& methodName) {
    string message = "failed to run server";
    if (!methodName.empty()) {
        message += " (" + methodName + ")";
    }
    PrintManager::instance().printWarning(message);
}