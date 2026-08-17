#!/bin/bash

echo `basename $(pwd)`
cmake -B build -DDEBUG=ON

if [[ $? -eq 0 ]] ;then
	cd build
	echo "CMake ok"
    make -j$(nproc)
else
    echo "CMake fumbled, escaping program launch"
    exit 1
fi

if [[ $? -eq 0 ]] ;then
	echo "Make ok"
    #./tests/DiscordRPGTests
else
    echo "Compilation went wrong, escaping program launch"
    exit 1
fi

if [[ $? -eq 0 ]] ;then
	echo "Tests ok"
    ./DiscordRPG
else
    echo "Tests failed somewhere, escaping program launch"
    exit 1
fi
