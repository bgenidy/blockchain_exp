import hashlib
import json

from uuid import uuid4
from time import time

class BlockChain(object):
    def __init__(self):
        self.chain = []
        self.current_transactions = []

        self.new_block(previous_hash='1', proof=100)

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