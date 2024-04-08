FROM ubuntu:jammy
WORKDIR /src
COPY . .

RUN \
    apt update && \
    apt install -y \
        g++ \
        perl \
        p7zip-full \
        nasm \
        tup \
        make \
        gcc \
        sudo \
        mtools \
        mkisofs \
        parted \
        gdisk \
        gcc-multilib \
        wget \
        git && \
    rm -rf /var/lib/apt/lists/*

RUN \
    wget "http://board.kolibrios.org/download/file.php?id=9919&sid=bc8412934004a60f831b1b92eae0ad34" -O install_kgcc && \
    chmod +x ./install_kgcc && \
    ./install_kgcc && \
    wget "https://websvn.kolibrios.org/filedetails.php?repname=Kolibri+OS&path=%2Fprograms%2Fdevelop%2Fktcc%2Ftrunk%2Fbin%2Fkos32-tcc" -O /home/autobuild/tools/win32/bin/kos32-tcc && \
    chmod +x /home/autobuild/tools/win32/bin/kos32-tcc

RUN \
    export PATH=/home/autobuild/tools/win32/bin:$PATH && \
    cd /src/programs/develop/objconv/ && \
    g++ -o objconv -O2 *.cpp && \
    chmod +x objconv && \
    mv objconv /home/autobuild/tools/win32/bin/. && \
    cd /src/programs/other/kpack/kerpack_linux/ && \
    make && \
    chmod +x kerpack && \
    mv kerpack /home/autobuild/tools/win32/bin/. && \
    cd /src/programs/other/kpack/linux/ && \
    bash build.sh && \
    chmod +x kpack && \
    mv kpack /home/autobuild/tools/win32/bin/. && \
    cd /src/programs/develop/clink && \
    gcc main.c -o clink && \
    chmod a+x clink && \
    mv clink /home/autobuild/tools/win32/bin/.
