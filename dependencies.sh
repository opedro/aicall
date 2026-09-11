#!/bin/bash
set -e

apt-get update
apt-get install -y \
    build-essential \
    libssl-dev \
    nlohmann-json3-dev \
    flite1-dev \
    ca-certificates
