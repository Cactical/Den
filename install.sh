#!/bin/bash
echo "## DEN install script (Version 0.1) ##"
echo "#### Pulling Den scripts from remote... ####"
git pull
echo "#### Cloning Den code from remote... ####"
cd
git clone https://github.com/Cactical/Den.git --branch dencode --single-branch --recurse-submodules dencode
echo "### Entering code dir... #### "
cd dencode 
cd devenv.proj/inc 
ls 
cd ..
cd ..
echo "#### Creating build dir... #### "
cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ -S ~/dencode -B ~/dencode/build -G Ninja
cd build 
echo "#### Building... ####"
cmake --build . --config Release --target all
mv devenv ..
cd ..
echo "#### Cleaning up... ####"
cd ..
sudo rm -rf /usr/local/bin/devenv
sudo mv devenv /usr/local/bin/
echo "## Done! Run 'devenv' to start DEN ##"
