### Change Files:
```
cp fift.cpp ton/crypto/test/fift.cpp
```


### Chnage ton/CMakeLists.txt
```
add_executable(test-fift test/test-td-main.cpp ${FIFT_TEST_SOURCE})

to

add_executable(test-fift ${FIFT_TEST_SOURCE})
```