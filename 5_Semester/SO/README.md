projects in separate repos

## SO SHELL
fill-in-the-gaps project with most of additional code prewritten by the lecturer

## MALLOC
fast and not resource wasteful malloc algorithm written from scratch

- uses implicit list of free blocks divided into segments (each for a power of 2)
- each segment being a linked lists
- information is encoded in headers and footers of blocks (no mallocs used in writing this malloc!)
- performs careful padding for blocks
- finds first free block on appropiate segment for a given allocation
- might perform split on allocation and coalescence on freeing
- optimized reallocation
- invariant checker for debugging purposes to run and check for bugs inbetween allocations and deallocations


## EXT2 filesystem
simulated ext2 filesystem