#!/usr/bin/env bash
export CC=/AFLplusplus/afl-clang-fast
export CXX=/AFLplusplus/afl-clang-fast++
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

mkdir /out/
cp bazel-bin/lte/gateway/c/core/oai/fuzzing/nas5g_message_decode /out/.
cp bazel-bin/lte/gateway/c/core/oai/fuzzing/nas_message_decode /out/.

cp -r lte/gateway/c/core/oai/fuzzing/*_seed_corpus/ /out/
