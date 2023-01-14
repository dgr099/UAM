	.file	"simple2.c"
	.text
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB39:
	.cfi_startproc
	endbr64
#APP
# 19 "simple2.c" 1
	#populate
# 0 "" 2
#NO_APP
	xorl	%eax, %eax
	leaq	b(%rip), %rcx
	leaq	a(%rip), %rdx
.L2:
	pxor	%xmm0, %xmm0
	leal	1(%rax), %esi
	cvtsi2sdl	%eax, %xmm0
	movsd	%xmm0, (%rcx,%rax,8)
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%esi, %xmm0
	movsd	%xmm0, (%rdx,%rax,8)
	addq	$1, %rax
	cmpq	$2048, %rax
	jne	.L2
#APP
# 26 "simple2.c" 1
	#operation
# 0 "" 2
#NO_APP
	movsd	c(%rip), %xmm1
	movsd	.LC0(%rip), %xmm2
	movl	$1000000, %esi
.L3:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L4:
	movsd	(%rdx,%rax), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	(%rcx,%rax), %xmm0
	addq	$8, %rax
	addsd	%xmm0, %xmm1
	cmpq	$16384, %rax
	jne	.L4
	subl	$1, %esi
	jne	.L3
	movsd	%xmm1, c(%rip)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.local	c
	.comm	c,8,8
	.local	b
	.comm	b,16384,32
	.local	a
	.comm	a,16384,32
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	-611603343
	.long	1072693352
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
