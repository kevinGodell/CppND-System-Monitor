#!/bin/bash
echo "pulling updates"
git pull
echo "compiling c++ files..."
g++ -std=c++17 -c main.cpp
g++ -std=c++17 -c Process.cpp
g++ -std=c++17 -c ProcessContainer.cpp
g++ -std=c++17 -c ProcessParser.cpp
g++ -std=c++17 -c SysInfo.cpp
g++ -std=c++17 -c Util.cpp
echo "linking compiled files..."
g++ -std=c++17 main.o Process.o ProcessContainer.o ProcessParser.o SysInfo.o Util.o -o app
echo "running program"
./app