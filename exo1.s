	.file	"exo1.c"
	.text
	.globl	is_prime_naive
	.type	is_prime_naive, @function
is_prime_naive:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$3, -4(%rbp)
	jmp	.L2
.L5:
	movl	-4(%rbp), %eax
	movslq	%eax, %rcx
	movq	-24(%rbp), %rax
	cqto
	idivq	%rcx
	movq	%rdx, %rax
	testq	%rax, %rax
	jne	.L3
	movl	$0, %eax
	jmp	.L4
.L3:
	addl	$1, -4(%rbp)
.L2:
	movl	-4(%rbp), %eax
	cltq
	cmpq	%rax, -24(%rbp)
	jg	.L5
	movl	$1, %eax
.L4:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	is_prime_naive, .-is_prime_naive
	.globl	modpow_naive
	.type	modpow_naive, @function
modpow_naive:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	$1, -8(%rbp)
	movl	$1, -12(%rbp)
	jmp	.L7
.L8:
	movq	-24(%rbp), %rax
	imulq	-8(%rbp), %rax
	cqto
	idivq	-40(%rbp)
	movq	%rdx, -8(%rbp)
	addl	$1, -12(%rbp)
.L7:
	movl	-12(%rbp), %eax
	cltq
	cmpq	%rax, -32(%rbp)
	jge	.L8
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	modpow_naive, .-modpow_naive
	.globl	modpow
	.type	modpow, @function
modpow:
.LFB8:
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
	cmpq	$0, -48(%rbp)
	jne	.L11
	movl	$1, %eax
	jmp	.L12
.L11:
	movq	-48(%rbp), %rax
	andl	$1, %eax
	testq	%rax, %rax
	jne	.L13
	movq	-48(%rbp), %rax
	movq	%rax, %rdx
	shrq	$63, %rdx
	addq	%rdx, %rax
	sarq	%rax
	movq	%rax, %rcx
	movq	-56(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	modpow
	cltq
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	imulq	%rax, %rax
	cqto
	idivq	-56(%rbp)
	movq	%rdx, %rax
	jmp	.L12
.L13:
	movq	-48(%rbp), %rax
	movq	%rax, %rdx
	shrq	$63, %rdx
	addq	%rdx, %rax
	sarq	%rax
	movq	%rax, -8(%rbp)
	movq	-56(%rbp), %rdx
	movq	-8(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	modpow
	cltq
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	imulq	%rax, %rax
	cqto
	idivq	-56(%rbp)
	movq	%rdx, %rax
	imulq	-40(%rbp), %rax
	cqto
	idivq	-56(%rbp)
	movq	%rdx, %rax
.L12:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	modpow, .-modpow
	.globl	witness
	.type	witness, @function
witness:
.LFB9:
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
	movq	%rcx, -48(%rbp)
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	modpow
	cltq
	movq	%rax, -8(%rbp)
	cmpq	$1, -8(%rbp)
	jne	.L15
	movl	$0, %eax
	jmp	.L16
.L15:
	movq	$0, -16(%rbp)
	jmp	.L17
.L19:
	movq	-48(%rbp), %rax
	subq	$1, %rax
	cmpq	%rax, -8(%rbp)
	jne	.L18
	movl	$0, %eax
	jmp	.L16
.L18:
	movq	-48(%rbp), %rdx
	movq	-8(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	modpow
	cltq
	movq	%rax, -8(%rbp)
	addq	$1, -16(%rbp)
.L17:
	movq	-16(%rbp), %rax
	cmpq	-32(%rbp), %rax
	jl	.L19
	movl	$1, %eax
.L16:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	witness, .-witness
	.globl	rand_long
	.type	rand_long, @function
rand_long:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	call	rand@PLT
	cltq
	movq	-16(%rbp), %rdx
	subq	-8(%rbp), %rdx
	leaq	1(%rdx), %rcx
	cqto
	idivq	%rcx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	rand_long, .-rand_long
	.globl	is_prime_miller
	.type	is_prime_miller, @function
is_prime_miller:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	cmpq	$2, -40(%rbp)
	jne	.L23
	movl	$1, %eax
	jmp	.L24
.L23:
	movq	-40(%rbp), %rax
	andl	$1, %eax
	testq	%rax, %rax
	je	.L25
	cmpq	$1, -40(%rbp)
	jg	.L26
.L25:
	movl	$0, %eax
	jmp	.L24
.L26:
	movq	$0, -8(%rbp)
	movq	-40(%rbp), %rax
	subq	$1, %rax
	movq	%rax, -16(%rbp)
	jmp	.L27
.L28:
	movq	-16(%rbp), %rax
	movq	%rax, %rdx
	shrq	$63, %rdx
	addq	%rdx, %rax
	sarq	%rax
	movq	%rax, -16(%rbp)
	addq	$1, -8(%rbp)
.L27:
	movq	-16(%rbp), %rax
	andl	$1, %eax
	testq	%rax, %rax
	je	.L28
	movl	$0, -20(%rbp)
	jmp	.L29
.L31:
	movq	-40(%rbp), %rax
	subq	$1, %rax
	movq	%rax, %rsi
	movl	$2, %edi
	call	rand_long
	movq	%rax, -32(%rbp)
	movq	-40(%rbp), %rcx
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rsi
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	witness
	testl	%eax, %eax
	je	.L30
	movl	$0, %eax
	jmp	.L24
.L30:
	addl	$1, -20(%rbp)
.L29:
	movl	-20(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jl	.L31
	movl	$1, %eax
.L24:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	is_prime_miller, .-is_prime_miller
	.globl	random_prime_number
	.type	random_prime_number, @function
random_prime_number:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movl	%esi, -40(%rbp)
	movl	%edx, -44(%rbp)
	movq	$2, -8(%rbp)
	movq	$2, -16(%rbp)
	movl	$1, -20(%rbp)
	jmp	.L33
.L34:
	salq	-8(%rbp)
	addl	$1, -20(%rbp)
.L33:
	movl	-36(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jg	.L34
	movl	$1, -24(%rbp)
	jmp	.L35
.L36:
	salq	-16(%rbp)
	addl	$1, -24(%rbp)
.L35:
	movl	-24(%rbp), %eax
	cmpl	-40(%rbp), %eax
	jle	.L36
	subq	$1, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	rand_long
	movq	%rax, -32(%rbp)
	jmp	.L37
.L38:
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	rand_long
	movq	%rax, -32(%rbp)
.L37:
	movl	-44(%rbp), %edx
	movq	-32(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	is_prime_miller
	cmpl	$1, %eax
	jne	.L38
	movq	-32(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	random_prime_number, .-random_prime_number
	.ident	"GCC: (Debian 10.2.1-6) 10.2.1 20210110"
	.section	.note.GNU-stack,"",@progbits
