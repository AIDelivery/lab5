#include <iostream>
#include <unistd.h>
#include <signal.h>

void ssig_handler() {
  kill(0, SIGINT);
}

int main(int argv, char* argc[]) {
  sigset_t mask;
  signal(SIGALRM, (sighandler_t) ssig_handler);

  for(int i = 0; i < 5; i++) {
    if(fork() == 0) {
      std::cout << "New descesor process with PID = " << getpid() << std::endl;
      pause();
      std::cout << getpid() << " is paused..." << std::endl;
    }
  }

  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);
  sigprocmask(SIG_BLOCK, &mask, 0);
  std::cout << "Sending alarm signal..." << std::endl;
  alarm(10);
  pause();
  std::cout << "Ancesor ending its job..." << std::endl;
  return 0;
}
