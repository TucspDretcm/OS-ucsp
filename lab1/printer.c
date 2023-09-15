#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sig_act(int sign, siginfo_t *info, void *context) {
    printf("Value of x + 1 = %d\n", info->si_value.sival_int + 1);
}

int main(int argc, char **args) {
  pid_t pid = getpid();
  printf("PID Program: %d\nProgram Run ...\n", (int)pid);
  
  struct sigaction sa = {
    .sa_sigaction= sig_act,
    .sa_flags = SA_RESTART|SA_SIGINFO
  };
  
  sigaction(SIGUSR1, &sa, NULL);

  while (1) {
    sleep(1);
  }
  
  return (0);
}