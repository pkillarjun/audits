# Fuzzing
add_executable(fuzz_block fuzzing/fuzz-block.cpp)
target_link_libraries(fuzz_block PUBLIC ton_crypto fift-lib ton_block git ${LIB_FUZZING_ENGINE})

add_executable(fuzz_fift fuzzing/fuzz-fift.cpp)
target_link_libraries(fuzz_fift PRIVATE fift-lib ${LIB_FUZZING_ENGINE})

add_executable(fuzz_asm fuzzing/fuzz-asm.cpp)
target_link_libraries(fuzz_asm PRIVATE ton_crypto fift-lib ${LIB_FUZZING_ENGINE})

add_executable(fuzz_vm fuzzing/fuzz-vm.cpp)
target_link_libraries(fuzz_vm PRIVATE ton_crypto fift-lib ${LIB_FUZZING_ENGINE})

add_executable(fuzz_basic fuzzing/fuzz-basic.cpp)
target_link_libraries(fuzz_basic PRIVATE smc-envelope fift-lib ton_db memprof tdfec ${LIB_FUZZING_ENGINE})

add_executable(fuzz_ed25519 fuzzing/fuzz-ed25519.cpp)
target_link_libraries(fuzz_ed25519 PRIVATE ton_crypto ${LIB_FUZZING_ENGINE})

add_executable(fuzz_torrent fuzzing/fuzz-torrent.cpp)
target_link_libraries(fuzz_torrent PRIVATE storage ton_db memprof tl_api tl-utils fec rldp2 ${LIB_FUZZING_ENGINE})

add_executable(fuzz_raptorq fuzzing/fuzz-raptorq.cpp)
target_link_libraries(fuzz_raptorq PRIVATE tdfec tdutils ${LIB_FUZZING_ENGINE})

add_executable(fuzz_json fuzzing/fuzz-json.cpp)
target_link_libraries(fuzz_json PRIVATE tdutils ${LIB_FUZZING_ENGINE})

add_executable(fuzz_http fuzzing/fuzz-http.cpp)
target_link_libraries(fuzz_http PRIVATE tonhttp ${LIB_FUZZING_ENGINE})
