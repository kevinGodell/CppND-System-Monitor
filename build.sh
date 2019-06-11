#!/bin/bash
echo "pulling updates"
git pull
echo "building c++ files..."
g++ -std=c++17 main_test.cpp ProcessParser.cpp Util.cpp SysInfo.cpp -o app
echo "running program"
./app