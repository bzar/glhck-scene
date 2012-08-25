#!/bin/sh

git submodule update --init --recursive

mkdir target
cd target
cmake ..
make
