#!/bin/bash
echo "pulling updates"
git pull
echo "compiling app..."
g++ -std=c++17 main.cpp Process.cpp ProcessContainer.cpp ProcessParser.cpp SysInfo.cpp Util.cpp -o app -lncurses
echo "running program"
./app