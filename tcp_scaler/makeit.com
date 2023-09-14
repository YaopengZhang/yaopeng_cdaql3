#!/bin/bash
# must run this ./makeit.com
rm xcli
rm xser

gcc -w -o xcli clientScaler.c
gcc -w -o xser serverScaler.c
