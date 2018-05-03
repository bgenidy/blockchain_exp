# Blockchain

### About this repo
This repository is a compilation of all my research into different blockchain
concepts, applications, implementations, etc.

### Directory Break Down
[docs.md](./docs.md) : Contains all articles that I have found interesting and are related to
blockchain concepts.

[src-python](./src-python) : Contains a python implementation of a blockchain.
(implementation was done for learning purposes)

[src-c++](./src-c++) : Contains a C++ implementation of a blockchain.
(implementation is geared towards embedded systems)

### Knowledge Gained

From February 2018 – May 2018 I conducted research in different Blockchain technologies, concepts and implementations. The result was the development of a simple Proof of Work Blockchain implementation in C++. This Blockchain was written in C++ to develop an embedded systems Blockchain. Future enhancements of this Blockchain could be the following set of features:

-	Wallet feature: The implementation of a wallet feature will allow nodes to easily identify and manage their own balances as well as efficiently check the balance of other nodes on the network.
-	Switch from Proof of Work to Proof of Stake: While different implementations have different benefits, since the main goal of this project is to have a Blockchain that could potentially be deployed on remote systems, it makes since that the implementation should leverage less power constrained algorithms.
-	Heartbeat capabilities: By creating heartbeat capabilities nodes can detect changes across the Blockchain network much quicker.
-	Partial table download: As the Blockchain gets bigger, it will be necessary for nodes to participate without having the full ledger, otherwise many embedded devices might not be able to support the implementation for long.

There are many other features that could be incorporated, but this is a good start for enhancements.

#### Summary of Concepts

During my research into these technologies, I learned a few things about different Blockchain concepts and in the proceeding documentation I will summarize a few of those findings.
**Please keep in mind that this is my understanding of these concepts, so there might be a few errors. For any corrections or enhancements please feel free to submit a PR.**

To understand anything mentioned below in further details refer to [docs.md](./docs.md) as it contains all articles utilized for the below descriptions.

##### Proof of Work
Miners (i.e compute nodes) have to solve a cryptographic puzzle as fast as possible where they are competing with other miners. The first miner to solve this puzzle gets a reward (free crypto coins). This puzzle is meant to be hard to solve (i.e compute intensive and time consuming), but easy to verify by other miners. This type of consensus algorithm is the most well-known one due to its usage in Bitcoin (bitcoin was the first blockchain).

##### Proof of Stake
In this consensus algorithm nodes vote on the mined blocks and your vote is impacted by how much stake you have into the blockchain. Therefore, you must own a portion of the blockchain to participate in the blockchain.  This is the second most popular consensus algorithm due to its usage in Casper (Casper is an Ether fork). It has started gaining large popularity as a viable alternative to Proof of Work because it requires much less energy and hardware to operate.

##### Consensus Algorithm Safety (copied from [here]( https://blockgeeks.com/guides/proof-of-work-vs-proof-of-stake/))
Any computer system wants to be free from the possibility of hacker attacks, especially if the service is related to money.
So, the main problem is: proof of stake safer than proof of work?
Experts are worried about it, and there are several skeptics in the community.
Using a Proof-of-Work system, bad actors are cut out thanks to technological and economic disincentives.
In fact, programming an attack to a PoW network is very expensive, and you would need more money than you can steal from the attack.
Instead, the underlying PoS algorithm must be as bulletproof as possible because, without penalties, a proof of stake-based network could be cheaper to attack.
To solve this issue, Buterin created the Casper protocol, designing an algorithm that can use the set some circumstances under which a bad validator might lose their deposit.
He explained: “Economic finality is accomplished in Casper by requiring validators to submit deposits to participate, and taking away their deposits if the protocol determines that they acted in some way that violates some set of rules (‘slashing conditions’).”
Slashing conditions refer to the circumstances above or laws that a user is not supposed to break.

##### Enterprise Level Blockchain

Conventionally most public blockchains are used for cryptocurrency; however, blockchains can be used for any ledger based info (contracts, money, logs, etc.) because in its simplest form a blockchain is a write only database. Due to the inherent increased security, available in utilizing a blockchain over conventional database (decentralized, trustless, no single point of failure, data can’t be altered) enterprises are very interested in leveraging such concepts into their businesses. Unfortunately, current blockchains are implemented in a trustless manner which significantly impacts performance. For an enterprise, they can create a slight trust relationship between their consensus nodes which will significantly improve performance and bring blockchain concensus down to a reasonable time amount. The current most widely proposed solution of achieving such a task is to utilize trusted execution environments provided by the native OS or hardware (such as intel SGX or Windows VSM) to decouple the blockchain operations from other system operations, thus insuring the integrity of data provided from each node that is participating in the consensus.

