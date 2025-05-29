
#!/bin/bash

path=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
CC=/home/nvidia/df/HAD/S73a2/toolchain/arm-gnu-toolchain-12.2.rel1-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-gcc

$CC $path/main_test.c -o $path/../../output/bin/main_test
