#include <iostream>
#include <signal.h>

using namespace std;

void error_handler(int signal_number){

  cout << "Error occurred: ";
  switch(signal_number) {
    case SIGHUP: cout << "TTY is dead. Teminating..." << endl; break;
    case SIGINT: cout << "Interrupted from the keyboad. Teminating..." << endl; break;
    case 10: cout << "SIGNAL 10" << endl; exit(1);
    case 12: cout << "SIGNAL 12" << endl; exit(2);
    default: cout << "Unknown" << endl; break;
  }
  cout << "Interruption..." << endl;
}

int main(int argc, char *argv[]) {
  sigset_t mask;

  int proc_arg = atoi(argv[1]);

  sigemptyset(&mask);
  sigaddset(&mask, SIGHUP);
  sigaddset(&mask, SIGINT);
  sigprocmask(SIG_BLOCK, &mask, 0);

  signal(SIGHUP, error_handler);
  signal(SIGINT, error_handler);
  signal(10, error_handler);
  signal(12, error_handler);

  try {
    switch(proc_arg) {
      case 1: throw overflow_error("DivbyZero"); break;
      case 2: throw out_of_range("Pointer is incorrect"); break;
      default: cout << "Unknown error" << endl; break;
    }
  }
  catch(overflow_error e) {
    cout << "ov catch" << endl;
    kill(0, 10);
  }
  catch(out_of_range e) {
    cout << "our error catch" << endl;
    kill(0, 12);
  }

  return 0;
}
