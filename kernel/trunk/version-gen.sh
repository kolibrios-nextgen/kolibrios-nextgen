#!/bin/bash

# Copyright (C) KolibriOS-NG team 2024. All rights reserved
# Distributed under terms of the GNU General Public License

set -eu

full_ver=$(git describe --tag --long)

tag=$(echo $full_ver | cut -d'-' -f1 | cut -c 2-)
offset=$(echo $full_ver | cut -d'-' -f2)
hash=$(echo $full_ver | cut -d'-' -f3 | cut -c 2-)

a_ver=$(echo $tag | cut -d'.' -f1)
b_ver=$(echo $tag | cut -d'.' -f2)

short_ver=$(printf %-14s "v$a_ver.$b_ver-$offset")

cat << EOF
macro VERSION_INFO {
        db  $a_ver, $b_ver
        dw  $offset
.hash   db  '$hash', 0
}

macro BOOT_VERSION_INFO {
        db  '$short_ver',13,10,13,10,0
}
EOF
