#!/bin/bash
echo "## DEN install script (Version 0.1) ##"
echo "#### Pulling Den code from remote... ####"
cd
git clone https://github.com/Cactical/Den.git --branch dencode --single-branch dencode
echo "### Entering code dir... #### "
cd dencode 
cd devenv.proj/inc 
ls 
cd ..
cd ..
echo "#### Creating build dir... #### "
cmake -S . -B build /usr/bin/clang 
cd build 
echo "#### Building... ####"
cmake --build . --config Release --target all
mv devenv ..
cd ..
echo "#### Cleaning up... ####"
cd ..
rm -rf dencode
sudo rm -rf /usr/local/bin/devenv
sudo mv devenv /usr/local/bin/
echo "## Done! Run 'devenv' to start DEN ##"
