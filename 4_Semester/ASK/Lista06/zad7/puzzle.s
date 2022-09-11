	.file	"puzzle.c"
	.text
	.globl	puzzle7
	.type	puzzle7, @function
puzzle7:
.LFB0:
	.cfi_startproc
	endbr64
	subq	$88, %rsp
	.cfi_def_cfa_offset 96
	movq	%rsi, 40(%rsp)
	movq	%rdx, 48(%rsp)
	movq	%rcx, 56(%rsp)
	movq	%r8, 64(%rsp)
	movq	%r9, 72(%rsp)
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	movl	$8, (%rsp)
	leaq	96(%rsp), %rax
	movq	%rax, 8(%rsp)
	leaq	32(%rsp), %rax
	movq	%rax, 16(%rsp)
	movl	$0, %edx
	jmp	.L2
.L3:
	movq	8(%rsp), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, 8(%rsp)
.L4:
	addq	(%rax), %rdx
	subq	$1, %rdi
.L2:
	testq	%rdi, %rdi
	jle	.L8
	cmpl	$47, (%rsp)
	ja	.L3
	movl	(%rsp), %eax
	addq	16(%rsp), %rax
	addl	$8, (%rsp)
	jmp	.L4
.L8:
	movq	24(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L9
	movq	%rdx, %rax
	addq	$88, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L9:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE0:
	.size	puzzle7, .-puzzle7
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
