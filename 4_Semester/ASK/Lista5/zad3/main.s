	.file	"main.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"puzzle(%u,%u) == %u\n"
	.section	.text.startup,"ax",@progbits
	.globl	main
	.type	main, @function
main:
.LFB13:
	.cfi_startproc
	endbr64
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$4, %esi
	movl	$5, %edi
	call	puzzle3@PLT
	movl	$4, %ecx
	movl	$5, %edx
	leaq	.LC0(%rip), %rsi
	movl	%eax, %r8d
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movl	$4, %esi
	movl	$6, %edi
	call	puzzle3@PLT
	movl	$4, %ecx
	movl	$6, %edx
	leaq	.LC0(%rip), %rsi
	movl	%eax, %r8d
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movl	$4, %esi
	movl	$7, %edi
	call	puzzle3@PLT
	movl	$4, %ecx
	movl	$7, %edx
	leaq	.LC0(%rip), %rsi
	movl	%eax, %r8d
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movl	$4, %esi
	movl	$8, %edi
	call	puzzle3@PLT
	movl	$4, %ecx
	movl	$8, %edx
	leaq	.LC0(%rip), %rsi
	movl	%eax, %r8d
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movl	$5, %esi
	movl	$32, %edi
	call	puzzle3@PLT
	movl	$32, %edx
	movl	$5, %ecx
	leaq	.LC0(%rip), %rsi
	movl	%eax, %r8d
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	xorl	%eax, %eax
	popq	%rdx
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
