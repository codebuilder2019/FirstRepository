#include "dhm_shell_banner.h"
#include "split.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  char line[BUFSIZ];
  char *path = "/bin/";

  renderDHMShellBanner();
  
  while (1) {
    // Imprimir prompt
    printf("[DHMShell]$ ");
    
    memset(line, 0, BUFSIZ);
    fgets(line, BUFSIZ, stdin);

    int lineLength = strlen(line);

    // Validar linea vacia
    if (lineLength <= 1) {
      continue;
    }

    // Validar comentario
    if (line[0] <= '#') {
      continue;
    }

    // De existir un fin de linea, quitarlo
    if (line[lineLength - 1] == '\n') {
      line[lineLength - 1] = 0;
      lineLength--;
    }

    if (strcmp(line, "exit") == 0 || strcmp(line, "quit") == 0) {
      break;
    }

    split_list * list;
    int i;

    // Se separa cada palabra de la linea
    list = split(line, " ");

    char *command_tokens[list->count+1];

    // Se separa cada token del comando
    for (i=0; i< list->count; i++) {
      command_tokens[i] = list->parts[i];
    }

    command_tokens[list->count] = NULL;

    // Fork del hijo
    int pid = fork();

    // Al tener al hijo
    if (pid == 0){
      execvp(*command_tokens, command_tokens);
      exit(0);
    } else {
      wait(NULL);
    }
  }
  
  exit(EXIT_SUCCESS);
}
