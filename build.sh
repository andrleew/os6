#! /bin/bash

make
rm *.o
mkdir bin
mv server client bin
