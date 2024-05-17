/* Copyright 2023 0x34d
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
      http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "block-auto.h"
#include "block/block.h"

#define kMinInputLength 5
#define kMaxInputLength 1024

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

    if (Size < kMinInputLength || Size > kMaxInputLength) {
        return 1;
    }

    td::Slice inputData(Data, Size);

    vm::BagOfCells boc;
    auto res = boc.deserialize(inputData);

    if (res.is_error()) {
        return 1;
    }
    if (res.move_as_ok() <= 0 || boc.get_root_cell().is_null()) {
        return 1;
    }

    auto root = boc.get_root_cell();
    block::gen::t_Block.validate_ref(root);

    ton::BlockIdExt id;
    std::vector<ton::BlockIdExt> prev;
    ton::BlockIdExt mc_blkid;
    bool after_split;
    block::unpack_block_prev_blk_try(root, id, prev, mc_blkid, after_split, &id);

    return 0;
}
