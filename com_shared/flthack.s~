	.globl	i
	.data
	.align 4
	.type	i, @object
	.size	i, 4
i:
	.long	3
	.globl	x
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	1078530000
	.globl	xx
	.align 8
	.type	xx, @object
	.size	xx, 8
xx:
	.long	4028335726
	.long	1074340345
	.section	.rodata
.LC2:
	.string	"i=%i, x=%f, xx=%lf\n"
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
	subq	$16, %rsp
	movl	i(%rip), %eax
	addl	$8, %eax
	movl	%eax, i(%rip)

	movss	x(%rip), %xmm1
	movss	.LC0(%rip), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, x(%rip)

	movsd	xx(%rip), %xmm1
	movsd	.LC1(%rip), %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, xx(%rip)
	
	movq	xx(%rip), %rax
	movss	x(%rip), %xmm0
	unpcklps	%xmm0, %xmm0
	cvtps2pd	%xmm0, %xmm0
	movl	i(%rip), %edx
	movq	%rax, -8(%rbp)
	movsd	-8(%rbp), %xmm1
	movl	%edx, %esi
	movl	$.LC2, %edi
	movl	$2, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC0:
	.long	1090519040
	.align 8
.LC1:
	.long	0
	.long	1075838976
	.ident	"GCC: (GNU) 4.8.3 20140911 (Red Hat 4.8.3-7)"
	.section	.note.GNU-stack,"",@progbits
