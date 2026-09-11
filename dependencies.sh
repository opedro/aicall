#!/bin/bash
set -e

sudo apt-get update
sudo apt-get install -y \
    build-essential \
    libssl-dev \
    nlohmann-json3-dev \
    flite1-dev
