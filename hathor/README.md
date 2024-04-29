# Fuzzing hathor-core

## Setup docker

```bash
docker pull ubuntu:20.04
docker run -it --name hathor --entrypoint bash docker.io/library/ubuntu:20.04
```

## Dependency & Harness

```bash
docker cp install.sh hathor:/
docker cp fuzz/ hathor:/home/hathor-core/tests/fuzz
```

## Run Fuzz test

```bash
poetry run python tests/fuzz/fuzz_block.py tests/fuzz/fuzz_block_corpus/
poetry run python tests/fuzz/fuzz_merge_mined_block.py tests/fuzz/fuzz_merge_mined_block_corpus/
poetry run python tests/fuzz/fuzz_nano.py tests/fuzz/fuzz_nano_corpus/
poetry run python tests/fuzz/fuzz_scripts.py tests/fuzz/fuzz_scripts_corpus/
poetry run python tests/fuzz/fuzz_token.py tests/fuzz/fuzz_token_corpus/
poetry run python tests/fuzz/fuzz_transaction.py tests/fuzz/fuzz_transaction_corpus/
```
