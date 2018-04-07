# Blockchain C++ Edition

### About Project
C++ implementation of a blockchain.

### How to run

**Prereqs**

libssl is required by `cpr` library.

**For Ubuntu**
```bash
sudo apt-get install libssl-dev 
```

libboost is required by `crow` library.

**For Ubuntu**
```bash
sudo apt-get install libboost-all-dev
```

`crow` library also recommends the following should be installed.

**For Ubuntu**
```bash
sudo apt-get install build-essential libtcmalloc-minimal4 && sudo ln -s /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libtcmalloc_minimal.so
```

### External Libraries Used

[json](https://github.com/nlohmann/json) - json library<br>
[PicoSHA2](https://github.com/okdshin/PicoSHA2) - sha256 library<br>
[cpr](https://github.com/whoshuu/cpr) - web requests library (similar to python requests)<br>
[crow](https://github.com/ipkn/crow) - web framework (similar to flask)