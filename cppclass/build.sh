/#!/bin/bash
g++ -c game.cpp
g++ -c game_map.cpp
g++ -c main.cpp
g++ -c entity.cpp
g++ -c entity_transformer.cpp
g++ -c physic_entity.cpp
g++ -c platform.cpp
g++ -c player.cpp

g++ game.o main.o game_map.o entity.o entity_transformer.o physic_entity.o platform.o player.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

