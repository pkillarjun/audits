#include "vm/vm.h"
#include "vm/cp0.h"
#include "vm/dict.h"
#include "fift/utils.h"
#include "common/bigint.hpp"

#include "td/utils/base64.h"
#include "td/utils/tests.h"
#include "td/utils/ScopeGuard.h"
#include "td/utils/StringBuilder.h"

#include <unistd.h>

int main(int argc, char** argv)
{
/*vm.cpp test-vm*/
/*
 * crypto/test/vm.cpp
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

  fift::compile_asm(inputData);

  free(Data);
  fclose(infile);
  free(DataFx);

  return 0;
}
