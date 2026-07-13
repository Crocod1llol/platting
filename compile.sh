#!/bin/bash

g++ -Wpedantic -Wall -Wextra -o game main.cpp -L./lib -lraylib -lm -lpthread -ldl -lrt -lX11
