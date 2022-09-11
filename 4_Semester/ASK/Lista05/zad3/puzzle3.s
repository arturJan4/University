	.file	"puzzle3.c"
	.text
	.globl	puzzle3
	.type	puzzle3, @function
puzzle3:
.LFB0:
	.cfi_startproc
	endbr64
	movl	%edi, %edi
	salq	$32, %rsi
	movl	$32, %edx
	movl	$-2147483648, %ecx
	xorl	%eax, %eax
.L3:
	addq	%rdi, %rdi
	movq	%rdi, %r8
	subq	%rsi, %r8
	js	.L2
	orl	%ecx, %eax
	movq	%r8, %rdi
.L2:
	shrl	%ecx
	decl	%edx
	jne	.L3
	ret
	.cfi_endproc
.LFE0:
	.size	puzzle3, .-puzzle3
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
