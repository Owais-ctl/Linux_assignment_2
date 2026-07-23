#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } 
    
    if (pid == 0) {
        // Child Process: Simulate heavy compute workload
        printf("[Child] PID %d started. Executing task...\n", getpid());
        sleep(10); 
        printf("[Child] Workload completed naturally.\n");
        exit(EXIT_SUCCESS);
    } 
    
    // Parent Process: Monitor child state with timeout handling
    int status;
    printf("[Parent] Monitoring Child (PID %d). Waiting 3 seconds...\n", pid);
    sleep(3); 
    
    // Non-blocking status check
    pid_t result = waitpid(pid, &status, WNOHANG);
    
    if (result == 0) {
        printf("[Parent] Child PID %d timed out. Issuing SIGKILL...\n", pid);
        kill(pid, SIGKILL); 
        
        // Final blocking wait to reap child process
        waitpid(pid, &status, 0); 
        printf("[Parent] Child successfully reaped. No zombie remaining.\n");
    } else {
        printf("[Parent] Child process completed within allocated threshold.\n");
    }

    return 0;
}