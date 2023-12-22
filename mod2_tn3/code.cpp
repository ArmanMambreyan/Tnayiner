#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main() {
    pid_t pid = fork();




    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
      
    } else if (pid == 0) {
        sleep(2);
        printf("Verevi processi anjatman porc nerqevinic\n");

      
        if (kill(getppid(), SIGKILL) == 0) {
            printf("Porci hajoxum\n");
        } else {
            printf("Porci dzaxoxum\n");
        }
    } else {
        printf("Processi veradarc\n");
        sleep(5);
        printf("Processi mah\n");
    }

    return 0;
}
