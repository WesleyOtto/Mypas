
/*global label counter*/
extern int labelcounter;

/*control pseudo-instructions*/
int go_false(int label);
int jump(int label);
int mklabel(int label);
int lmove_int(char const* variable);
int lmove_q(char const* variable);
int rmove_int(char const* variable);
int rmove_q(char const* variable);

/*ULA pseudo-instructions*/
/*unary*/
int neg_logic(void);
int neg_int(void);
int neg_float(void);
int neg_double(void);

/*binary addition*/
int add_logic(void);
int add_int(void);
int add_float(void);
int add_double(void);

/*binary subtraction*/
int sub_int(void);
int sub_float(void);
int sub_double(void);

/*binary mutiplication*/
int mul_logic(void);
int mul_int(void);
int mul_float(void);
int mul_double(void);

/*binary division*/
int div_int(void);
int div_float(void);
int div_double(void);

