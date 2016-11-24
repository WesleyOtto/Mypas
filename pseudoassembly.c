
int labelcounter = 1;

int go_false(int label) {
	fprintf(object, "\tjz .L%d\n", label);
	return label;
}

int jump(int label) {
	fprintf(object, "\tjmp .L%d\n", label);
	return label;
}

int mklabel(int label) {
	fprintf(object, "\t.L%d:\n", label);
	return label;
}

int lmove_int(char const* variable) { //32 bits
	fprintf (object, "\tmovl %%eax, %s\n", variable);
	return 0
}

int lmove_q(char const* variable) { //64 bits
	fprintf (object, "\tmovq %%rax, %s\n", variable);
	return 0;
}

int rmove_int(char const* variable) { //32 bits
	fprintf(object, "\tpushl %%eax");
	fprintf (object, "\tmovl %s, %%eax\n", variable);
	return 0;
}

int rmove_q(char const* variable) { //64 bits
	fprintf(object, "\tpushl %%rax");
	fprintf (object, "\tmovq %s, %%rax\n", variable);
	return 0;
}

/*ULA pseudo-instructions*/
/*unary*/
int neg_logic(void) {
	//NOT
}

int neg_int(void) {
	fprintf(obejct, "\tnegl %%eax\n");
	return 0;
}

int neg_float(void) {

}

int neg_double(void) {

}

/*binary addition*/
int add_logic(void) {
	//OR
}

int add_int(void) {
	fprintf(object, "\taddl %%eax, (%%esp)\n");
	fprintf(object, "\taddl $4, %%esp\n"); //dec pilha
	return 0;
}

int add_float(void) {
	fprintf(object, "\tmovss (%%esp), %%xmm1\n");
	fprintf(object, "\tmovss %%eax, %%xmm0\n");
	fprintf(object, "\taddss %%xmm1, %%xmm0\n");
	fprintf(object, "\tmovss %%xmm0, %%eax\n");
	fprintf(object, "\taddl $4, %%esp\n"); //dec pilha
	return 0;
}

int add_double(void) {
	fprintf(object, "\tmovsd (%%rsp), %%xmm1\n");
	fprintf(object, "\tmovsd %%rax, %%xmm0\n");
	fprintf(object, "\taddsd %%xmm1, %%xmm0\n");
	fprintf(object, "\tmovsd %%xmm0, %%rax\n");
	fprintf(object, "\taddq $8, %%rsp\n"); //dec pilha
	return 0;
}

/*binary subtraction*/
int sub_int(void) {
	fprintf(object, "\tsubl %%eax, (%%esp)\n");
	fprintf(object, "\tpopl %%eax\n");
	return 0;
}

int sub_float(void) {
	fprintf(object, "\tmovss (%%esp), %%xmm1\n");
	fprintf(object, "\tmovss %%eax, %%xmm0\n");
	fprintf(object, "\tsubss %%xmm1, %%xmm0\n");
	fprintf(object, "\tmovss %%xmm0, %%eax\n");
	fprintf(object, "\taddl $4, %%esp\n"); //dec pilha
	return 0;
}

int sub_double(void) {
	fprintf(object, "\tmovsd (%%rsp), %%xmm1\n");
	fprintf(object, "\tmovsd %%rax, %%xmm0\n");
	fprintf(object, "\tsubsd %%xmm1, %%xmm0\n");
	fprintf(object, "\tmovsd %%xmm0, %%rax\n");
	fprintf(object, "\taddq $8, %%rsp\n"); //dec pilha
	return 0;
}

/*binary mutiplication*/
int mul_logic(void) {
	//AND
}

int mul_int(void) {
	fprintf(object, "\tmull (%%esp)\n");
	fprintf(object, "\taddl $4, %%esp\n");

	return 0;
}

int mul_float(void) {
	fprintf(object, "\tmovss (%%esp), %%xmm1\n");
	fprintf(object, "\tmovss %%eax, %%xmm0\n");
	fprintf(object, "\tmulss %%xmm1, %%xmm0\n");
	fprintf(object, "\tmovss %%xmm0, %%eax\n");
	fprintf(object, "\taddl $4, %%esp\n"); //dec pilha
	return 0;
}

int mul_double(void) {
	fprintf(object, "\tmovsd (%%rsp), %%xmm1\n");
	fprintf(object, "\tmovsd %%rax, %%xmm0\n");
	fprintf(object, "\tmulsd %%xmm1, %%xmm0\n");
	fprintf(object, "\tmovsd %%xmm0, %%rax\n");
	fprintf(object, "\taddq $8, %%rsp\n"); //dec pilha
	return 0;
}

/*binary division*/

int mod_int(void) {
	fprintf(object, "divl (%%esp)");
	fprintf(obejct, "movl %%edx, %%eax");
	return 0;
}

int div_int(void) {
	fprintf(object, "\tdivl (%%esp)\n");
	fprintf(object, "\taddl $4, %%esp\n");
	return 0;
}

int div_float(void) {
	fprintf(object, "\tmovss (%%rsp), %%xmm0\n");
	fprintf(object, "\tmovss %%rax, %%xmm1\n");
	fprintf(object, "\tdivss %%xmm1, %%xmm0\n");
	fprintf(object, "\tmovss %%xmm0, %%rax\n");
	fprintf(object, "\taddq $8, %%rsp\n"); //dec pilha
	return 0;
}

int div_double(void) {
	fprintf(object, "\tmovsd (%%rsp), %%xmm0\n");
	fprintf(object, "\tmovsd %%rax, %%xmm1\n");
	fprintf(object, "\tdivsd %%xmm1, %%xmm0\n");
	fprintf(object, "\tmovsd %%xmm0, %%rax\n");
	fprintf(object, "\taddq $8, %%rsp\n"); //dec pilha
	return 0;
}
