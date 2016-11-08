#define MAX_SYMTAB_ENTRIES 0x10000

extern int symtab[MAX_SYMTAB_ENTRIES][2];
extern char symtab_stream[];

int symtab_append(char const *name, int type);
int symtab_lookup(char const *name);
