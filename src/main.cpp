#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <cstdlib>
#include <sys/wait.h>
#include "CLI11.hpp"

using namespace std;

void print_process() {
  cout << "I am Prozess: " << getpid() << endl;
  cout << "parent id is " << getppid() << endl;
  cout << endl;
}
void fork_process(int n, int m, int depth)
{
  int t = 0;
  int i = 0;
  if (depth == 0) {
    t = n;
  } else if (depth == 1) {
    t = m;
  } else {
    return;
  }
  
  while (i < t) {
    auto pid{fork()};
    if (pid == -1) {
      cerr << "forking failed : " << errno << endl;
      exit(EXIT_FAILURE);
    }
    if (pid == 0) {
      print_process();
      fork_process(n, m, depth + 1);
      sleep(1);
      quick_exit(EXIT_SUCCESS);
    } else  {
      int status;
      waitpid(pid, &status, 0);
    } i++;
  }
}

int main() {
  cout << "main process" << endl;
  print_process();
  fork_process(2, 3, 0);
}