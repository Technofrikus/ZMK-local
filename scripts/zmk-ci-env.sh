#!/usr/bin/env bash
# Aligns with ZMK upstream .github/workflows/build.yml:
# - container: docker.io/zmkfirmware/zmk-build-arm:4.1
# - west update --fetch-opt=--filter=tree:0
# - west build … -p (pristine, not -p always)
# Override for experiments: export ZMK_BUILD_IMAGE=… before sourcing.

export ZMK_BUILD_IMAGE="${ZMK_BUILD_IMAGE:-docker.io/zmkfirmware/zmk-build-arm:4.1}"
