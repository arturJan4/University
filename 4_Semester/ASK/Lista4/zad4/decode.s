	.file	"decode.c"
	.section	.text.unlikely,"x"
LCOLDB0:
	.text
LHOTB0:
	.p2align 4,,15
	.globl	_decode
	.def	_decode;	.scl	2;	.type	32;	.endef
_decode:
	movl	4(%esp), %eax
	addl	12(%esp), %eax
	movl	8(%esp), %edx
	adcl	16(%esp), %edx
	movl	8(%esp), %ecx
	movl	16(%esp), %eax
	xorl	%edx, %ecx
	xorl	%edx, %eax
	andl	%eax, %ecx
	movl	%ecx, %edx
	sarl	$31, %edx
	movl	%edx, %eax
	ret
	.section	.text.unlikely,"x"
LCOLDE0:
	.text
LHOTE0:
	.ident	"GCC: (tdm-1) 5.1.0"
