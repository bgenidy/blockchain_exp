
#ifndef SRC_C_BLOCKCHAIN_HPP
#define SRC_C_BLOCKCHAIN_HPP

#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Blockchain {
private:
    json current_transactions;
    json chain;
    json nodes;

public:
    Blockchain();
    void registerNode(string address);
    bool validChain(json chain);
    bool resolveConflicts();
    json newBlock(int proof, string previous_hash);
    int newTransaction(string sender, string recipient, json amount);
    json lastBlock();
    int proofOfWork(json lastBlock);

    // getters
    json getChain();
    json getNodes();

    static bool isValidAddress(string address);
    static string hash(json block);
    static bool validProof(int lastProof, int proof, string lastHash);
};


#endif //SRC_C_BLOCKCHAIN_HPP
