# macro_args
command line arguments parse using c x-macros

## Feature
1. Header file only.
2. No malloc/free.
3. Less depends, only std and `getopt`.
4. Support shot argument and long argument.
5. Support multiple occurrences of the same argument.

## Usage
See [Example](example_args.c)


```bash
# compile
gcc -Wall -o args example_args.c

# run
 ./args -h
Usage: ./args [-h|--help] [-p|--print] [-v|--verbose] [-t|--timeout=<secs>] [--longonly] [-s] [-f|--from=<file>] [-k|--token=<token>]

Example:
 -h, --help                   show help
 -p, --print                  print arg struct
 -v, --verbose                verbose
 -t, --timeout=<secs>         timeout in secs
 --longonly                   test long only arg
 -s                           test short only arg
 -f, --from=<file>            file path
 -k, --token=<token>          process tokens

# run
./args -p
optind =2
 arg help(-h, --help, show help): [0]
 arg print(-p, --print, print arg struct): [1]
 arg verbose(-v, --verbose, verbose): [0]
 arg timeout(-t, --timeout=<secs>, timeout in secs): [0/1]
 arg longonly(--longonly, test long only arg): [0]
 arg shortonly(-s, test short only arg): [0]
 arg from(-f, --from=<file>, file path): [0/1]
 arg token(-k, --token=<token>, process tokens): [0/32]

Need token provide

# run
./args --not-exists
./args: unrecognized option '--not-exists'
Usage: ./args [-h|--help] [-p|--print] [-v|--verbose] [-t|--timeout=<secs>] [--longonly] [-s] [-f|--from=<file>] [-k|--token=<token>]

./args -t 3.2323 -k token1 -k token2 -k token3 -p
optind =10
 arg help(-h, --help, show help): [0]
 arg print(-p, --print, print arg struct): [1]
 arg verbose(-v, --verbose, verbose): [0]
 arg timeout(-t, --timeout=<secs>, timeout in secs): [1/1]
  3.2323
 arg longonly(--longonly, test long only arg): [0]
 arg shortonly(-s, test short only arg): [0]
 arg from(-f, --from=<file>, file path): [0/1]
 arg token(-k, --token=<token>, process tokens): [3/32]
  token1, token2, token3

token 0: token1
token 1: token2
token 2: token3

```
