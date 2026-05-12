#!/bin/bash

#rodar esse enquanto os .hnão estiverem pronto
#gcc main.c -o programa

#rodar esse depois q .h estiverem prontos
gcc main.c src/*.c -I include -o programa
if [ $? -eq 0 ]; then
    ./main
fi