	.file	"puzzle2.c"
	.text
	.p2align 4
	.globl	puzzle2
	.type	puzzle2, @function
puzzle2:
.LFB0:
	.cfi_startproc
	endbr64
	movq	%rdi, %rax
.L4:
	movq	%rsi, %rdx
	jmp	.L3
	.p2align 4,,10
	.p2align 3
.L2:
	cmpb	%cl, (%rax)
	je	.L8
.L3:
	movzbl	(%rdx), %ecx
	addq	$1, %rdx
	testb	%cl, %cl
	jne	.L2
	subq	%rdi, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L8:
	addq	$1, %rax
	jmp	.L4
	.cfi_endproc
.LFE0:
	.size	puzzle2, .-puzzle2
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
