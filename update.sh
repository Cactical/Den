#!/bin/sh
echo "## DEN update script (Version 0.1) ##"
echo "#### This script updates the scripts (not DEN itself). ####"
git fetch
git pull https://github.com/Cactical/Den.git denscripts
echo "## Done! Run 'install.sh' to install DEN. ##"