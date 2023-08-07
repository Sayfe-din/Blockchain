	.file	"exo2.c"
	.text
	.globl	extended_gcd
	.type	extended_gcd, @function
extended_gcd:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%rcx, -64(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L2
	movq	-56(%rbp), %rax
	movq	$0, (%rax)
	movq	-64(%rbp), %rax
	movq	$1, (%rax)
	movq	-48(%rbp), %rax
	jmp	.L4
.L2:
	movq	-48(%rbp), %rax
	cqto
	idivq	-40(%rbp)
	movq	%rdx, %rdi
	leaq	-24(%rbp), %rcx
	leaq	-16(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rax, %rsi
	call	extended_gcd
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rcx
	movq	-48(%rbp), %rax
	cqto
	idivq	-40(%rbp)
	movq	%rax, %rdx
	movq	-16(%rbp), %rax
	imulq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	extended_gcd, .-extended_gcd
	.globl	generate_key_values
	.type	generate_key_values, @function
generate_key_values:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%rcx, -64(%rbp)
	movq	%r8, -72(%rbp)
	movq	-40(%rbp), %rax
	imulq	-48(%rbp), %rax
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-40(%rbp), %rax
	leaq	-1(%rax), %rdx
	movq	-48(%rbp), %rax
	subq	$1, %rax
	imulq	%rdx, %rax
	movq	%rax, -24(%rbp)
	movq	$0, -16(%rbp)
	jmp	.L6
.L7:
	call	rand@PLT
	cltq
	cqto
	idivq	-24(%rbp)
	movq	%rdx, -8(%rbp)
	leaq	-32(%rbp), %rcx
	movq	-72(%rbp), %rdx
	movq	-24(%rbp), %rsi
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	extended_gcd
	movq	%rax, -16(%rbp)
.L6:
	cmpq	$1, -16(%rbp)
	jne	.L7
	movq	-64(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	generate_key_values, .-generate_key_values
	.section	.rodata
.LC0:
	.string	"exo2.c"
.LC1:
	.string	"tab"
	.text
	.globl	encrypt
	.type	encrypt, @function
encrypt:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	salq	$3, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L9
	leaq	__PRETTY_FUNCTION__.1(%rip), %rcx
	movl	$53, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	call	__assert_fail@PLT
.L9:
	movl	$0, -4(%rbp)
	jmp	.L10
.L11:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	modpow@PLT
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,8), %rcx
	movq	-16(%rbp), %rdx
	addq	%rcx, %rdx
	cltq
	movq	%rax, (%rdx)
	addl	$1, -4(%rbp)
.L10:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L11
	movq	-16(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	encrypt, .-encrypt
	.section	.rodata
.LC2:
	.string	"chaine"
	.text
	.globl	decrypt
	.type	decrypt, @function
decrypt:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movl	-28(%rbp), %eax
	addl	$1, %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L14
	leaq	__PRETTY_FUNCTION__.0(%rip), %rcx
	movl	$67, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC2(%rip), %rdi
	call	__assert_fail@PLT
.L14:
	movl	$0, -4(%rbp)
	jmp	.L15
.L16:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	modpow@PLT
	movl	%eax, %edx
	movl	-4(%rbp), %eax
	movslq	%eax, %rcx
	movq	-16(%rbp), %rax
	addq	%rcx, %rax
	movb	%dl, (%rax)
	addl	$1, -4(%rbp)
.L15:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L16
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	-16(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	decrypt, .-decrypt
	.section	.rodata
	.align 8
	.type	__PRETTY_FUNCTION__.1, @object
	.size	__PRETTY_FUNCTION__.1, 8
__PRETTY_FUNCTION__.1:
	.string	"encrypt"
	.align 8
	.type	__PRETTY_FUNCTION__.0, @object
	.size	__PRETTY_FUNCTION__.0, 8
__PRETTY_FUNCTION__.0:
	.string	"decrypt"
	.ident	"GCC: (Debian 10.2.1-6) 10.2.1 20210110"
	.section	.note.GNU-stack,"",@progbits
