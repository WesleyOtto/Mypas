SUB
	movl	i(%rip), %eax
	subl	$8, %eax
	movl	%eax, i(%rip)

	movss	x(%rip), %xmm0
	movss	.LC0(%rip), %xmm1
	subss	%xmm1, %xmm0
	movss	%xmm0, x(%rip)

	movsd	xx(%rip), %xmm0
	movsd	.LC1(%rip), %xmm1
	subsd	%xmm1, %xmm0
	movsd	%xmm0, xx(%rip)

MUL

	movl	i(%rip), %eax
	sall	$3, %eax
	movl	%eax, i(%rip)

	movss	x(%rip), %xmm1
	movss	.LC0(%rip), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, x(%rip)

	movsd	xx(%rip), %xmm1
	movsd	.LC1(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, xx(%rip)

DIV

	movl	i(%rip), %eax
	leal	7(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$3, %eax
	movl	%eax, i(%rip)

	movss	x(%rip), %xmm0
	movss	.LC0(%rip), %xmm1
	divss	%xmm1, %xmm0
	movss	%xmm0, x(%rip)

	movsd	xx(%rip), %xmm0
	movsd	.LC1(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, xx(%rip)

NEG

	movl	i(%rip), %eax
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, i(%rip)

	movss	x(%rip), %xmm0
	xorps	%xmm1, %xmm1
	ucomiss	%xmm1, %xmm0
	jp	.L2
	xorps	%xmm1, %xmm1
	ucomiss	%xmm1, %xmm0
	jne	.L2
	movl	.LC1(%rip), %eax
	jmp	.L4
.L2:
	movl	.LC0(%rip), %eax
.L4:
	movl	%eax, x(%rip)

	movsd	xx(%rip), %xmm0
	xorpd	%xmm1, %xmm1
	ucomisd	%xmm1, %xmm0
	jp	.L5
	xorpd	%xmm1, %xmm1
	ucomisd	%xmm1, %xmm0
	jne	.L5
	movabsq	$4607182418800017408, %rax
	jmp	.L7
.L5:
	movl	$0, %eax
.L7:
	movq	%rax, xx(%rip)


