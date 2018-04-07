#include <iostream>

#include "Blockchain.hpp"
#include "crow_all.h"

int main() {
    // TODO implement blockchain endpoints
    crow::SimpleApp app;

    CROW_ROUTE(app, "/mine")([](){
        return "Hello Blockchain";
    });

    app.port(18080).multithreaded().run();

    return 0;
}