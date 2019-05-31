#!/bin/bash
echo "building c++ files..."
g++ -std=c++17 main_test.cpp Util.cpp ProcessParser.cpp
echo "done"