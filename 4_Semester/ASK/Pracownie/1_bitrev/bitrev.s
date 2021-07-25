	.text
	.globl	bitrev
	.type	bitrev, @function

bitrev:	
		# TODO: można lepsze IPC wycisnąć z tego
		movl 	%edi, %eax
		rorw	$8, %ax		# endian switch
		rorl 	$16, %eax
		rorw	$8,	%ax
		shlq	$32, %rax

		shrq	$32, %rdi	# higher 32 bits
		rorw	$8, %di
		rorl 	$16, %edi
		rorw	$8,	%di
		orq     %rdi, %rax
		movq	%rax, %rdi
		
		movq	$0xF0F0F0F0F0F0F0F0, %rdx # rdx - mask
		andq 	%rdx, %rdi
		shrq	$4, %rdi		# (x & mask) >> 4			
		shlq    $4, %rax		# (x << 4) & mask == (x & ~mask) << 4
		andq    %rdx, %rax
		orq     %rax, %rdi
		movq	%rdi,%rax		
		
		movq	$0xCCCCCCCCCCCCCCCC, %rdx # rdx - mask
		andq 	%rdx, %rdi
		shrq	$2, %rdi
		shlq    $2, %rax
		andq    %rdx, %rax
		orq     %rax, %rdi
		movq	%rdi,%rax 
		
		movq	$0xAAAAAAAAAAAAAAAA, %rdx # rdx - mask
		andq 	%rdx, %rdi
		shrq	%rdi
		shlq    %rax
		andq    %rdx, %rax
		orq     %rdi, %rax
	ret

	.size	bitrev, .-bitrev
