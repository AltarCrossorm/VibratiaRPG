#!/bin/bash

echo `basename $(pwd)`
cmake -B build -DDEBUG=ON

if [[ $? -eq 0 ]] ;then
	cd build
    make -j$(nproc)
else
    echo "CMake fumbled, escaping program launch"
    exit 1
fi

if [[ $? -eq 0 ]] ;then
    ./tests/DiscordRPGTests
else
    echo "Compilation went wrong, escaping program launch"
    exit 1
fi

if [[ $? -eq 0 ]] ;then
    ./DiscordRPG
else
    echo "Tests failed somewhere, escaping program launch"
    exit 1
fi
