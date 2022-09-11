	.file	"puzzle.c"
	.text
	.globl	aframe
	.type	aframe, @function
aframe:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	0(,%rdi,8), %r9
	leaq	23(%r9), %rax
	movq	%rax, %rcx
	andq	$-16, %rcx
	andq	$-4096, %rax
	movq	%rsp, %r10
	subq	%rax, %r10
	movq	%r10, %rax
.L2:
	cmpq	%rax, %rsp
	je	.L3
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	jmp	.L2
.L3:
	movq	%rcx, %rax
	andl	$4095, %eax
	subq	%rax, %rsp
	testq	%rax, %rax
	je	.L4
	orq	$0, -8(%rsp,%rax)
.L4:
	leaq	15(%rsp), %r8
	andq	$-16, %r8
	movq	%r8, %rcx
	leaq	-8(%rbp), %rax
	movq	%rax, -8(%r8,%r9)
	movq	$0, -8(%rbp)
.L5:
	movq	-8(%rbp), %rax
	cmpq	%rdi, %rax
	jge	.L8
	movq	%rdx, (%rcx,%rax,8)
	addq	$1, -8(%rbp)
	jmp	.L5
.L8:
	movq	(%r8,%rsi,8), %rax
	movq	(%rax), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	aframe, .-aframe
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
