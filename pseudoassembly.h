
// global label counter
extern int labelcounter;

// control pseudo-instructions
int go_false(int label);
int jump(int label);
int mklabel(int label);
int lmove_int(char const* variable);
int lmove_q(char const* variable);
int rmove_int(char const* variable);
int rmove_q(char const* variable);


// ULA pseudo-instructions

// Unary instructions
int neg_instruction(int type);

// Binary Instructions
int add_instruction(int type);
int sub_instruction(int type);
int mul_instruction(int type);
int div_instruction(int type);
int mod_instruction();

void rel_instruction(char *jump);
int generate_rel(int relop);
