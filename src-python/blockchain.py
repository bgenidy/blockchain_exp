import hashlib
import json
import requests

from time import time

from textwrap import dedent
from uuid import uuid4
from flask import Flask, jsonify, request
from urllib.parse import urlparse

class BlockChain(object):
    def __init__(self):
        self.chain = []
        self.current_transactions = []
        self.nodes = set()

        self.new_block(previous_hash='1', proof=100)

    def register_node(self, address):
        """
        add a new node to the list of nodes

        :param address: <str> address of node ex. 'http://192.168.1.12:5000'
        :return:
        """

        parsed_url = urlparse(address)
        self.nodes.add(parsed_url.netloc)

    def new_block(self, proof, previous_hash=None):
        """
        Create a new block in the blockchain

        :param proof: <int> proof given by proof of work algorithm
        :param previous_hash: (optional) <str> hash of previous block
        :return: <dict> new block
        """
        block = {
            'index': len(self.chain) + 1,
            'timestamp': time(),
            'transactions': self.current_transactions,
            'proof': proof,
            'previous_hash': previous_hash or self.hash(self.chain[-1])
        }

        # reset current list of transactions
        self.current_transactions = []

        self.chain.append(block)
        return block

    def new_transactions(self, sender, recipient, amount):
        """
        Creates a new transaction to go into the next mined block

        :param sender: <str> address of the sender
        :param recipient: <str> address of the recipient
        :param amount: <int> amount
        :return: <int> index of the block holding this transaction
        """
        self.current_transactions.append({
            'sender': sender,
            'recipient': recipient,
            'amount':amount,
        })

        return self.last_block['index'] + 1

    def proof_of_work(self, last_proof):
        """
        Simple proof of work algorithm:
        - find a number p' such that hash(pp') contains leading 4 zeroes,
        where p is the previous p'
        - p is the previous proof, and p' is the new proof
        :param last_proof: <int>
        :return: <int>
        """

        proof = 0
        while self.valid_proof(last_proof, proof) is False:
            proof += 1

        return proof

    def valid_chain(self, chain):
        """
        determine if a gien blockchain is valid

        :param chain: <list> a blockchain
        :return: <bool> true if valid, false if not
        """
        last_block = chain[0]
        current_index = 1

        while current_index < len(chain):
            block = chain[current_index]
            print(f'{last_block}')
            print(f'{block}')
            print('\n-------\n')

            # check hash of block is correct
            if block['previous_hash'] != self.hash(last_block):
                return False

            # check that PoW is correct
            if not self.valid_proof(last_block['proof'], block['proof']):
                return False

            last_block = block
            current_index += 1

        return True

    def resolve_conflicts(self):
        """
        consensus algorithm. resolves conflicts by replacing the chain
        with the longest one in the network.

        :return: <bool> True if our chain was replaced, False if not
        """
        neighbours = self.nodes
        new_chain = None

        # looking for chains longer than us
        max_length = len(self.chain)

        # grap and verify the chains from all nodes in our network
        for node in neighbours:
            response = requests.get(f'http://{node}/chain')

            if response.status_code == 200:
                length = response.json()['length']
                chain = response.json()['chain']

                # check if the length is longer and the chain is valid
                if length > max_length and self.valid_chain(chain):
                    max_length = length
                    new_chain = chain

        if new_chain:
            self.chain = new_chain
            return True

        return False

    @staticmethod
    def valid_proof(last_proof, proof):
        """
        Validates the proof: does hash(last_proof, proof) contains 4 leading zeroes?

        :param last_proof: <int> previous proof
        :param proof: <int> current proof
        :return: <bool> True if correct, False if not
        """

        guess = f'{last_proof}{proof}'.encode()
        guess_hash = hashlib.sha256(guess).hexdigest()
        return guess_hash[:4] == '0000'


    @staticmethod
    def hash(block):
        """
        Creates a sha-256 hash of a block

        :param block: <dict> block
        :return: <str>
        """

        # ensure dictionary is ordered for consistent hashes
        block_string = json.dumps(block, sort_keys=True).encode()
        return hashlib.sha256(block_string).hexdigest()

    @property
    def last_block(self):
        # returns the last block in the chain
        return self.chain[-1]

# init node
app = Flask(__name__)

# generate globally unique address for this node
node_identifier = f'{uuid4()}'.replace('-','')

# init the blockchain
blockchain = BlockChain()

@app.route('/mine', methods=['GET'])
def mine():
    # run proof of work algorithm to get the next proof
    last_block = blockchain.last_block
    last_proof = last_block['proof']
    proof = blockchain.proof_of_work(last_proof)

    # give reward for finding proof
    blockchain.new_transactions(sender='0', recipient=node_identifier, amount=1)

    # force the new block by adding it to the chain
    previous_hash = blockchain.hash(last_block)
    block = blockchain.new_block(proof, previous_hash)

    response = {
        'message': 'new block forged',
        'index': block['index'],
        'transactions': block['transactions'],
        'proof': block['proof'],
        'previous_hash': block['previous_hash'],
    }
    return jsonify(response), 200

@app.route('/transactions/new', methods=['POST'])
def new_transaction():
    values = request.get_json()

    # check that the required fields are in the POST data
    required = ['sender', 'recipient', 'amount']
    if not all(k in values for k in required):
        return 'Missing values', 400

    index = blockchain.new_transactions(values['sender'], values['recipient'], values['amount'])

    response = {'message': f'Transaction will be added to Block {index}'}
    return jsonify(response), 201

@app.route('/chain', methods=['GET'])
def full_chain():
    response = {
        'chain': blockchain.chain,
        'length': len(blockchain.chain)
    }
    return jsonify(response), 200

@app.route('/nodes/register', methods=['POST'])
def register_nodes():
    values = request.get_json()

    nodes = values.get('nodes')
    if nodes is None:
        return 'Error: Please supply a valid list of nodes', 400

    for node in nodes:
        blockchain.register_node(node)

    response = {
        'message': 'New nodes have been added',
        'total_nodes': list(blockchain.nodes),
    }

    return jsonify(response), 201

@app.route('/nodes/resolve', methods=['GET'])
def consensus():
    replaced = blockchain.resolve_conflicts()

    if replaced:
        response = {
            'message': 'Our chain was replaced',
            'new_chain': blockchain.chain
        }
    else:
        response = {
            'message': 'Our chain is authoritative',
            'chain': blockchain.chain
        }

    return jsonify(response), 200


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

