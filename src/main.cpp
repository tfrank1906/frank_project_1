#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <cstdlib>
#include <sys/wait.h>
#include <csignal>
#include <vector>
#include "CLI11.hpp"

using namespace std;


int cnt1 = 1;
int cnt2 = 1;
void print_process(){
  cout << "I am Prozess: " << getpid() << endl;
  cout << "Parent id is : " << getppid() << endl;
  cout << endl;
}
void fork_process(int n, int m, int depth){
  int i = 0;
  if (depth == 0) {
    while (i < n) {
      auto pid{fork()};
      if (pid == -1) {
        cerr << "forking failed : " << errno << endl;
        exit(EXIT_FAILURE);
      }
      if (pid == 0) {
        cnt1 += i;
        cout << cnt1 << endl;
        print_process();
        fork_process(n, m, depth + 1);
        quick_exit(EXIT_SUCCESS);
      } else {
        int status;
        waitpid(pid, &status, 0);
      }
      i++;
    }
  }
  else if (depth == 1) {
   
    while (i < m) {
      auto pid{fork()};
      if (pid == -1) {
        cerr << "forking failed : " << errno << endl;
        exit(EXIT_FAILURE);
      }
      if (pid == 0) {
        cnt2 += i;
        cout << cnt1 << "." << cnt2 << endl;
        print_process();
        fork_process(n, m, depth + 1);
        //quick_exit(EXIT_SUCCESS);
      } else {
        int status;
        waitpid(pid, &status, 0);
      }
      i++;
    }
  } else {
    return;
  }
}

int main(int argc, char** argv) {
  CLI::App app{"Process Tree, project_1"};

  int n;
  int m;

  app.add_option("children", n, "Number of children");
  app.add_option("leaves", m, "Number of leaves");
  CLI11_PARSE(app, argc, argv);

 

 
  cout << "main process" << endl;
  print_process();
  fork_process(n, m, 0);

  sleep(2);

}