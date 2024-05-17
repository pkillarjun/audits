#include "lte/gateway/c/core/oai/tasks/amf/amf_app_ue_context_and_proc.hpp"

using namespace magma5g;

#define kMinInputLength 10
#define kMaxInputLength 5120

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
/*
* amf/test_amf_encode_decode.cpp
*/

    if (Size < kMinInputLength || Size > kMaxInputLength){
        return 0;
    }
  
    amf_nas_message_t decode_msg = {};
    amf_nas_message_decode_status_t decode_status = {};
    int status = RETURNerror;

    status = nas5g_message_decode(Data, &decode_msg, Size, nullptr, &decode_status);

    return status;
}
