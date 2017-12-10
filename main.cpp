#include "Server.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;
int main() {
    Server server;
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
    server.Play();
    server.stop();
}