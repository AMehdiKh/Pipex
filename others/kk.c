#include <stdio.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    char buffer[20];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process
        // close(pipefd[1]); // Close the write end of the pipe
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child process received message: %s\n", buffer);
        // close(pipefd[0]); // Close the read end of the pipe
    } else {
        // Parent process
        // close(pipefd[0]); // Close the read end of the pipe
        write(pipefd[1], "Hello from parent", 17);
        // close(pipefd[1]); // Close the write end of the pipe
    }

    return 0;
}