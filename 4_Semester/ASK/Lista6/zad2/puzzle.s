	.file	"puzzle.c"
	.text
	.p2align 4
	.globl	puzzle
	.type	puzzle, @function
puzzle:
.LFB0:
	.cfi_startproc
	endbr64
	movq	%rdi, %r11
	movq	%rdx, %rdi
	testq	%rdx, %rdx
	jle	.L4
	movabsq	$9223372036854775807, %r9
	leaq	(%rsi,%rdx,8), %r10
	xorl	%eax, %eax
	movabsq	$-9223372036854775808, %r8
	.p2align 4,,10
	.p2align 3
.L3:
	movq	(%rsi), %rcx
	cmpq	%rcx, %r9
	cmovg	%rcx, %r9
	cmpq	%rcx, %r8
	cmovl	%rcx, %r8
	addq	$8, %rsi
	addq	%rcx, %rax
	cmpq	%r10, %rsi
	jne	.L3
	cqto
	movq	%r9, (%r11)
	idivq	%rdi
	movq	%r8, 8(%r11)
	movq	%rax, 16(%r11)
	movq	%r11, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	movabsq	$9223372036854775807, %r9
	xorl	%eax, %eax
	movabsq	$-9223372036854775808, %r8
	movq	%rax, 16(%r11)
	movq	%r11, %rax
	movq	%r9, (%r11)
	movq	%r8, 8(%r11)
	ret
	.cfi_endproc
.LFE0:
	.size	puzzle, .-puzzle
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
