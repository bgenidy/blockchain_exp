
#include <iostream>
#include <ctime>
#include "Blockchain.hpp"
#include "picosha2.h"

Blockchain::Blockchain() {
    current_transactions = json::array();
    chain = json::array();
    nodes = json::array();

    newBlock(1, "100");
}

void Blockchain::registerNode(string address) {
    // TODO validate that address is a properly formatted address

    for (auto& element: nodes) {
        if (element == address) {
            return; // already exists
        }
    }

    nodes.push_back(address);
}

bool Blockchain::validChain(json chain) {
    json last_block = chain[0];
    int current_index = 1;

    while (current_index < chain.size()) {
        json block = chain[current_index];
        cout << last_block.dump() << endl;
        cout << block.dump() << endl;
        cout << "\n--------------\n" << endl;

        if (block["previous_hash"] != hash(last_block)) {
            return false;
        }

        if (!validProof(last_block["proof"], block["proof"], last_block["previous_hash"])) {
            return false;
        }

        last_block = block;
        current_index++;
    }

    return true;
}

bool Blockchain::resolveConflicts() {
    json neighbours = nodes;
    json new_chain;

    long max_length = chain.size();

    for(auto& node: neighbours) {
        // TODO make web requests to the neighbouring nodes to compare chains
    }

    if (!new_chain.empty()) {
        chain = new_chain;
        return true;
    }

    return false;
}

json Blockchain::newBlock(int proof, string previous_hash) {
    json block = json::object();
    block["index"] = chain.size() + 1;
    time_t now = time(0);
    block["timestamp"] = ctime(&now);
    block["transactions"] = current_transactions;
    block["proof"] = proof;
    block["previous_hash"] = previous_hash.empty() ? hash(chain[chain.size()-1]) : previous_hash;

    current_transactions.clear();

    chain.push_back(block);
    return block;
}

int Blockchain::newTransaction(string sender, string recipient, json amount) {
    json transaction = json::object();
    transaction["sender"] = sender;
    transaction["recipient"] = recipient;
    transaction["amount"] = amount;

    current_transactions.push_back(transaction);
    int index = lastBlock()["index"];
    return index + 1;
}

json Blockchain::lastBlock() {
    return chain[chain.size()-1];
}

int Blockchain::proofOfWork(json last_block) {
    int last_proof = lastBlock()["proof"];
    string last_hash = hash(last_block);

    int proof = 0;
    while (validProof(last_proof, proof, last_hash) == false) {
        proof++;
    }

    return proof;
}

string Blockchain::hash(json block) {
    return picosha2::hash256_hex_string(block.dump());
}

bool Blockchain::validProof(int lastProof, int proof, string lastHash) {
    string guess = std::to_string(lastProof) + "" + std::to_string(proof) + "" + lastHash;
    string guess_hash = picosha2::hash256_hex_string(guess);
    return guess_hash.substr(0,4) == "0000";;
}