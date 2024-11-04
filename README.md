# OpenSSL-entropy

Own lab to proof how RAND_bytes() work.

The code that includes a call to `RAND_add` with hard-coded entropy sources: a timestamp (in microseconds), the process ID (`PID`), and a simulated "mouse movement" value. These values are then fed into `RAND_add` to strengthen the entropy before calling `RAND_bytes`. 
But please be aware this code using OpenSSL 0.9.8c that was made to be "vulnerable" again. Don't use in the production.

## Compilation:
    
    gcc -o main main.cpp -I./openssl-0.9.8c-vuln/include -L./openssl-0.9.8c-vuln -lssl -lcrypto

## Running:
    
    LD_LIBRARY_PATH=./openssl-0.9.8c-vuln/ ./main

    LD_LIBRARY_PATH=./openssl-0.9.8c-vuln/ ./pkb2pkh

The result:
```shell
Bitcoin Private Key (Hex): 2fd4ffb77d59f68384d2090b2761d51bc25876412c338c58609e83ae9b6f70f6
```