#!/bin/bash

#set -x

XCODE_IPHONE_SIMULATOR_DIR=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform
IPHONE_SIMULATOR_AR=${XCODE_IPHONE_SIMULATOR_DIR}/Developer/usr/bin/ar

if [ -d "$XCODE_IPHONE_SIMULATOR_DIR" -a ! -e "$IPHONE_SIMULATOR_AR" ]
then
    echo "Error: \`ar\` not found for iPhoneSimulator at ${IPHONE_SIMULATOR_AR}"
    echo
    echo "This is probably a bug with Xcode 5. You can fix it with the following command:"
    echo
    echo "sudo ln -s ../../Toolchains/XcodeDefault.xctoolchain/usr/bin/ar $IPHONE_SIMULATOR_AR"
    exit 1
fi

platform="all"
configuration="Debug"
make_targets="all"

if [ "x$1" = "x-h" -o "x$1" = "x--help" ]
then
  echo "Usage: $(basename $0) [all|host|ios-device|ios-simulator|ios-universal|osx-ios-universal] [Debug|Release] [make_target_1 [make_target_2 [...]]]"
  exit
fi

if [ $# -ge 1 ]
then
  platform=$1
  shift
fi

if [ $# -ge 1 ]
then
  configuration=$1
  shift
fi

if [ $# -ge 1 ]
then
  make_targets="$@"
fi

if [ $platform = "all" ]
then
  platforms="host ios-device ios-simulator ios-universal osx-ios-universal"
elif [ $platform = "ios-universal" ]
then
  platforms="ios-device ios-simulator ios-universal"
elif [ $platform = "osx-ios-universal" ]
then
  platforms="host ios-device ios-simulator ios-universal osx-ios-universal"
else
  platforms=$platform
fi

parent_pwd=$(pwd)

for p in $platforms; do
  echo "==> building platform '$p'"
  p_build_dir="$parent_pwd/build/$p/$configuration"
  p_out_dir="$p_build_dir/out"
  p_out_lib_dir="$p_out_dir/lib"
  p_out_lib_static_filename="$p_out_lib_dir/libopencash-static.a"

  mkdir -p "$p_build_dir"
  cd "$p_build_dir"

  if [ $p = "ios-universal" ]
  then
    rm -rf "$p_out_dir"
    mkdir -p "$p_out_dir"
    cp -r "$parent_pwd/build/ios-device/$configuration/out/include" "$p_out_dir/include"
    mkdir -p "$p_out_lib_dir"
    lipo -create \
      "$parent_pwd/build/ios-device/$configuration/out/lib/libopencash-static.a" \
      "$parent_pwd/build/ios-simulator/$configuration/out/lib/libopencash-static.a" \
      -output "$p_out_lib_static_filename" >/dev/null

  elif [ $p = "osx-ios-universal" ]
  then
    rm -rf "$p_out_dir"
    mkdir -p "$p_out_dir"
    cp -r "$parent_pwd/build/ios-device/$configuration/out/include" "$p_out_dir/include"
    mkdir -p "$p_out_lib_dir"
    lipo -create \
      "$parent_pwd/build/host/$configuration/out/lib/libopencash-static.a" \
      "$parent_pwd/build/ios-universal/$configuration/out/lib/libopencash-static.a" \
      -output "$p_out_lib_static_filename" >/dev/null

  else
    [ $configuration = "Debug" ] && cmake_debug_arg="-DOC_DEBUG=ON"
    cmake $cmake_debug_arg -DOC_STATIC=ON -DOC_PLATFORM=$p "$parent_pwd" &&
      make $make_targets &&
      rm -rf "$p_out_lib_static_filename" &&
      libtool -static -o "${p_out_lib_static_filename}.tmp" "${p_out_lib_dir}"/*.a >/dev/null &&
      mv "${p_out_lib_static_filename}.tmp" "${p_out_lib_static_filename}"
  fi

  echo "<== done platform '$p'"
  cd "$parent_pwd"
done

echo "done."
