	.file	"puzzle.c"
	.text
	.p2align 4
	.globl	puzzle5
	.type	puzzle5, @function
puzzle5:
.LFB0:
	.cfi_startproc
	endbr64
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	leaq	8(%rsp), %rdi
	call	readlong@PLT
	leaq	16(%rsp), %rdi
	call	readlong@PLT
	movq	8(%rsp), %rax
	cqto
	idivq	16(%rsp)
	testq	%rdx, %rdx
	sete	%al
	movq	24(%rsp), %rcx
	xorq	%fs:40, %rcx
	jne	.L5
	movzbl	%al, %eax
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L5:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE0:
	.size	puzzle5, .-puzzle5
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
