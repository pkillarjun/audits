#!/usr/bin/env bash
export CC=clang
export CXX=clang++
export CFLAGS="-O1 -fno-omit-frame-pointer -gline-tables-only -fsanitize=address -fsanitize-address-use-after-scope"
export LIB_FUZZING_ENGINE="-fsanitize=fuzzer"

readonly EXTRA_BAZEL_FLAGS="$(
for f in ${CFLAGS}; do
  echo "--conlyopt=${f}" "--linkopt=${f}"
  echo "--cxxopt=${f}" "--linkopt=${f}"
done
)"

bazel build \
  --dynamic_mode=off \
  --repo_env=CC=${CC} \
  --repo_env=CXX=${CXX} \
  --linkopt=${LIB_FUZZING_ENGINE} \
  --linkopt=-lc++ \
  ${EXTRA_BAZEL_FLAGS} \
  //lte/gateway/c/core/oai/fuzzing/...:*

<<TEST
//lte/gateway/c/core/oai/fuzzing:gtpv2_fteid_test
./bazel-bin/lte/gateway/c/core/oai/fuzzing/gtpv2_fteid_test

bazel test \
  --dynamic_mode=off \
  --repo_env=CC=${CC} \
  --repo_env=CXX=${CXX} \
  ${EXTRA_BAZEL_FLAGS} \
  //lte/gateway/c/core/...:*
TEST
