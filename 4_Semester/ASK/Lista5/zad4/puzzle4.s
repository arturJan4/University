	.file	"puzzle4.c"
	.text
	.globl	puzzle4
	.type	puzzle4, @function
puzzle4:
.LFB0:
	.cfi_startproc
	endbr64
.L2:
	movq	%rcx, %rax
	subq	%rdx, %rax
	shrq	%rax
	addq	%rdx, %rax
	cmpq	%rdx, %rcx
	jb	.L7
	cmpq	%rsi, (%rdi,%rax,8)
	je	.L1
	jle	.L5
	leaq	-1(%rax), %rcx
	jmp	.L2
.L5:
	leaq	1(%rax), %rdx
	jmp	.L2
.L7:
	orl	$-1, %eax
.L1:
	ret
	.cfi_endproc
.LFE0:
	.size	puzzle4, .-puzzle4
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
