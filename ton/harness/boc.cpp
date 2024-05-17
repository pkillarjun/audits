#include "vm/boc.h"
#include "vm/cellslice.h"
#include "vm/cells.h"
#include "common/AtomicRef.h"
#include "vm/cells/CellString.h"
#include "vm/cells/MerkleProof.h"
#include "vm/cells/MerkleUpdate.h"
#include "vm/db/CellStorage.h"
#include "vm/db/CellHashTable.h"
#include "vm/db/TonDb.h"
#include "vm/db/StaticBagOfCellsDb.h"

#include "td/utils/base64.h"
#include "td/utils/benchmark.h"
#include "td/utils/crypto.h"
#include "td/utils/Random.h"
#include "td/utils/Slice.h"
#include "td/utils/Span.h"
#include "td/utils/Status.h"
#include "td/utils/Timer.h"
#include "td/utils/filesystem.h"
#include "td/utils/port/path.h"
#include "td/utils/format.h"
#include "td/utils/misc.h"
#include "td/utils/optional.h"
#include "td/utils/tests.h"
#include "td/utils/tl_parsers.h"
#include "td/utils/tl_helpers.h"

#include "td/db/utils/BlobView.h"
#include "td/db/RocksDb.h"
#include "td/db/MemoryKeyValue.h"
#include "td/db/utils/CyclicBuffer.h"

#include "td/fec/fec.h"

#include <set>
#include <map>

#include <openssl/sha.h>

#include "openssl/digest.hpp"


#include <unistd.h>
using namespace vm;

int main(int argc, char** argv)
{
/*
 * crypto/test/test-db.cpp
 * tonlib/tonlib/TestWallet.cpp
 * tonlib/tonlib/Wallet.cpp
 * test-db boc
*/

  if(argc < 2) {
    printf("Usage: %s <input file>\n", argv[0]);
    return 0;
  }

  uint8_t *Data;
  size_t Size;
  FILE *infile;

  infile = fopen(argv[1],"rb");

  fseek(infile, 0L, SEEK_END);
  Size = ftell(infile);
  fseek(infile, 0L, SEEK_SET);

  Data = (uint8_t*)calloc(Size, sizeof(uint8_t));
  fread(Data, sizeof(char),Size, infile);

  uint8_t *DataFx;
  size_t SizeFx = Size+1;
  DataFx = (uint8_t *)calloc(SizeFx,sizeof(uint8_t));
  memcpy((void *)DataFx,(void *)Data,Size);

  td::Slice inputData(DataFx,Size);


  vm::std_boc_deserialize(inputData);

  BagOfCells boc;
  auto res = boc.deserialize(inputData);

  free(Data);
  free(DataFx);
  fclose(infile);

  return 0;
}
