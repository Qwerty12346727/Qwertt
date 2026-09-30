# Commands

> 2026 code open source. DONT MODIFY IF NOT ORIGINAL CREATOR.

## File Commands

### `createFile <filename> <contents>`
Creates a file and writes the specified contents into it.

Example:
`createFile hello.txt Hello world!`

### `cat <filename/filepath>`
Prints the contents of a text file.

Example:
`cat hello.txt`

### `listFileHex <filename/filepath>`
Displays the contents of a file as hexadecimal character values.

Example:
`listFileHex hello.txt`

Example output:
`48 65 6c 6c 6f`

### `cp <source> <destination>`
Copies a file or directory.

Alias:
`copy`

Example:
`cp hello.txt backup.txt`

### `rn <source> <destination>`
Renames or moves a file or directory.

Alias:
`rename`

Example:
`rn hello.txt hello2.txt`

### `rm <path>`
Removes a file or directory.

Alias:
`remove`

Example:
`rm hello.txt`

---

## Directory Commands

### `ls [path]`
Lists the contents of a directory.

Alias:
`list`

Examples:
`ls`
`ls /storage/emulated/0`

### `ls [path] --sub`
Recursively lists the contents of a directory and its subdirectories.

Alias:
`list`

Examples:
`ls --sub`
`ls /storage/emulated/0 --sub`

### `cd <path>`
Changes the current working directory.

Alias:
`changeDirectory`

Examples:
`cd /storage/emulated/0`
`cd MyFolder`

### `mkdir <directory>`
Creates a new directory.

Alias:
`makeDirectory`

Example:
`mkdir MyFolder`

### `home`
Returns to the directory where me.shell originally started.

Example:
`home`

---

## Search Commands

### `find <name> [path]`
Recursively searches for a file or directory by name.

Examples:
`find hello.txt`
`find hello.txt /storage/emulated/0`

### `find <name> [path] --goTo`
Recursively searches for an item and changes the current directory to the item's parent directory when found.

Example:
`find hello.txt /storage/emulated/0 --goTo`

---

## Memory / Data Commands

### `readRam <bytes>`
Allocates the specified number of bytes and displays their memory addresses and hexadecimal values.

Example:
`readRam 32`

### `strToInt <text>`
Converts each character into its numeric character code.

Example:
`strToInt ABC`

Output:
`65 66 67`

---

## Shell Commands

### `exit`
Exits me.shell.

Example:
`exit`

---

# Complete Command List

| Command | Alias | Arguments | Description |
|---|---|---|---|
| `exit` | — | None | Exit the shell |
| `strToInt` | — | `<text>` | Convert characters to numeric character codes |
| `createFile` | — | `<filename> <contents>` | Create and write a file |
| `readRam` | — | `<bytes>` | Allocate and inspect RAM |
| `ls` | `list` | `[path]` | List directory contents |
| `ls --sub` | `list` | `[path] --sub` | Recursively list directory contents |
| `cd` | `changeDirectory` | `<path>` | Change the current directory |
| `mkdir` | `makeDirectory` | `<directory>` | Create a directory |
| `rm` | `remove` | `<path>` | Delete a file or directory |
| `rn` | `rename` | `<source> <destination>` | Rename or move an item |
| `cp` | `copy` | `<source> <destination>` | Copy an item |
| `cat` | — | `<filename/filepath>` | Print file contents |
| `listFileHex` | — | `<filename/filepath>` | Display file data as hexadecimal |
| `find` | — | `<name> [path]` | Recursively search for an item |
| `find --goTo` | — | `<name> [path] --goTo` | Find an item and enter its parent directory |
| `home` | — | None | Return to the original starting directory |
