projects in separate repos

## [SO SHELL](https://github.com/arturJan4/shell)
fill-in-the-gaps project with most of additional code prewritten by the lecturer  


## [MALLOC](https://github.com/arturJan4/malloc)
fast and not resource wasteful malloc algorithm written from scratch

- uses implicit list of free blocks divided into segments (each for a power of 2)
- each segment being a linked lists
- information is encoded in headers and footers of blocks (no mallocs used in writing this malloc!)
- performs careful padding for blocks
- finds first free block on appropiate segment for a given allocation
- might perform split on allocation and coalescence on freeing
- optimized reallocation
- invariant checker for debugging purposes to run and check for bugs inbetween allocations and deallocations

## [EXT2 filesystem](https://github.com/arturJan4/ext2)
simulated ext2 filesystem
