#!/bin/bash -eu
# Copyright 2023 0x34d
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
################################################################################

export ASAN_OPTIONS=detect_leaks=0

if [ -d "mybuild" ]; then
    rm -rf mybuild
fi
mkdir mybuild/

pushd mybuild/
cmake \
    -DCMAKE_C_FLAGS="-Wall -Wextra $CFLAGS" -DCMAKE_CXX_FLAGS="-Wall -Wextra $CXXFLAGS" \
    -DCMAKE_EXE_LINKER_FLAGS="$CXXFLAGS" -DLIB_FUZZING_ENGINE="$LIB_FUZZING_ENGINE" ../.
make -j$(($(nproc)*2))
popd

cp $SRC/ton/mybuild/fuzz_asm        $OUT/
cp $SRC/ton/mybuild/fuzz_basic      $OUT/
cp $SRC/ton/mybuild/fuzz_block      $OUT/
cp $SRC/ton/mybuild/fuzz_ed25519    $OUT/
cp $SRC/ton/mybuild/fuzz_fift       $OUT/
cp $SRC/ton/mybuild/fuzz_http       $OUT/
cp $SRC/ton/mybuild/fuzz_json       $OUT/
cp $SRC/ton/mybuild/fuzz_raptorq    $OUT/
cp $SRC/ton/mybuild/fuzz_torrent    $OUT/
cp $SRC/ton/mybuild/fuzz_vm         $OUT/

cp $SRC/ton/fuzzing/fuzz_asm_seed_corpus.zip        $OUT/
cp $SRC/ton/fuzzing/fuzz_basic_seed_corpus.zip      $OUT/
cp $SRC/ton/fuzzing/fuzz_block_seed_cropus.zip      $OUT/
cp $SRC/ton/fuzzing/fuzz_ed25519_seed_cropus.zip    $OUT/
cp $SRC/ton/fuzzing/fuzz_fift_seed_corpus.zip       $OUT/
cp $SRC/ton/fuzzing/fuzz_http_seed_cropus.zip       $OUT/
cp $SRC/ton/fuzzing/fuzz_json_seed_corpus.zip       $OUT/
cp $SRC/ton/fuzzing/fuzz_raptorq_seed_cropus.zip    $OUT/
cp $SRC/ton/fuzzing/fuzz_torrent_seed_corpus.zip    $OUT/
cp $SRC/ton/fuzzing/fuzz_vm_seed_corpus.zip         $OUT/
