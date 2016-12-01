#include <stdio.h>
#include <parser.h>
#include <keywords.h>
#include <tokens.h>
#include <pseudoassembly.h>

int labelcounter = 1;

// control pseudo-instructions

int go_false(int label)
{
  fprintf(object, "\tjz .L%d\n", label);
  return label;
}

int jump(int label)
{
  fprintf(object, "\tjmp .L%d\n", label);
  return label;
}

int mklabel(int label)
{
  fprintf(object, "\t.L%d:\n", label);
  return label;
}

int lmove_int(char const* variable)
{ //32 bits
  fprintf (object, "\tmov %%rax, %s\n", variable);
  return 0;
}

int lmove_q(char const* variable)
{ //64 bits
  fprintf (object, "\tmovq %%rax, %s\n", variable);
  return 0;
}

int rmove_int(char const* variable)
{ //32 bits
  fprintf(object, "\tpushl %%rax\n");
  fprintf (object, "\tmovl %s, %%rax\n", variable);
  return 0;
}

int rmove_q(char const* variable)
{ //64 bits
  fprintf(object, "\tpushl %%rax\n");
  fprintf (object, "\tmovq %s, %%rax\n", variable);
  return 0;
}

// ULA pseudo-instructions

// Unary instructions

int neg_instruction(int type)
{
    switch(type) {
        case BOOLEAN:
            fprintf(object, "\tnot %%rax\n");
            break;
        case INTEGER:
            fprintf(object, "\tnegl %%rax\n");
            break;
        case REAL:
            fprintf(object, "\tnegss %%rax\n");
            break;
        case DOUBLE:
            fprintf(object, "\tnegsd %%rax\n");
            break;
        default:
            return -1;
    }

  return 0;
}

// Binary instructions

int add_instruction(int type)
{
    switch(type) {
        case BOOLEAN:
            fprintf(object, "\tOR %%rax, (%%rsp) \n");
            fprintf(object, "\taddl $8, %%rsp\n");
            break;

        case INTEGER:
            fprintf(object, "\taddl %%rax, (%%rsp)\n");
            fprintf(object, "\taddl $8, %%rsp\n");
            break;

        case REAL:
            fprintf(object, "\tmovss (%%rsp), %%xmm1\n");
            fprintf(object, "\tmovss %%rax, %%xmm0\n");
            fprintf(object, "\taddss %%xmm1, %%xmm0\n");
            fprintf(object, "\tmovss %%xmm0, %%rax\n");
            fprintf(object, "\taddl $8, %%rsp\n");
            break;

        case DOUBLE:
            fprintf(object, "\tmovsd (%%rsp), %%xmm1\n");
            fprintf(object, "\tmovsd %%rax, %%xmm0\n");
            fprintf(object, "\taddsd %%xmm1, %%xmm0\n");
            fprintf(object, "\tmovsd %%xmm0, %%rax\n");
            fprintf(object, "\taddq $8, %%rsp\n");
            break;

        default:
            return -1;
    }
    return 0;
}

int sub_instruction(int type)
{
    switch(type) {
        case INTEGER:
            fprintf(object, "\tsubl %%rax, (%%rsp)\n");
            fprintf(object, "\taddl $8, %%rsp\n");
            break;

        case REAL:
            fprintf(object, "\tmovss (%%rsp), %%xmm1\n");
            fprintf(object, "\tmovss %%rax, %%xmm0\n");
            fprintf(object, "\tsubss %%xmm1, %%xmm0\n");
            fprintf(object, "\tmovss %%xmm0, %%rax\n");
            fprintf(object, "\taddl $8, %%rsp\n");
            break;

        case DOUBLE:
            fprintf(object, "\tmovsd (%%rsp), %%xmm1\n");
            fprintf(object, "\tmovsd %%rax, %%xmm0\n");
            fprintf(object, "\tsubsd %%xmm1, %%xmm0\n");
            fprintf(object, "\tmovsd %%xmm0, %%rax\n");
            fprintf(object, "\taddq $8, %%rsp\n");
            break;

        default:
            return -1;
    }
    return 0;
}

int mul_instruction(int type)
{
    switch(type) {
        case BOOLEAN:
            fprintf(object, "\tAND %%rax, (%%rsp) \n");
            fprintf(object, "\taddl $8, %%rsp\n");
            break;

        case INTEGER:
            fprintf(object, "\tmull (%%rsp)\n");
            fprintf(object, "\taddl $8, %%rsp\n");
            break;

        case REAL:
            fprintf(object, "\tmovss (%%rsp), %%xmm1\n");
            fprintf(object, "\tmovss %%rax, %%xmm0\n");
            fprintf(object, "\tmulss %%xmm1, %%xmm0\n");
            fprintf(object, "\tmovss %%xmm0, %%rax\n");
            fprintf(object, "\taddl $8, %%rsp\n");
            break;

        case DOUBLE:
            fprintf(object, "\tmovsd (%%rsp), %%xmm1\n");
            fprintf(object, "\tmovsd %%rax, %%xmm0\n");
            fprintf(object, "\tmulsd %%xmm1, %%xmm0\n");
            fprintf(object, "\tmovsd %%xmm0, %%rax\n");
            fprintf(object, "\taddq $8, %%rsp\n");
            break;

        default:
            return -1;
    }
    return 0;
}

int div_instruction(int type)
{
    switch(type) {
        case INTEGER:
            fprintf(object, "\tdivl (%%rsp)\n");
            fprintf(object, "\taddl $8, %%rsp\n");
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

        default:
            return -1;
    }

  return 0;
}

int mod_instruction()
{
    fprintf(object, "divl (%%rsp)");
    fprintf(object, "movl %%rdx, %%rax");
    return 0;
}

int relLabelCounter = 0;

void rel_instruction(char *jump)
{
    int jmpTrue, jmpFalse;

    fprintf(object, "\tcmp (%%rsp), %%rax\n");
    fprintf(object, "\t%s .REL_LABEL%d\n", jump, jmpTrue = relLabelCounter++);
    fprintf(object, "\tmov $0, %%rax\n");
    fprintf(object, "\tjmp .REL_LABEL%d\n", jmpFalse = relLabelCounter++);
    fprintf(object, "\t.REL_LABEL%d:\n", jmpTrue);
    fprintf(object, "\tmov $1, %%rax\n");
    fprintf(object, "\t.REL_LABEL%d:\n",jmpFalse);
    fprintf(object, "\tcmp $0, %%rax\n");
}

int generate_rel(int relop)
{
    switch(relop) {
        case '>':
            rel_instruction("jg");
            break;

        case GEQ:
            rel_instruction("jge");
            break;

        case '<':
            rel_instruction("jl");
            break;

        case LEQ:
            rel_instruction("jle");
            break;

        case '=':
            rel_instruction("je");
            break;

        case NEQ:
            rel_instruction("jne");
            break;
    }
    return 0;
}

