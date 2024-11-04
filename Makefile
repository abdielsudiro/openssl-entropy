

all: main.cpp
	gcc -o main main.cpp -I./openssl-0.9.8c-vuln/include -L./openssl-0.9.8c-vuln -lssl -lcrypto
