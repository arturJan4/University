	.file	"puzzle.c"
	.text
	.globl	proc
	.type	proc, @function
proc:
.LFB0:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rax), %rdx
	movq	(%rdx), %rdx
	subq	8(%rax), %rdx
	movq	%rdx, (%rdi)
	ret
	.cfi_endproc
.LFE0:
	.size	proc, .-proc
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
