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

#include "td/utils/base64.h"
#include "smc-envelope/ManualDns.h"
#include <iomanip>

#define kMinInputLength 5
#define kMaxInputLength 1024

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

    if (Size < kMinInputLength || Size > kMaxInputLength) {
        return 1;
    }

    td::Slice inputData(Data, Size);
    {
        vm::BagOfCells boc;
        boc.deserialize(inputData);
    }
    {
        vm::std_boc_deserialize(inputData);
    }
    {
        ton::ManualDns::parse(inputData);
    }
    {
        block::StdAddress::parse(inputData);
    }
    {
        td::base64_decode(inputData);
    }
    {
        block::PublicKey::parse(inputData);
    }

    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (size_t i = 0; i < Size; i++) {
        ss << std::setw(2) << static_cast<int>(Data[i]);
    }

    std::string str = ss.str();
    td::Slice code_hex = td::Slice(str.data(), str.size());
    {
        unsigned char buff[1024];
        int bits = (int)td::bitstring::parse_bitstring_hex_literal(buff, sizeof(buff), code_hex.begin(), code_hex.end());
    }

    return 0;
}
