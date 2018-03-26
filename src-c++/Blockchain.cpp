
#include "Blockchain.hpp"

Blockchain::Blockchain() {
    current_transactions = json::array();
    chain = json::array();
    nodes = json::array();
}

void Blockchain::registerNode(string address) {
    // TODO validate that address is a properly formatted address
    long sz = nodes.size();

    for (long i = 0; i < sz; i++) {
        if (nodes[i] == address) {
            return; // already exists
        }
    }

    nodes[sz] = address;
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
    // TODO
    return nullptr;
}

int Blockchain::newTransaction(string sender, string recipient, json amount) {
    // TODO
    return 0;
}

json Blockchain::lastBlock() {
    return chain[chain.size()-1];
}

int Blockchain::proofOfWork(json lastBlock) {
    // TODO
    return -1;
}

static string Blockchain::hash(json block) {
    // TODO
    return nullptr;
}

static bool Blockchain::validProof(int lastProof, int proof, string lastHash) {
    // TODO
    return false;
}