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

#include "http/http.h"

#define kMinInputLength 5
#define kMaxInputLength 1024

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

    if (Size < kMinInputLength || Size > kMaxInputLength) {
        return 1;
    }

    td::ChainBufferWriter w;
    w.init(0);
    w.append(td::Slice(Data, Size));
    auto r = w.extract_reader();

    bool exit_loop = false;
    std::string cur_line = "";
    auto Req = ton::http::HttpRequest::parse(nullptr, cur_line, exit_loop, r);
    auto Res = ton::http::HttpResponse::parse(nullptr, cur_line, false, false, exit_loop, r);

    return 0;
}
