#!/bin/sh

git submodule init
git submodule update

cd lib/glhck
git submodule init
git submodule update
cd -

mkdir target
cd target
cmake ..
make
