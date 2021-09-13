Feuille64 MIDI Arpgiator
-------------------------------
## What is this?
This is alternative firmware for Feuille64 based on Polygome.   

## build
```sh
> make
```

## test
```sh
// prepare
> cd test
test> cmake -S . -B build

// test
test> cmake --build build && ./build/test_scale
```