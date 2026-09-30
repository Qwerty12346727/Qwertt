
# COMMANDS

QWERTT is a C++ interactive command shell.

## BASIC

### `exit`
Exits QWERTT.

### `home`
Returns to the directory where QWERTT was originally started.

---

## TEXT

### `strToInt <text>`
Prints the integer character code of each character.

Example: `strToInt Hello`

---

## FILES

### `createFile <filename> <contents>`
Creates a file and writes the specified contents.

Example: `createFile hello.txt Hello world!`

### `cat <filename/filepath>`
Prints the contents of a file.

Example: `cat hello.txt`

### `fileHex <filename/filepath>`
Displays the file's characters as hexadecimal values.

Example: `fileHex hello.txt`

---

## MEMORY

### `readRam <bytes>`
Allocates the specified number of bytes and displays their memory addresses and hexadecimal values.

Example: `readRam 32`

---

## DIRECTORIES

### `ls [path]`
Lists the contents of a directory. Uses the current directory if no path is provided.

### `list [path]`
Alias for `ls`.

### `ls [path] --sub`
Recursively lists directory contents and subdirectories.

Examples:
- `ls --sub`
- `ls /storage/emulated/0 --sub`

### `cd <path>`
Changes the current working directory.

### `changeDirectory <path>`
Alias for `cd`.

### `mkdir <directory>`
Creates a directory.

### `makeDirectory <directory>`
Alias for `mkdir`.

---

## FILE MANAGEMENT

### `rm <path>`
Removes a file or directory. Directories are removed recursively.

### `remove <path>`
Alias for `rm`.

### `rn <source> <destination>`
Renames or moves a file or directory.

### `rename <source> <destination>`
Alias for `rn`.

### `cp <source> <destination>`
Copies a file or directory to the specified destination.

### `copy <source> <destination>`
Alias for `cp`.

### `cp <source>`
Copies the source to an automatically generated destination.

The destination starts with `copy_`. If it already exists, another `copy_` is added repeatedly.

Example sequence:
- `file.txt`
- `copy_file.txt`
- `copy_copy_file.txt`
- `copy_copy_copy_file.txt`

### `copy <source>`
Alias for `cp <source>`.

---

## SEARCH

### `find <name>`
Recursively searches for a matching filename from the current directory.

### `find <name> <path>`
Recursively searches from the specified path.

### `find <name> [path] --list`
Prints every item encountered during the recursive search.

Examples:
- `find Movie001.mp4 --list`
- `find Movie001.mp4 /storage/emulated/0 --list`

### `find <name> [path] --goTo`
Searches for the specified name and changes the current working directory to the parent directory of a match.

Examples:
- `find Movie001.mp4 --goTo`
- `find Movie001.mp4 /storage/emulated/0 --goTo`

---

## ALIASES

| Command | Alias |
|---|---|
| `ls` | `list` |
| `cd` | `changeDirectory` |
| `mkdir` | `makeDirectory` |
| `rm` | `remove` |
| `rn` | `rename` |
| `cp` | `copy` |

---

## ALL RECOGNIZED COMMAND NAMES

These are the 20 command names checked by `main()`:

- `exit`
- `strToInt`
- `createFile`
- `readRam`
- `ls`
- `list`
- `cd`
- `changeDirectory`
- `mkdir`
- `makeDirectory`
- `rm`
- `remove`
- `rn`
- `rename`
- `cp`
- `copy`
- `cat`
- `find`
- `home`
- `fileHex`

## RECOGNIZED FLAGS

- `ls`: `--sub`
- `find`: `--list`, `--goTo`
