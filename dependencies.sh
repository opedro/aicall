#!/bin/bash
set -e

apk update
apk add --no-cache \
    build-base \
    openssl-dev \
    curl-dev \
    flite-dev \
    nlohmann-json \
    ca-certificates
