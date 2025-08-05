#include "kernel/types.h"
#include "user/user.h"

int main() {
    int p2c[2];
    int c2p[2];
    char buf[1];
    pipe(p2c);
    pipe(c2p);
    
    int pid;
    pid = fork();
    if (pid<0) {
        printf("Fork Failed!!\n");
        exit(0);
    }
    if (pid == 0) { // returns 0 in the child process
        read(p2c[0], buf, 1);
        printf("%d: received ping \n", getpid());
        write(c2p[1], buf, 1);
        exit(0);
    } else {
        write(p2c[1], "x", 1);
		read(c2p[0], buf, 1);
		printf("%d: received pong\n", getpid()); // 1 -> file descriptor -> standard output (0-stdin, 1- stdout, 2- stderr)
		wait(0);
		exit(0);
    }
}