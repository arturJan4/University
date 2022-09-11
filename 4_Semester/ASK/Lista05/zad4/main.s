	.file	"main.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"index of %ld: %d\n"
	.section	.rodata
	.align 32
.LC0:
	.quad	1
	.quad	3
	.quad	4
	.quad	6
	.quad	9
	.quad	12
	.quad	14
	.quad	15
	.quad	16
	.quad	20
	.section	.text.startup,"ax",@progbits
	.globl	main
	.type	main, @function
main:
.LFB13:
	.cfi_startproc
	endbr64
	subq	$104, %rsp
	.cfi_def_cfa_offset 112
	xorl	%edx, %edx
	movl	$20, %ecx
	movq	%fs:40, %rax
	movq	%rax, 88(%rsp)
	xorl	%eax, %eax
	leaq	8(%rsp), %rdi
	leaq	.LC0(%rip), %rsi
	rep movsl
	leaq	8(%rsp), %rdi
	movl	$9, %ecx
	movl	$15, %esi
	call	puzzle4@PLT
	movl	$15, %edx
	movl	$1, %edi
	leaq	.LC1(%rip), %rsi
	movl	%eax, %ecx
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movq	88(%rsp), %rax
	xorq	%fs:40, %rax
	je	.L2
	call	__stack_chk_fail@PLT
.L2:
	xorl	%eax, %eax
	addq	$104, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE13:
	.size	main, .-main
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
