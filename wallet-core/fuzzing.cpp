/*
 * export CC=clang
 * export CXX=clang++
 * export CMAKE_C_FLAGS="-O1 -fno-omit-frame-pointer -gline-tables-only -fsanitize=address -fsanitize=undefined -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link"
 * cmake -DCMAKE_C_COMPILER="$CC" -DCMAKE_CXX_COMPILER="$CXX" -DCMAKE_C_FLAGS="$CMAKE_C_FLAGS" -DCMAKE_CXX_FLAGS="$CMAKE_C_FLAGS" ../.
 * make -j$(nproc)
 */

#include <cstring>
#include <memory>

#include "Cbor.h"
#include "Data.h"
#include "Ethereum/ABI.h"
#include "Ethereum/ABI/ValueDecoder.h"
#include "Ethereum/RLP.h"
#include "Everscale/CommonTON/Cell.h"
#include "FIO/Action.h"
#include "FIO/NewFundsRequest.h"
#include "FIO/Transaction.h"
#include "Mnemonic.h"
#include "NEO/CoinReference.h"
#include "NEO/ReadData.h"
#include "NEO/Transaction.h"
#include "NEO/TransactionAttribute.h"
#include "NEO/TransactionAttributeUsage.h"
#include "NEO/TransactionOutput.h"
#include "NEO/TransactionType.h"
#include "NEO/Witness.h"
#include <TrustWalletCore/TWEthereumAbi.h>
#include <TrustWalletCore/TWEthereumAbiFunction.h>
#include <TrustWalletCore/TWMnemonic.h>
#include <TrustWalletCore/TWString.h>

#define STRING(x) std::shared_ptr<TWString>(TWStringCreateWithUTF8Bytes(x), TWStringDelete)
#define WRAPS(x) std::shared_ptr<TWString>(x, TWStringDelete)

using namespace TW;
using namespace TW::NEO;

#define kMinInputLength 25
#define kMaxInputLength 1024

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *DataIn, size_t Size) {

    if (Size < kMinInputLength || Size > kMaxInputLength) {
        return 1;
    }

    char* data = (char *)malloc(Size + 1);
    std::memcpy((void*)data, DataIn, Size);
    data[Size] = '\0';

    Data dataInput(reinterpret_cast<byte*>(data), reinterpret_cast<byte*>(data + Size));

/*
    {
        TWMnemonicIsValid(STRING(data).get());
    }

    {
        TW::Mnemonic::isValid(data);
    }
    {
       const auto decode = TW::Cbor::Decode(dataInput);
       decode.isValid();
    }
    {
        try {
            auto decodedItem = TW::Ethereum::RLP::decode(dataInput);
        } catch (...) {
            // Nothing ! 
        }
    }
*/
    {
        TWEthereumAbiFunction* func = TWEthereumAbiFunctionCreateWithString(WRAPS(TWStringCreateWithUTF8Bytes("readout")).get());
        auto twData = TWDataCreateWithBytes(reinterpret_cast<const uint8_t*>(data), Size);

        TWEthereumAbiDecodeOutput(func, twData);

        TWDataDelete(twData);
        TWEthereumAbiFunctionDelete(func);
    }
/*
    {
        TW::Ethereum::ABI::ValueDecoder::decodeValue(dataInput, "uint");
        TW::Ethereum::ABI::ValueDecoder::decodeArray(dataInput, "uint8[]");
    }
    {
        try {
            TW::CommonTON::Cell::deserialize((const uint8_t *)data, Size);
        } catch(...) {
            // Nothing !
        }
    }
    {
        size_t index = 0;
        try {
            const auto newFunds = TW::FIO::NewFundsContent::deserialize(dataInput, index);
        } catch(...) {
            // Nothing!
        }
    }
    {
        auto coinReference = CoinReference();
        auto transactionAttribute = TransactionAttribute();
        auto transactionOutput = TransactionOutput();
        auto deWitness = Witness();
        auto deserializedTransaction_ = Transaction();
 
        try {
            coinReference.deserialize(dataInput);
            transactionAttribute.deserialize(dataInput);
            transactionOutput.deserialize(dataInput);
            deWitness.deserialize(dataInput);
            deserializedTransaction_.deserialize(dataInput);
            std::unique_ptr<Transaction> deserializedTransaction(Transaction::deserializeFrom(dataInput));
        } catch(...) {
            // Nothing!
        }
    }
*/
    free(data);
    return 0;
}

//./tests/fuzzer save-crash/crash-036c495b33c4e99f4ce8f50dd10dbfc7b93d088d
//./tests/fuzzer save-crash/crash-24131dc2118363beef3866b57a720eb8ac53928a
//./tests/fuzzer save-hang/timeout-10741c304c41aa575ca1df2390e683f2419603b6
