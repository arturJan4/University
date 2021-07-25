	.file	"fun.c"
	.text
	.globl	_fun
	.def	_fun;	.scl	2;	.type	32;	.endef
_fun:
	movl	8(%esp), %ecx
	movl	4(%esp), %eax
	rorl	%cl, %eax
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
