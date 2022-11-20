#!/bin/bash
echo "DEN install script (Version 0.1)"
echo "Creating build dir..."
cmake -S . -B build
cd build 
echo "Building..."
cmake --build . 
mv devenv ..
cd ..
echo "Done! Run './devenv' to start DEN
 