# ReverbSC for LMMS

This repository aims to be a proof-of-concept way to build LMMS
plugins separately from the LMMS project using CMake. 

This has only been tested on Linux. YMMV

To compile:

mkdir build
cd build
cmake -G "Unix Makefiles" ../
make
sudo cp libreverbsc.so /usr/local/lib/lmms

When you start up LMMS, you should hopefully see an effect called "ReverbSC". 
