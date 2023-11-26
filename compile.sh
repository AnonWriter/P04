#!/bin/bash
#programa para compilar desde bash (linux)
gcc src/ej/TADColaDin.c src/sim2.c src/sim3.c src/main.c -lncurses -o bin/main
