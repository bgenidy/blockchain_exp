
#include <iostream>
#include <ctime>
#include "Blockchain.hpp"

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
    // TODO
    return false;
}

bool Blockchain::resolveConflicts() {
    // TODO
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
    // TODO
    return "";
}

bool Blockchain::validProof(int lastProof, int proof, string lastHash) {
    // TODO
    return false;
}