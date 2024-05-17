### Compile
```
    docker build -t ton:build .
    docker run -it --name ton --entrypoint bash ton:build
    bash build.sh
```


### Note: Read ./patch/ folder, After Compile.

### Report with gef
```
apt-get install curl file
bash -c "$(curl -fsSL https://gef.blah.cat/sh)"
gdb -x GDBrun --args ./test-fift report/bug.*.raw
```
