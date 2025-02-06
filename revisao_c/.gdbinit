target remote localhost:1234
dir $ZEPHYR_BASE
load ./build/zephyr/zephyr.elf
b main
tui enable
c
