#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a.h"

static char input[2048];

int main(int argc, const char *argv[]) {

  puts("a version v0.1");
  
  while(1)
  {
    fputs("a> ", stdout);
    fgets(input, 2048, stdin);
    printf("You Said: %s", input);
    
  }

  return 0;

}
