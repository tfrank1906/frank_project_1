#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <cstdlib>
#include <sys/wait.h>
#include <csignal>
#include <vector>
#include <signal.h>
#include <csignal>
#include "CLI11.hpp"

using namespace std;

int cnt1 = 1;
int cnt2 = 1;
vector<pid_t> children;



void signalHandler(int signal) {

 if(signal == 15){
  if (children.size() > 0){
    for(size_t c = 0; c < children.size(); c++){
      cout << "killíng : " << children[c] << endl;
      kill(children[c], SIGKILL);
    }
  }
  cout << "killing now: " << getpid() << endl;
  quick_exit(EXIT_SUCCESS);
    
  } else {
    cout << "Got bad signal!" << endl;
  }
}

void print_process(){

  cout << "I am Prozess  : " << getpid() << endl;
  cout << "Id from my is : " << getppid() << endl;
  cout << endl;

}

void fork_process(int n, int m, int depth) {
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
        sleep(50);
      }
      else {
        children.push_back(pid);
      }
      sleep(1);
      i++;
    }
    sleep(2);
    int status;
    for (size_t k = 0; k < children.size(); k++) {
      kill(children[k], SIGTERM);
      waitpid(children[k], &status, 0);  
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
        sleep(50);
      }
      else {
        children.push_back(pid);
      }
      i++;
    }
    sleep(1);
  }
  else
  {
    return;
  }
}

void fork_process_auto(int n, int m, int depth){
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
        fork_process_auto(n, m, depth + 1);
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
        quick_exit(EXIT_SUCCESS);
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


int main(int argc, char **argv) {
  signal(SIGTERM, signalHandler);
 
  CLI::App app{"Process Tree, project_1"};

  int n;
  int m;
  bool signalBool;

  app.add_option("children", n, "Number of children");
  app.add_option("leaves", m, "Number of leaves");
  app.add_flag("--killsignal, --k", signalBool, "kill leaves with signal");

  CLI11_PARSE(app, argc, argv);

  cout << "main process" << endl;
  print_process();

  if(signalBool){
    fork_process(n, m, 0);
  } else {
    fork_process_auto(2, 2, 0);
  }
  

}