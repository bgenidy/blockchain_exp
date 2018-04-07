# Blockchain C++ Edition

### About Project
This is a C++ implementation of a blockchain. 
The goal of this implementation is to create a viable and usable embedded systems
blockchain.

This implementation would not be possible without the use of a few libraries:

[json library](https://github.com/nlohmann/json) 
developed by [nlohmann](https://github.com/nlohmann). For convenience his json library
has been ported directly in this project under `json.hpp`; however you can always find
the latest release of his library [here](https://github.com/nlohmann/json/releases).

[sha256 hash](https://github.com/okdshin/PicoSHA2) developed by [okdshin](https://github.com/okdshin).
For convenience his sha256 implementation has been ported directly in this project under `picosha2.h`.

[web requests](https://github.com/whoshuu/cpr) developed by [whoshuu](https://github.com/whoshuu).
This project uses a fork of his library that can be found under `cpr/`.

### How to run

libssl is need to make web requests. 
On ubuntu systems it can be installed using the following command:
```bash
sudo apt-get install libssl-dev 
```

**Implementation/Documentation coming soon!**