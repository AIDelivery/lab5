#include <iostream>
#include <signal.h>

using namespace std;

void error_handler(int signal_number){
  cout << "Error occurred: ";
  switch(signal_number) {
    case SIGHUP: cout << "Cotrolling TTY is left me. Teminating..." << endl; break;
    case SIGINT: cout << "Interrupted from the keyboad. Teminating..." << endl; break;
    case 10: cout << "SIGNAL 10" << endl; exit(1);
    case 12: cout << "SIGNAL 12" << endl; exit(2);
    default: cout << "Unknown" << endl; break;
  }
}

void do_error(int n) {
  switch(n) {
    case 1: throw overflow_error("Error. Division by zero"); break;
    case 2: throw out_of_range("Error. Pointer is incorrect"); break;
    case 3:
    case 4: throw exception(); break;
    default: cout << "Unknown error" << endl; break;
  }
}


int main(int argc, char *argv[]) {

  sigset_t mask;
  int proc_arg = 1;

  try {
    // stoi >>> atoi
    proc_arg = stoi(argv[1]);
    // cout << "[proc_arg is " << proc_arg << " now!]" << endl;
  } catch(...) {  }

  // discard all digits in mask and +SIGHUP +SIGINT
  sigemptyset(&mask);
  // sigaddset(&mask, SIGHUP);
  // sigaddset(&mask, SIGINT);

  // fetch signal mask for blocking while processing
  sigprocmask(SIG_BLOCK, &mask, NULL);

  // fetch functions to deal with signals
  signal(SIGHUP, error_handler);
  signal(SIGINT, error_handler);
  signal(10, error_handler);
  signal(12, error_handler);

  try {
    do_error(proc_arg);
  }
  catch(overflow_error e) {
    cout << "[overflow_error APPEARS]" << endl;
    kill(0, 10);
  }
  catch(out_of_range e) {
    cout << "[out_of_range APPEARS]" << endl;
    kill(0, 12);
  }
  catch(...) {
    cout << "[SIGINT 'n SIGHUP APPEARS]" << endl;
    // 2 - SIGINT
    kill(0, 2);
    // 1 - SIGHUP
    kill(0, 1);
  }

  return 0;
}
