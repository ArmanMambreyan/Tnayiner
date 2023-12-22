#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t child1, child2;
    pid_t pid_buffer;

    
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if ((child1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child1 == 0) {
        
        close(pipe_fd[0]);  
    printf("First child pid: %d\n", getpid());
        
        pid_buffer = getpid();
        write(pipe_fd[1], &pid_buffer, sizeof(pid_t));

        close(pipe_fd[1]); 
        exit(EXIT_SUCCESS);
    } else {
        
        if ((child2 = fork()) == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child2 == 0) {
           
            close(pipe_fd[0]); 
      printf("Second child pid: %d\n", getpid());
            
            pid_buffer = getpid();
            write(pipe_fd[1], &pid_buffer, sizeof(pid_t));

            close(pipe_fd[1]);  
            exit(EXIT_SUCCESS);
        } else {
            
            close(pipe_fd[1]);  

           
            read(pipe_fd[0], &pid_buffer, sizeof(pid_t));
            printf("First child PID: %d\n", pid_buffer);

            read(pipe_fd[0], &pid_buffer, sizeof(pid_t));
            printf("Second child PID: %d\n", pid_buffer);

            close(pipe_fd[0]); 
            waitpid(child1, NULL, 0);
            waitpid(child2, NULL, 0);
        }
    }

    return 0;
}
