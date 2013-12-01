#!/bin/bash

oldpwd=`pwd`

for target in host ios iossimulator; do
    echo "Building for target '$target'"
    mkdir -p build/$target/Debug &&
    cd build/$target/Debug &&
    cmake -DOC_DEBUG=ON -DOC_STATIC=ON -DOC_TARGET=$target ../../.. &&
    make &&
    cd "$oldpwd"
done

cd "$oldpwd"
