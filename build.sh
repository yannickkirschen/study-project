#!/bin/sh

# This script can be used to build the entire project.

WORKING_DIR=$(dirname $0 | realpath)
export PICO_SDK_PATH=$WORKING_DIR/rail/lib/pico-sdk

make -C ${WORKING_DIR}/rail

cmake -S ${WORKING_DIR}/rail/embedded -B ${WORKING_DIR}/rail/target/embedded
make -C ${WORKING_DIR}/rail/target/embedded
