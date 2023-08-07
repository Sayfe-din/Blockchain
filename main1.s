	.file	"main1.c"
	.text
	.section	.rodata
.LC0:
	.string	" V e c t o r : [ "
.LC1:
	.string	"%lx  "
.LC2:
	.string	"] "
	.text
	.globl	print_long_vector
	.type	print_long_vector, @function
print_long_vector:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -4(%rbp)
.L2:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L3
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	print_long_vector, .-print_long_vector
	.section	.rodata
.LC3:
	.string	"cle publique = (%lx , %lx ) \n"
.LC4:
	.string	"cle privee = (%lx , %lx ) \n"
.LC5:
	.string	"Initial Message : %s \n"
.LC6:
	.string	"Encoded representation: "
.LC7:
	.string	"Decoded : %s \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movl	$0, %edi
	call	time@PLT
	movl	%eax, %edi
	call	srand@PLT
	movl	$5000, %edx
	movl	$7, %esi
	movl	$3, %edi
	call	random_prime_number@PLT
	movq	%rax, -16(%rbp)
	movl	$5000, %edx
	movl	$7, %esi
	movl	$3, %edi
	call	random_prime_number@PLT
	movq	%rax, -8(%rbp)
	jmp	.L5
.L6:
	movl	$5000, %edx
	movl	$7, %esi
	movl	$3, %edi
	call	random_prime_number@PLT
	movq	%rax, -8(%rbp)
.L5:
	movq	-16(%rbp), %rax
	cmpq	-8(%rbp), %rax
	je	.L6
	leaq	-72(%rbp), %rdi
	leaq	-64(%rbp), %rcx
	leaq	-56(%rbp), %rdx
	movq	-8(%rbp), %rsi
	movq	-16(%rbp), %rax
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	generate_key_values@PLT
	movq	-72(%rbp), %rax
	testq	%rax, %rax
	jns	.L7
	movq	-16(%rbp), %rax
	leaq	-1(%rax), %rdx
	movq	-8(%rbp), %rax
	subq	$1, %rax
	imulq	%rdx, %rax
	movq	%rax, -24(%rbp)
	movq	-72(%rbp), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -72(%rbp)
.L7:
	movq	-56(%rbp), %rdx
	movq	-64(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-56(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movabsq	$478560413000, %rax
	movq	%rax, -82(%rbp)
	movw	$0, -74(%rbp)
	leaq	-82(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movl	%eax, -28(%rbp)
	movq	-56(%rbp), %rdx
	movq	-64(%rbp), %rcx
	leaq	-82(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	encrypt@PLT
	movq	%rax, -40(%rbp)
	leaq	-82(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC5(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC6(%rip), %rdi
	call	puts@PLT
	movl	-28(%rbp), %edx
	movq	-40(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	print_long_vector
	movq	-56(%rbp), %rcx
	movq	-72(%rbp), %rdx
	movl	-28(%rbp), %esi
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	decrypt@PLT
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC7(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Debian 10.2.1-6) 10.2.1 20210110"
	.section	.note.GNU-stack,"",@progbits
