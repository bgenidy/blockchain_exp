#include <iostream>

#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

#include "Blockchain.hpp"
#include "crow_all.h"

int main(int argc, char **argv) {
    int port = 5000;

    if (argc == 2) {
        port = atoi(argv[1]);
    }
    else if (argc > 2) {
        string application = argv[0];
        cout << "Usage: " + application + " <port>" << endl;
        return 1;
    }

    boost::uuids::random_generator generator;
    crow::SimpleApp app;
    Blockchain blockchain;

    boost::uuids::uuid uuid = generator();
    string node_identifier = boost::lexical_cast<std::string>(uuid);

    CROW_ROUTE(app, "/mine")
            .methods("GET"_method)
                    ([&blockchain, &node_identifier]() {
                        // run proof of work algorithm to get the next proof...
                        json last_block = blockchain.lastBlock();
                        int proof = blockchain.proofOfWork(last_block);

                        // receive a reward for finding the proof.
                        // sender is "0" to signify that this node has
                        // mined a new coin
                        blockchain.newTransaction(
                                "0", // sender
                                node_identifier, // recipient
                                1 // amount
                        );

                        string previous_hash = blockchain.hash(last_block);
                        json block = blockchain.newBlock(proof, previous_hash);

                        json response = json::object();
                        response["message"] = "New Block Forged";
                        response["index"] = block["index"];
                        response["transactions"] = block["transactions"];
                        response["proof"] = block["proof"];
                        response["previous_hash"] = block["previous_hash"];

                        return response.dump();
                    });

    CROW_ROUTE(app, "/transactions/new")
               .methods("POST"_method)
                       ([&blockchain](const crow::request& req) {
                           json values = json::parse(req.body);

                           // check required fields exist
                           json required = {"sender", "recipient", "amount"};

                           for (auto& r: required) {
                               if (values.count(r) == 0) {
                                   return crow::response(400, "missing values");
                               }
                           }

                           int index = blockchain.newTransaction(
                                   values["sender"],
                                   values["recipient"],
                                   values["amount"]
                           );

                           json response = json::object();
                           response["message"] = "Transaction will be added to Block " + index;
                           return crow::response(201, response.dump());
                       });

    CROW_ROUTE(app, "/chain")
               .methods("GET"_method)
                       ([&blockchain]() {
                           json response = json::object();
                           response["chain"] = blockchain.getChain();
                           response["length"] = blockchain.getChain().size();
                           return response.dump();
                       });

    CROW_ROUTE(app, "/nodes/register")
               .methods("POST"_method)
                       ([&blockchain](const crow::request& req) {
                           json values = json::parse(req.body);

                           json nodes = values["nodes"];
                           if (nodes.empty()) {
                               return crow::response(400, "Error: Please supply a valid list of nodes");
                           }

                           for (auto& node: nodes) {
                               blockchain.registerNode(node);
                           }

                           json response = {
                                   {"message", "New nodes have been added"},
                                   {"total_nodes", blockchain.getNodes()}
                           };
                           return crow::response(201, response.dump());
                       });

    CROW_ROUTE(app, "/nodes/resolve")
               .methods("GET"_method)
                       ([&blockchain]() {
                           bool replaced = blockchain.resolveConflicts();
                           json response;

                           if (replaced) {
                               response = {
                                       {"message", "Our chain was replaced"},
                                       {"new_chain", blockchain.getChain()}
                               };
                           } else {
                               response = {
                                       {"message", "Our chain is authoritative"},
                                       {"chain", blockchain.getChain()}
                               };
                           }

                           return response.dump();
                       });

    app.port(port).multithreaded().run();

    return 0;
}