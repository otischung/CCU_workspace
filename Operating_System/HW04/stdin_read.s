	.file	"stdin_read.c"
	.text
	.section	.rodata
.LC0:
	.string	"\344\275\240\350\274\270\345\205\245\347\232\204\345\255\227\345\205\203\346\230\257 '%c'\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-17(%rbp), %rax
	movq	%rax, -16(%rbp)
#APP
# 8 "stdin_read.c" 1
	mov $0, %rax
	mov $0, %rdi
	mov -16(%rbp), %rsi
	mov $1, %rdx
	syscall

# 0 "" 2
#NO_APP
	movzbl	-17(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 11.1.0"
	.section	.note.GNU-stack,"",@progbits
