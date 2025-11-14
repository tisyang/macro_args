# macro_args
command line arguments process by x-macros

## Feature
1. Header file only.
2. No malloc.
3. Less depends, only std and `getopt`.
4. Support shot arg opt and long arg opt.

## Usage
See [Example](example_args.c)


```bash
# compile
gcc -o args example_args.c
# run
./args -h
Usage: ./args [-h|--help] [-p|--print] [-v|--verbose=<level>] [-t|--timeout=<secs>] [--longonly=<flag>] [-s=<test>] [-f|--from=<file>]

Example:
 -h, --help                   show help
 -p, --print                  print arg struct
 -v, --verbose=<level>        verbose level
 -t, --timeout=<secs>         timeout in secs
 --longonly=<flag>            test long only arg
 -s=<test>                    test short only arg
 -f, --from=<file>            file path

# run
./args -p
optind =2
 arg [0]help: 0 (-h, --help, show help)
 arg [1]print: 1        (-p, --print, print arg struct)
 arg [0]verbose: 0      (-v, --verbose=<level>, verbose level)
 arg [0]timeout: 0      (-t, --timeout=<secs>, timeout in secs)
 arg [0]longonly: 0     (--longonly=<flag>, test long only arg)
 arg [0]shortonly: 0    (-s=<test>, test short only arg)
 arg [0]from: (null)    (-f, --from=<file>, file path)

# run
./args --not-exists
./args: unrecognized option '--not-exists'

```
