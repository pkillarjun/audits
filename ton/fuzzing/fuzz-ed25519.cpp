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

#include "crypto/ellcurve/Ed25519.h"

#define kMinInputLength 50
#define kMaxInputLength 1024
#define KeySize 32
#define SignatureSize 64

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

    if (Size < kMinInputLength || Size > kMaxInputLength) {
        return 1;
    }

    uint8_t rfc8032_secret_key[KeySize] = {0};
    uint8_t rfc8032_signature[SignatureSize] = {0};
    uint8_t* rfc8032_message = new uint8_t[Size - KeySize]();

    memcpy(rfc8032_secret_key, Data, KeySize);
    memcpy(rfc8032_message, Data + KeySize, Size - KeySize);

    crypto::Ed25519::PrivateKey PK;
    PK.import_private_key(rfc8032_secret_key);


    uint8_t rfc8032_public_key[KeySize] = {0};
    PK.export_public_key(rfc8032_public_key);


    crypto::Ed25519::PublicKey PubK(rfc8032_public_key);
    PK.sign_message(rfc8032_signature, rfc8032_message, Size - KeySize);


    PubK.check_message_signature(rfc8032_signature, rfc8032_message, Size - KeySize);


    uint8_t secret12[32] = {0};
    uint8_t secret21[32] = {0};
    uint8_t temp_pubkey[32] = {0};

    crypto::Ed25519::TempKeyGenerator TKG;

    TKG.create_temp_shared_secret(temp_pubkey, secret12, PubK, rfc8032_message, Size - KeySize);

    PK.compute_temp_shared_secret(secret21, temp_pubkey);

    delete[] rfc8032_message;
    return 0;
}
