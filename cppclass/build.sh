/#!/bin/bash
g++ -c -g main.cpp
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
rm main.o
