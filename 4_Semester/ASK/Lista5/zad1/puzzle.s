	.file	"puzzle.c"
	.text
	.p2align 4
	.globl	puzzle
	.type	puzzle, @function
puzzle:
.LFB0:
	.cfi_startproc
	endbr64
	testl	%esi, %esi
	je	.L4
	xorl	%eax, %eax
	xorl	%r8d, %r8d
	.p2align 4,,10
	.p2align 3
.L3:
	movl	%edi, %edx
	addl	$1, %eax
	sarq	%rdi
	andl	$1, %edx
	addl	%edx, %r8d
	cmpl	%esi, %eax
	jne	.L3
	movl	%r8d, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	xorl	%r8d, %r8d
	movl	%r8d, %eax
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
