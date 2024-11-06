#include "network/server.hpp"
#include <iostream>

using namespace std;

int main() {
    try {
        DatabaseServer server(5432);  // Using PostgreSQL's default port
        server.start();
        return 0;
    }
    catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << endl;
        return 1;
    }
}
