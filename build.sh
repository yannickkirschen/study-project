#!/bin/sh

# This script can be used to build the entire project.

set -e

WORKING_DIR=$(dirname "$0" | realpath)
export PICO_SDK_PATH=$WORKING_DIR/mini-rail/lib/pico-sdk

cmake -D TARGET_ARCH=host -B "${WORKING_DIR}"/mini-rail/build/host -S "${WORKING_DIR}"/mini-rail
cmake -D TARGET_ARCH=pico -B "${WORKING_DIR}"/mini-rail/build/embedded -S "${WORKING_DIR}"/mini-rail

make -C "${WORKING_DIR}"/mini-rail/build/host
make -C "${WORKING_DIR}"/mini-rail/build/embedded
