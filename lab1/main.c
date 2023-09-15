#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
//  https://people.cs.pitt.edu/~alanjawi/cs449/code/shell/UnixSignals.htm

/*
SIGHUP	1	Exit	Hangup
SIGINT	2	Exit	Interrupt
SIGQUIT	3	Core	Quit
SIGILL	4	Core	Illegal Instruction
SIGTRAP	5	Core	Trace/Breakpoint Trap
SIGABRT	6	Core	Abort
SIGEMT	7	Core	Emulation Trap
SIGFPE	8	Core	Arithmetic Exception
SIGKILL	9	Exit	Killed
SIGBUS	10	Core	Bus Error
SIGSEGV	11	Core	Segmentation Fault
SIGSYS	12	Core	Bad System Call
SIGPIPE	13	Exit	Broken Pipe
SIGALRM	14	Exit	Alarm Clock
SIGTERM	15	Exit	Terminated
SIGUSR1	16	Exit	User Signal 1
SIGUSR2	17	Exit	User Signal 2
SIGCHLD	18	Ignore	Child Status
SIGPWR	19	Ignore	Power Fail/Restart
SIGWINCH	20	Ignore	Window Size Change
SIGURG	21	Ignore	Urgent Socket Condition
SIGPOLL	22	Ignore	Socket I/O Possible
SIGSTOP	23	Stop	Stopped (signal)
SIGTSTP	24	Stop	Stopped (user)
SIGCONT	25	Ignore	Continued
SIGTTIN	26	Stop	Stopped (tty input)
SIGTTOU	27	Stop	Stopped (tty output)
SIGVTALRM	28	Exit	Virtual Timer Expired
SIGPROF	29	Exit	Profiling Timer Expired
SIGXCPU	30	Core	CPU time limit exceeded
SIGXFSZ	31	Core	File size limit exceeded
SIGWAITING	32	Ignore	All LWPs blocked
SIGLWP	33	Ignore	Virtual Interprocessor Interrupt for Threads Library
SIGAIO	34	Ignore	Asynchronous I/O

*/
int x = 66, pid, y;
union sigval val;

void sighandler(int);
void sighandler_random(int);
void sighandler_argv(int);
void sig_term(int);

int main(int argc, char **argv) {
  int num;
  pid_t my_pid = getpid();
  pid = atoi(argv[1]);
  y = atoi(argv[2]);
  printf("My PID: %d\nPID to send: %d\nProgram Run ...\n", (int)my_pid, pid);
  
  signal(SIGINT, sighandler);
  signal(SIGQUIT,	sighandler_random);
  signal(SIGILL, sighandler_argv);
  signal(SIGTERM, sig_term);
  
  while (1) {
    sleep(1);
  }
  return (0);
}

void sighandler(int signum) {
  printf("Caught signal %d sending global value: %d ...\n", signum, x);
  val.sival_int = x;
  sigqueue(pid, SIGUSR1, val);
}

void sighandler_random(int signum) {
  srand(time(NULL));
  int r = (rand()%100) + 1;
  
  printf("Caught signal %d sending random number: %d...\n", signum, r);
  val.sival_int = r;
  sigqueue(pid, SIGUSR1, val);
}

void sighandler_argv(int signum) {
  printf("Caught signal %d sending arg value: %d...\n", signum, y);
  val.sival_int = y;
  sigqueue(pid, SIGUSR1, val);
}

void sig_term(int signum) {
  printf("Good Bye! :D\n");
  kill(pid, SIGTERM);
  exit(0);
}