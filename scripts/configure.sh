#! /bin/sh
cmake -DGLFW_BUILD_DOCS=OFF -DUSE_USELESS_LIB=OFF -DCMAKE_INSTALL_PREFIX=./build/install -S . -B build