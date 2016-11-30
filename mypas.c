#include <stdio.h>
#include <stdlib.h>
#include <parser.h>
#include <string.h>
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
  char* output_file_name = "out.s";
  const char* source_file_extension;
/*
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

  source_file_extension = get_filename_ext(source_file_name);

  // If it's not .pas extension, abort the program
  if (strcmp(source_file_extension, "pas")) {
    fprintf(stderr, "The source file name must have a .pas extension\n");
    return -1;
  }
*/
  //source = fopen(source_file_name, "r");
  source = fopen("teste.pas", "r");

  if (source == NULL) {
    fprintf(stderr, "%s: cannot open %s. Exiting...\n", argv[0], source_file_name);
    return -2;
  }

  object = fopen(output_file_name, "w");

  mypas();

  fclose(source);
  fclose(object);

  if (semanticErr > 0) {
    remove(output_file_name);
  }

  return semanticErr;
}

const char *get_filename_ext(const char *filename) {
  const char *dot = strrchr(filename, '.');
  if(!dot || dot == filename) return "";
  return dot + 1;
}

void print_usage_message() {
  fprintf(stderr, "You are not using it correctly, my friend!\n");
  fprintf(stderr, "Usage:\n\n");
  fprintf(stderr, "\t<program_name> source_file_name [options]\n\n");
  fprintf(stderr, "Options:\n");
  fprintf(stderr, "\t-o\t\t\t\t\t# Specify an output file name\n");
}
