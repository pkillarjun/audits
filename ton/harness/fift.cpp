#include "fift/words.h"
#include "fift/Fift.h"
#include "fift/utils.h"

#include "td/utils/tests.h"
#include "td/utils/PathView.h"
#include "td/utils/port/path.h"
#include "td/utils/filesystem.h"

int main(int argc, char** argv)
{
/*fift.cpp test-fift*/
/*
 * crypto/test/fift.cpp
 * crypto/test/fift/.fif
*/

    if(argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        return 0;
    }

    int ret = 0;
    std::string file(argv[1]);

    auto readfile =  td::read_file_str(file).move_as_ok();

    auto res = fift::mem_run_fift(readfile);
    if(res.is_error()){
      ret = 1;
    }

  return 0;
}
