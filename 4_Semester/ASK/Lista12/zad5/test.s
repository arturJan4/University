	.file	"test.c"
	.text
	.section	.rodata
.LC0:
	.string	"\n Inside func4() "
	.text
	.globl	func4
	.type	func4, @function
func4:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
1:	call	*mcount@GOTPCREL(%rip)
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	addl	$1, -4(%rbp)
.L2:
	cmpl	$65535, -4(%rbp)
	jle	.L3
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	func4, .-func4
	.section	.rodata
.LC1:
	.string	"\n Inside func3() "
	.text
	.globl	func3
	.type	func3, @function
func3:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
1:	call	*mcount@GOTPCREL(%rip)
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
	movl	$0, -4(%rbp)
	jmp	.L5
.L6:
	addl	$1, -4(%rbp)
.L5:
	cmpl	$268435455, -4(%rbp)
	jle	.L6
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	func3, .-func3
	.section	.rodata
.LC2:
	.string	"\n Inside func2() "
	.text
	.globl	func2
	.type	func2, @function
func2:
.LFB2:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
1:	call	*mcount@GOTPCREL(%rip)
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	movq	$1, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L8
.L9:
	movq	-8(%rbp), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leaq	3(%rax), %rdx
	testq	%rax, %rax
	cmovs	%rdx, %rax
	sarq	$2, %rax
	movq	%rax, -8(%rbp)
	addl	$1, -12(%rbp)
.L8:
	cmpl	$1048575, -12(%rbp)
	jle	.L9
	call	func3
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	func2, .-func2
	.section	.rodata
.LC3:
	.string	"\n Inside func1() "
	.text
	.globl	func1
	.type	func1, @function
func1:
.LFB3:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
1:	call	*mcount@GOTPCREL(%rip)
	leaq	.LC3(%rip), %rdi
	call	puts@PLT
	movl	$0, -4(%rbp)
	jmp	.L11
.L12:
	addl	$1, -4(%rbp)
.L11:
	cmpl	$16777215, -4(%rbp)
	jle	.L12
	call	func2
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	func1, .-func1
	.section	.rodata
.LC4:
	.string	"\n main() starts..."
.LC5:
	.string	"\n main() ends..."
	.text
	.globl	main
	.type	main, @function
main:
.LFB4:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
1:	call	*mcount@GOTPCREL(%rip)
	leaq	.LC4(%rip), %rdi
	call	puts@PLT
	movl	$0, -4(%rbp)
	jmp	.L14
.L15:
	addl	$1, -4(%rbp)
.L14:
	cmpl	$1048575, -4(%rbp)
	jle	.L15
	call	func1
	call	func4
	call	func3
	call	func2
	leaq	.LC5(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
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
