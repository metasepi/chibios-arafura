# Snatch [ChibiOS/RT](http://www.chibios.org/) using [Ajhc](http://ajhc.metasepi.org/)

Let's try to rewrite [ChibiOS/RT](http://www.chibios.org/)
using Haskell and [Ajhc](http://ajhc.metasepi.org/) compiler.

## Before start

### Buy [stm32f3-discovery](http://www.st.com/web/en/catalog/tools/FM116/SC959/SS1532/PF254044)

![](https://raw.github.com/ajhc/demo-cortex-m3/master/img/stm32f3-discovery.jpg)

* CPU: STM32F303VCT6
* ROM: 256kB
* RAM: 48kB

### Install summon-arm-toolchain

    $ git clone git://github.com/esden/summon-arm-toolchain.git
    $ apt-get install flex bison libgmp3-dev libmpfr-dev libncurses5-dev \
      libmpc-dev autoconf texinfo build-essential libftdi-dev zlib1g-dev \
      git zlib1g-dev python-yaml
    $ cd summon-arm-toolchain/
    $ ./summon-arm-toolchain
    $ export PATH=$HOME/sat/bin:$PATH

### Install stlink

    $ sudo apt-get install libsgutils2-dev libusb-1.0-0-dev
    $ git clone git://github.com/texane/stlink.git
    $ cd stlink/
    $ ./autogen.sh
    $ ./configure
    $ make
    $ sudo make install

## How to build

    $ git clone https://github.com/metasepi/chibios-arafura.git
    $ cd chibios-arafura/demos/ARMCM4-STM32F303-DISCOVERY/
    $ make

## How to write firmware

In one terminal, start the connection to the board.

    $ sudo st-util

In another terminal, connect to the debugger and flash program.

    $ make gdbwrite
    --snip--
    Loading section .isr_vector, size 0x188 lma 0x8000000
    Loading section .text, size 0x1ec4 lma 0x8000188
    Loading section .data, size 0x5c lma 0x800204c
    Start address 0x8001f89, load size 8360
    Transfer rate: 6 KB/sec, 2786 bytes/write.
    (gdb) c
