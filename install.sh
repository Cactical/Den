#!/bin/bash
echo "DEN install script (Version 0.1)"
echo "#### Creating build dir... #### "
cmake -S . -B build
cd build 
echo "#### Building... ####"
cmake --build . 
mv devenv ..
cd ..
echo "#### Cleaning up... ####"
rm -rf build
rm -rf devenv.proj
rm -rf CMakeLists.txt
echo "Done! Run './devenv' to start DEN"
