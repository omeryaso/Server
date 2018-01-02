#include "Server.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;
int main() {
    try {
    Server server;
    try {
        server.start();

        cout << "Enter exit to stop server" << endl;
        string str;
        cin >> str;
        if (str == "exit")
            server.stop();

    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
//    server.stop();
    } catch (const char *msg) {
        cout << msg << endl;
    }
}