
int labelcounter = 1;

// control pseudo-instructions

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
  fprintf (object, "\tmovl %%rax, %s\n", variable);
  return 0
}

int lmove_q(char const* variable) { //64 bits
  fprintf (object, "\tmovq %%rax, %s\n", variable);
  return 0;
}

int rmove_int(char const* variable) { //32 bits
  fprintf(object, "\tpushl %%rax");
  fprintf (object, "\tmovl %s, %%rax\n", variable);
  return 0;
}

int rmove_q(char const* variable) { //64 bits
  fprintf(object, "\tpushl %%rax");
  fprintf (object, "\tmovq %s, %%rax\n", variable);
  return 0;
}

// ULA pseudo-instructions

// Unary instructions

int neg_instruction(int type) {
  switch(type) {
    case BOOLEAN:
      // TODO
      break;
    case INTEGER:
      fprintf(obejct, "\tnegl %%rax\n");
      break;
    case REAL:
      // TODO
      break;
    case DOUBLE:
      // TODO
      break;
  }

  return 0;
}

// Binary instructions

int add_instruction(int type) {
  switch(type) {
    case BOOLEAN:
      // TODO
      break;

    case INTEGER:
      fprintf(object, "\taddl %%rax, (%%rsp)\n");
      fprintf(object, "\taddl $4, %%rsp\n");
      break;

    case REAL:
      fprintf(object, "\tmovss (%%rsp), %%xmm1\n");
      fprintf(object, "\tmovss %%rax, %%xmm0\n");
      fprintf(object, "\taddss %%xmm1, %%xmm0\n");
      fprintf(object, "\tmovss %%xmm0, %%rax\n");
      fprintf(object, "\taddl $4, %%rsp\n");
      break;

    case DOUBLE:
      fprintf(object, "\tmovsd (%%rsp), %%xmm1\n");
      fprintf(object, "\tmovsd %%rax, %%xmm0\n");
      fprintf(object, "\taddsd %%xmm1, %%xmm0\n");
      fprintf(object, "\tmovsd %%xmm0, %%rax\n");
      fprintf(object, "\taddq $8, %%rsp\n");
      break;
  }

  return 0;
}

int sub_instruction(int type) {
  if (type == BOOLEAN) {
    // TODO: throw an error or something like that
    return -1;
  }

  switch(type) {
    case INTEGER:
      fprintf(object, "\tsubl %%rax, (%%rsp)\n");
      fprintf(object, "\tpopl %%rax\n");
      break;

    case REAL:
      fprintf(object, "\tmovss (%%rsp), %%xmm1\n");
      fprintf(object, "\tmovss %%rax, %%xmm0\n");
      fprintf(object, "\tsubss %%xmm1, %%xmm0\n");
      fprintf(object, "\tmovss %%xmm0, %%rax\n");
      fprintf(object, "\taddl $4, %%rsp\n");
      break;

    case DOUBLE:
      fprintf(object, "\tmovsd (%%rsp), %%xmm1\n");
      fprintf(object, "\tmovsd %%rax, %%xmm0\n");
      fprintf(object, "\tsubsd %%xmm1, %%xmm0\n");
      fprintf(object, "\tmovsd %%xmm0, %%rax\n");
      fprintf(object, "\taddq $8, %%rsp\n");
      break;

  }

  return 0;
}

int mul_instruction(int type) {
  switch(type) {
    case BOOLEAN:
      // TODO
      break;
    case INTEGER:
      fprintf(object, "\tmull (%%rsp)\n");
      fprintf(object, "\taddl $4, %%rsp\n");
      break;

    case REAL:
      fprintf(object, "\tmovss (%%rsp), %%xmm1\n");
      fprintf(object, "\tmovss %%rax, %%xmm0\n");
      fprintf(object, "\tmulss %%xmm1, %%xmm0\n");
      fprintf(object, "\tmovss %%xmm0, %%rax\n");
      fprintf(object, "\taddl $4, %%rsp\n");
      break;

    case DOUBLE:
      fprintf(object, "\tmovsd (%%rsp), %%xmm1\n");
      fprintf(object, "\tmovsd %%rax, %%xmm0\n");
      fprintf(object, "\tmulsd %%xmm1, %%xmm0\n");
      fprintf(object, "\tmovsd %%xmm0, %%rax\n");
      fprintf(object, "\taddq $8, %%rsp\n");
      break;
  }

  return 0;
}

int mod_instruction() {
  fprintf(object, "divl (%%rsp)");
  fprintf(obejct, "movl %%edx, %%rax");
  return 0;
}

int div_instruction(int type) {
  if (type == BOOLEAN) {
    // TODO: throw an error or something like that
    return -1;
  }

  switch(type) {
    case INTEGER:
      fprintf(object, "\tdivl (%%rsp)\n");
      fprintf(object, "\taddl $4, %%rsp\n");
      break;

    case REAL:
      fprintf(object, "\tmovss (%%rsp), %%xmm0\n");
      fprintf(object, "\tmovss %%rax, %%xmm1\n");
      fprintf(object, "\tdivss %%xmm1, %%xmm0\n");
      fprintf(object, "\tmovss %%xmm0, %%rax\n");
      fprintf(object, "\taddq $8, %%rsp\n");
      break;

    case DOUBLE:
      fprintf(object, "\tmovsd (%%rsp), %%xmm0\n");
      fprintf(object, "\tmovsd %%rax, %%xmm1\n");
      fprintf(object, "\tdivsd %%xmm1, %%xmm0\n");
      fprintf(object, "\tmovsd %%xmm0, %%rax\n");
      fprintf(object, "\taddq $8, %%rsp\n");
      break;
  }

  return 0;
}
