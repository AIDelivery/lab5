#include <iostream>
#include <signal.h>

using namespace std;

void error_handler(int signal_number){
  cout << "Error occurred: [" << signal_number << "]" << endl;
  switch(signal_number) {
    case SIGHUP: cout << "Cotrolling TTY is left me. Teminating..." << endl; exit(0);
    case SIGINT: cout << "Interrupted from the keyboad. Teminating..." << endl; exit(0);
    case SIGFPE: cout << "Division by zero detected. Teminating..." << endl; exit(0);
    case SIGSEGV: cout << "Out of bounds detected. Teminating..." << endl; exit(0);
    default: cout << "Unknown signal. Unexpected thing happened" << endl; exit(1);
  }
}

void do_error(int n) {
  cout << "[do_error: arg " << n << "]" << endl;
  char s[100];

  switch(n) {
    case 1: cout << n / (n - 1); break;
    case 2: s[1000000000000000] = n; break;
    default: cout << "Unknown error detected. Terminating..." << endl; break;
  }
  exit(EXIT_FAILURE);
}


int main(int argc, char *argv[]) {

  sigset_t mask;
  int proc_arg = 1;

  try {
    // stoi >>> atoi
    proc_arg = stoi(argv[1]);
  } catch(...) {  }

  // discard all digits in mask and +SIGHUP +SIGINT
  sigemptyset(&mask);
  sigaddset(&mask, SIGHUP);
  sigaddset(&mask, SIGTSTP);
  sigaddset(&mask, SIGINT);

  // fetch signal mask for blocking while processing
  sigprocmask(SIG_BLOCK, &mask, NULL);

  // fetch functions to deal with signals
  signal(SIGHUP, error_handler);
  signal(SIGINT, error_handler);
  // Floating point exception
  signal(SIGFPE, error_handler);
  // Invalid memory reference
  signal(SIGSEGV, error_handler);

  char a;
  cin >> a;

  // try {
  do_error(proc_arg);
  // }
  // catch(exception &x) {
  //   cout << "[SIGINT 'n SIGHUP APPEARS]" << x.what() << endl;
  //   // 2 - SIGINT
  //   kill(0, 2);
  //   // 1 - SIGHUP
  //   kill(0, 1);
  // }

  char c;
  cin >> c;

  return 0;
}
