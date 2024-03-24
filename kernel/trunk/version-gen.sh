#!/bin/bash

# Copyright (C) KolibriOS-NG team 2024. All rights reserved
# Distributed under terms of the GNU General Public License 

full_version=$(git describe --tag)

version=$(echo $full_version | cut -d'-' -f1 | cut -c 2-)
offset=$(echo $full_version | cut -d'-' -f2)
hash=$(echo $full_version | cut -d'-' -f3)

major=$(echo $version | cut -d'.' -f1)
minor=$(echo $version | cut -d'.' -f2)
patch=$(echo $version | cut -d'.' -f3)


boot_gen()
{
cat > version.inc << EOF
db      '$full_version', 13,10,13,10,0
EOF
}

kernel_gen()
{
cat > version.inc << EOF
        db  $major, $minor, $patch
        dd  $offset
.hash   db  '$hash', 0
EOF
}

case $1 in
    "--kernel" ) kernel_gen ;;
    "--boot" ) boot_gen ;;
    *) fatal "Unknown argument!"
esac
