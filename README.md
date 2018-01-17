# gbs_player

A program for playing Game Boy sound (.gbs) files.

Do note that this is very much a work in progress.

## TODO

* Proper sound filter & resampling
* Game Boy Color support
* Platform independent controls
* Pass blargg's sound tests
* Sound visualizations

## Compile

Dependencies:

* libao (for audio output)

To compile, do

```
make
```

in the project root directory.

To compile with debugging support, [gbz80-disasm](https://github.com/frestr/gbz80-disasm) must configured.

Note: Only works on Linux for now, as the terminal controls are platform dependent.

## Usage

Run the program with your .gbs file as an argument:

```
$ ./player 
Usage: ./player <gbs-file>
```

### Controls

* `n`: next song
* `p`: previous song
* `q`: quit player

## Example

```
$ ./player DMG-TRA-0.gb
GBS version:      1
Song count:       17
First song:       1
Load address:     0x64e5
Init address:     0x64e5
Play address:     0x6553
Stack pointer:    0xcfff
Timer modulo:     0x0
Timer control:    0x0
Title:            Tetris v1.0
Author:           Hirokazu Tanaka
Copyright:        1989 Nintendo
Playing song no. 1
```

_cue music_
