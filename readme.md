Feuille64 MIDI Arpeggiator 
-------------------------------
## What is this?
Firmware of MIDI arpeggiator for [Feuille64](https://booth.pm/ja/items/3148735).

based on [Polygome](https://github.com/monome-community/polygome).   

## manual
[日本語マニュアル](docs/feuille64_MIDI_Firmware_manual_jp.md)

# pre compiled hex file
https://github.com/hsgw/feuille64-midi/tree/build

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

## License
See LICENSE

(c) 2021, Takuya Urakawa (hsgw)
