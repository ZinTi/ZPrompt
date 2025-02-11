#!/bin/bash
g++ -std=c++17 -Wall -Os -I/usr/local/ssl/include main.cpp HashUtils.cpp -o digest -L/usr/local/ssl/lib64 -L/usr/lib/x86_64-linux-gnu -lssl -lcrypto -ldl -lpthread -static
