#!/bin/bash
echo "## DEN install script (Version 0.1) ##"
echo "Pulling from remote..."
git pull --recurse-submodules
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
<<<<<<< HEAD
sudo rm -rf /usr/local/bin/devenv
sudo mv devenv /usr/local/bin/
=======
>>>>>>> parent of 4a9a089 (Update to: Install shell script)
echo "## Done! Run './devenv' to start DEN ##"
