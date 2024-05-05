# SPDX-License-Identifier: GPL-2.0-only
# SPDX-FileCopyrightText: 2024 KolibriOS-NG Team

#!/usr/bin/env bash

# Build toolchain
docker build --pull --rm -f Dockerfile.toolchain -t kolibriosng-toolchain:latest .

# Build system (ENG)
docker build -f Dockerfile.build-eng --output data .
mv data/kolibri.img data/kolibri-eng.img
mv data/kolibri.iso data/kolibri-eng.iso
mv data/kolibri.raw data/kolibri-eng.raw

# Build system (RUS)
docker build -f Dockerfile.build-rus --output data .
mv data/kolibri.img data/kolibri-rus.img
mv data/kolibri.iso data/kolibri-rus.iso
mv data/kolibri.raw data/kolibri-rus.raw
