#!/bin/bash

g++ -std=c++11 bezier.cpp -o bin/bezier -lsfml-graphics -lsfml-system -lsfml-window
./bin/bezier