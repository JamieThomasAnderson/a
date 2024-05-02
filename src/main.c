#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <editline/readline.h>
#include <editline/history.h>

#include "a.h"

static char input[2048];

int main(int argc, const char *argv[]) {

  puts("a version v0.1");
  
  while(1)
  {
    // change
    char * input = readline("a> ");
    add_history(input);
    printf("YOU SAID: %s\n", input);
    free(input);
  }

  return 0;

}
