#include <stdio.h>
#include <stdlib.h>
#include <parser.h>
#include <mypas.h>

// Source file stream
FILE *source;

// Output file stream
FILE *object;

// Variable that will count the number of semantic errors in the source program
int semanticErr = 0;

// @ parser.c
extern int lookahead;

int main (int argc, char *argv[], char *envp[]) {
  char* source_file_name = NULL;
  char* output_file_name = NULL;

  if (argc == 2) {
    source_file_name = argv[1];
    output_file_name = "out.s";
  } else if (argc == 4) {
    if (!strcmp(argv[1], "-o")) {
      output_file_name = argv[2];
      source_file_name = argv[3];
    } else if (!strcmp(argv[2], "-o")) {
      source_file_name = argv[1];
      output_file_name = argv[3];
    } else {
      fprintf(stderr, "[ERROR] Wrong passing of arguments!\n\n");
      print_usage_message();
      return -1;
    }
  } else {
    print_usage_message();
    return -1;
  }

  source = fopen(source_file_name, "r");

  if (source == NULL) {
    fprintf(stderr, "%s: cannot open %s. Exiting...\n", argv[0], source_file_name);
    return -2;
  }

  lookahead = gettoken(source);
  mypas();

  return semanticErr;
}
