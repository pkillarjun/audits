#!/usr/bin/env bash

#compile AFL
export CC=clang
export CXX=clang++
pushd AFLplusplus/
make all
popd

#patch base
pushd patch/
cp llvm-gcov.sh /usr/bin/llvm-gcov.sh
chmod +x /usr/bin/llvm-gcov.sh
patch -b -d /root/ton/validator/. < validator-group.hpp.patch
popd

#make all Dir
pushd ton/
mkdir mybuild.afl
mkdir mybuild.cov
popd

#Compile ton.afl
export CC=/root/AFLplusplus/afl-clang-fast
export CXX=/root/AFLplusplus/afl-clang-fast++
#export CFLAGS="-O1 -fno-omit-frame-pointer -gline-tables-only -fsanitize=address,undefined -fsanitize-address-use-after-scope"
#export CXXFLAGS="-O1 -fno-omit-frame-pointer -gline-tables-only -fsanitize=address,undefined -fsanitize-address-use-after-scope -stdlib=libc++"
export LIB_FUZZING_ENGINE="-fsanitize=fuzzer"

pushd ton/mybuild.afl/
cmake \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo -DTON_USE_ABSEIL=OFF \
    -DCMAKE_C_FLAGS="-Wall -Wextra $CFLAGS" -DCMAKE_CXX_FLAGS="-Wall -Wextra $CXXFLAGS" -DCMAKE_EXE_LINKER_FLAGS="$CXXFLAGS" -DLIB_FUZZING_ENGINE="$LIB_FUZZING_ENGINE" ../.
make -j$(nproc) --ignore-errors
popd

<<COV
#Compile ton.cov
export CC=clang
export CXX=clang++
export CFLAGS="-O1 -fno-omit-frame-pointer -gline-tables-only  -fprofile-instr-generate -fcoverage-mapping -pthread -Wl,--no-as-needed -Wl,-ldl -Wl,-lm -Wno-unused-command-line-argument"
export CXXFLAGS="-O1 -fno-omit-frame-pointer -gline-tables-only  -fprofile-instr-generate -fcoverage-mapping -pthread -Wl,--no-as-needed -Wl,-ldl -Wl,-lm -Wno-unused-command-line-argument -stdlib=libc++"
export LIB_FUZZING_ENGINE="-fsanitize=fuzzer"

pushd ton/mybuild.cov/
cmake \
    -DCMAKE_BUILD_TYPE=Debug -DTON_USE_ABSEIL=OFF \
    -DCMAKE_C_FLAGS="-Wall -Wextra $CFLAGS" -DCMAKE_CXX_FLAGS="-Wall -Wextra $CXXFLAGS" -DCMAKE_EXE_LINKER_FLAGS="$CXXFLAGS" -DLIB_FUZZING_ENGINE="$LIB_FUZZING_ENGINE" ../.
make -j$(nproc)
popd
COV
