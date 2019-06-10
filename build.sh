#!/bin/bash
echo "pulling updates"
git pull
echo "building c++ files..."
g++ -std=c++17 main_test.cpp Util.cpp ProcessParser.cpp
echo "running program"
./a.out