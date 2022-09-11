	.file	"puzzle.c"
	.text
	.globl	eval
	.type	eval, @function
eval:
.LFB0:
	.cfi_startproc
	endbr64
	movq	24(%rsp), %rcx
	movq	8(%rsp), %rdx
	movq	%rdi, %rax
	movq	(%rcx), %rcx
	movq	%rdx, %rdi
	movq	%rdx, %rsi
	subq	16(%rsp), %rsi
	movq	%rsi, 16(%rax)
	imulq	%rcx, %rdi
	subq	%rcx, %rdx
	movq	%rdx, 8(%rax)
	movq	%rdi, (%rax)
	ret
	.cfi_endproc
.LFE0:
	.size	eval, .-eval
	.globl	wrap
	.type	wrap, @function
wrap:
.LFB1:
	.cfi_startproc
	endbr64
	subq	$88, %rsp
	.cfi_def_cfa_offset 96
	movq	%rdi, %r8
	movq	%rdx, 8(%rsp)
	leaq	48(%rsp), %rdi
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	leaq	8(%rsp), %rax
	movq	%rsi, 24(%rsp)
	movq	%rax, 32(%rsp)
	pushq	32(%rsp)
	.cfi_def_cfa_offset 104
	pushq	32(%rsp)
	.cfi_def_cfa_offset 112
	pushq	%r8
	.cfi_def_cfa_offset 120
	call	eval
	movq	72(%rsp), %rax
	addq	80(%rsp), %rax
	imulq	88(%rsp), %rax
	addq	$24, %rsp
	.cfi_def_cfa_offset 96
	movq	72(%rsp), %rcx
	xorq	%fs:40, %rcx
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	addq	$88, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1:
	.size	wrap, .-wrap
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
