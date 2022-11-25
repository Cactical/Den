#!/bin/sh
echo "## DEN install script (Version 0.1) ##"
echo "#### This script builds and installs the latest version of DEN. ####"
echo "#### This script also uninstalls and reinstalls DEN if already installed, so it can be used to update DEN. ####"
echo "#### Pulling Den scripts from remote... ####"
git fetch
git pull https://github.com/Cactical/Den.git denscripts
echo "#### Cloning Den code from remote... ####"
cd
git clone https://github.com/Cactical/Den.git --branch dencode --single-branch --recurse-submodules dencode
echo "#### Entering code dir... #### "
cd dencode 
echo "#### Creating build dir... #### "
cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ -S . -B ./build -G Ninja
echo "#### Entering build dir... #### "
cd build 
echo "#### Building and installing... ####"
cmake --build . --config Release --target all
sudo rm -rf /usr/local/bin/devenv
sudo mv devenv /usr/local/bin/
cd ..
echo "#### Cleaning up... ####"
cd ..
sudo rm -rf ~/dencode
echo "## Done! Run 'devenv' to start DEN. ##"