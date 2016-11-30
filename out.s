	pushl %rax
	movl $2, %rax
	movl %rax, a
	pushl %eax
	movl b, %eax
	movl %rax, a
	pushl %eax
	movl a, %eax
	movl %rax, c
	pushl %rax
	movl $1, %rax
	movl %rax, c
	pushl %rax
	movl $1078774989, %rax
	movl %rax, c
	pushl %eax
	movl d, %eax
	movl %rax, c
	pushl %eax
	movl a, %eax
	movq %rax, e
	pushl %rax
	movl $1, %rax
	movq %rax, e
	pushl %rax
	movl $1078774989, %rax
	movq %rax, e
	pushl %eax
	movl d, %eax
	movq %rax, e
	pushl %eax
	movl f, %eax
	movq %rax, e
	pushl %eax
	movl y, %eax
	pushl %eax
	movl x, %eax
	jz .L1
	.L1:
	pushl %rax
	movl $3, %rax
	pushl %eax
	movl a, %eax
	jz .L2
	.L2:
	pushl %rax
	movl $1082549862, %rax
	pushl %eax
	movl c, %eax
	jz .L3
	.L3:
	pushl %eax
	movl x, %eax
	pushl %eax
	movl y, %eax
	jz .L4
	.L4:
	pushl %rax
	movl $2, %rax
	pushl %rax
	movl $4, %rax
	mull (%rsp)
	addl $4, %rsp
	pushl %eax
	movl b, %eax
	pushl %eax
	movl a, %eax
	divl (%rsp)
	addl $4, %rsp
	subl %rax, (%rsp)
	popl %rax
	movl %rax, a
	pushl %eax
	movl x, %eax
	pushl %eax
	movl a, %eax
	pushl %eax
	movl c, %eax
	movss (%rsp), %xmm1
	movss %rax, %xmm0
	mulss %xmm1, %xmm0
	movss %xmm0, %rax
	addl $4, %rsp
	pushl %eax
	movl e, %eax
	movsd (%rsp), %xmm0
	movsd %rax, %xmm1
	divsd %xmm1, %xmm0
	movsd %xmm0, %rax
	addq $8, %rsp
	pushl %rax
	movl $2, %rax
	pushl %rax
	movl $3, %rax
	mull (%rsp)
	addl $4, %rsp
	movsd (%rsp), %xmm1
	movsd %rax, %xmm0
	addsd %xmm1, %xmm0
	movsd %xmm0, %rax
	addq $8, %rsp
	movq %rax, e
	pushl %rax
	movl $3, %rax
	pushl %rax
	movl $4, %rax
	mull (%rsp)
	addl $4, %rsp
	pushl %rax
	movl $1079613850, %rax
	pushl %eax
	movl a, %eax
	movss (%rsp), %xmm1
	movss %rax, %xmm0
	addss %xmm1, %xmm0
	movss %xmm0, %rax
	addl $4, %rsp
	movss (%rsp), %xmm1
	movss %rax, %xmm0
	addss %xmm1, %xmm0
	movss %xmm0, %rax
	addl $4, %rsp
	pushl %eax
	movl c, %eax
	movss (%rsp), %xmm1
	movss %rax, %xmm0
	subss %xmm1, %xmm0
	movss %xmm0, %rax
	addl $4, %rsp
	movq %rax, e
	.L5:
	pushl %eax
	movl x, %eax
	pushl %eax
	movl y, %eax
	pushl %eax
	movl y, %eax
	jz .L6
	pushl %eax
	movl a, %eax
	pushl %eax
	movl b, %eax
	mull (%rsp)
	addl $4, %rsp
	pushl %rax
	movl $2, %rax
	pushl %rax
	movl $1082810329, %rax
	movss (%rsp), %xmm1
	movss %rax, %xmm0
	mulss %xmm1, %xmm0
	movss %xmm0, %rax
	addl $4, %rsp
	movss (%rsp), %xmm1
	movss %rax, %xmm0
	addss %xmm1, %xmm0
	movss %xmm0, %rax
	addl $4, %rsp
	movl %rax, c
	jmp .L5
	.L6:
