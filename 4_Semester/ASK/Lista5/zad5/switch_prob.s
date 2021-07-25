	.file	"switch_prob.c"
	.text
	.p2align 4
	.globl	switch_prob
	.type	switch_prob, @function
switch_prob:
.LFB0:
	.cfi_startproc
	endbr64
	cmpq	$64, %rsi
	je	.L2
	jg	.L3
	cmpq	$61, %rsi
	jle	.L14
	cmpq	$62, %rsi
	jne	.L6
	movq	%rdi, %rax
	salq	$4, %rax
	subq	%rdi, %rax
	movq	%rax, %rdi
	imulq	%rdi, %rdi
.L6:
	leaq	75(%rdi), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L3:
	cmpq	$65, %rsi
	jne	.L6
	imulq	%rdi, %rdi
	leaq	75(%rdi), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L14:
	leaq	0(,%rdi,8), %rax
	cmpq	$59, %rsi
	jle	.L6
	ret
	.p2align 4,,10
	.p2align 3
.L2:
	movq	%rdi, %rax
	sarq	$3, %rax
	ret
	.cfi_endproc
.LFE0:
	.size	switch_prob, .-switch_prob
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
