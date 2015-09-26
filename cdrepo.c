#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *parent_dir(char* path) {
  int path_index = 0;
  while (path[path_index] != '\0') {
    path_index += 1;
  }
  int path_length = path_index + 1;

  int parent_index = path_length;
  while (path[parent_index] != '/') {
    parent_index -= 1;
  }

  char *parent_dir = malloc(path_length);
  for (int i = 0; i < parent_index; i++) {
    parent_dir[i] = path[i];
  }

  return parent_dir;
}

int main(int argc, char **argv) {
  char *script = malloc(2048);
  realpath(argv[1], script);
  char *script_parent = parent_dir(script);
  FILE *script_fp = fopen(script, "r");

  char *line = NULL;
  size_t line_len = 0;

  char *accum;
  int accum_len = 0;
  char *prev_accum = "";
  int is_first_line = 1;

  while (getline(&line, &line_len, script_fp) != -1) {
    if (!is_first_line) {
      accum = malloc(accum_len + line_len);
      strcpy(accum, prev_accum);
      strcat(accum, line);

      accum_len += line_len;
      prev_accum = accum;
    } else {
      is_first_line = 0;
    }
  }

  char *script_src = accum;

  char **script_args = malloc(255);
  script_args[0] = "bash";
  script_args[1] = "-c";
  script_args[2] = script_src;
  script_args[3] = script_parent;

  int script_arg_count = 4;
  for (int i = 0; i < argc; i++) {
    script_args[i + 4] = argv[i + 2];
    script_arg_count += 1;
  }
  script_args[script_arg_count] = (char *)NULL;

  execv("/bin/bash", script_args);
}

