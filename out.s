	pushl %rax
	movl $2, %rax
	mov %rax, a

	pushl %rax
	movl b, %rax
	mov %rax, a

	pushl %rax
	movl a, %rax
	mov %rax, c

	pushl %rax
	movl $1, %rax
	mov %rax, c

	pushl %rax
	movl $1078774989, %rax
	mov %rax, c

	pushl %rax
	movss d, %rax
	mov %rax, c

	pushl %rax
	movl a, %rax
	movq %rax, e

	pushl %rax
	movl $1, %rax
	movq %rax, e

	pushl %rax
	movl $1078774989, %rax
	movq %rax, e

	pushl %rax
	movss d, %rax
	movq %rax, e

	pushl %rax
	movsd f, %rax
	movq %rax, e

	pushl %rax
	movl $-1, %rax
	mov %rax, x

	pushl %rax
	movl $0, %rax
	mov %rax, x

	pushl %rax
	movl y, %rax
	mov %rax, x

	pushl %rax
	movl x, %rax
	jz .L1
	pushl %rax
	movl $-1, %rax

	.L1:

	pushl %rax
	movl $3, %rax
	pushl %rax
	movl a, %rax
	cmp (%rsp), %rax
	jg .REL_LABEL0
	mov $0, %rax
	jmp .REL_LABEL1
	.REL_LABEL0:
	mov $1, %rax
	.REL_LABEL1:
	cmp $0, %rax
	jz .L2
	pushl %rax
	movl $-1, %rax

	.L2:

	pushl %rax
	movl $1082549862, %rax
	pushl %rax
	movss c, %rax
	cmp (%rsp), %rax
	jne .REL_LABEL2
	mov $0, %rax
	jmp .REL_LABEL3
	.REL_LABEL2:
	mov $1, %rax
	.REL_LABEL3:
	cmp $0, %rax
	jz .L3
	pushl %rax
	movl $-1, %rax

	.L3:

	pushl %rax
	movl x, %rax
	pushl %rax
	movl y, %rax
	AND %rax, (%rsp) 
	addl $8, %rsp
	jz .L4
	pushl %rax
	movl $-1, %rax

	.L4:

	pushl %rax
	movl $2, %rax
	pushl %rax
	movl $4, %rax
	mull (%rsp)
	addl $8, %rsp
	pushl %rax
	movl b, %rax
	pushl %rax
	movl a, %rax
	divl (%rsp)
	addl $8, %rsp
	subl %rax, (%rsp)
	addl $8, %rsp
	mov %rax, a

	pushl %rax
	movl $-1, %rax
	pushl %rax
	movl $0, %rax
	AND %rax, (%rsp) 
	addl $8, %rsp
	mov %rax, x

	pushl %rax
	movl x, %rax
	pushl %rax
	movl $0, %rax
	OR %rax, (%rsp) 
	addl $8, %rsp

	pushl %rax
	movl a, %rax
	pushl %rax
	movss c, %rax
	movss (%rsp), %xmm1
	movss %rax, %xmm0
	mulss %xmm1, %xmm0
	movss %xmm0, %rax
	addl $8, %rsp
	pushl %rax
	movsd e, %rax
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
	addl $8, %rsp
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
	addl $8, %rsp
	pushl %rax
	movl $1079613850, %rax
	pushl %rax
	movss a, %rax
	movss (%rsp), %xmm1
	movss %rax, %xmm0
	addss %xmm1, %xmm0
	movss %xmm0, %rax
	addl $8, %rsp
	movss (%rsp), %xmm1
	movss %rax, %xmm0
	addss %xmm1, %xmm0
	movss %xmm0, %rax
	addl $8, %rsp
	pushl %rax
	movss c, %rax
	movss (%rsp), %xmm1
	movss %rax, %xmm0
	subss %xmm1, %xmm0
	movss %xmm0, %rax
	addl $8, %rsp
	movq %rax, e

	.L5:
	pushl %rax
	movl x, %rax
	pushl %rax
	movl y, %rax
	pushl %rax
	movl y, %rax
	pushl %rax
	movl $-1, %rax
	AND %rax, (%rsp) 
	addl $8, %rsp
	AND %rax, (%rsp) 
	addl $8, %rsp
	OR %rax, (%rsp) 
	addl $8, %rsp
	jz .L6
	pushl %rax
	movl a, %rax
	pushl %rax
	movl b, %rax
	mull (%rsp)
	addl $8, %rsp
	pushl %rax
	movl $2, %rax
	pushl %rax
	movl $1082810329, %rax
	movss (%rsp), %xmm1
	movss %rax, %xmm0
	mulss %xmm1, %xmm0
	movss %xmm0, %rax
	addl $8, %rsp
	movss (%rsp), %xmm1
	movss %rax, %xmm0
	addss %xmm1, %xmm0
	movss %xmm0, %rax
	addl $8, %rsp
	mov %rax, c



	jmp .L5
	.L6:

