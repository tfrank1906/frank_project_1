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
  cout << signal << endl;
 
  if (children.size() > 0){
    //cout << "muss noch eine ebene tiefer gehen!" << endl;
    //cout << "ausgabe: " << children.size() << endl;
    for(size_t c = 0; c < children.size(); c++){
      cout << "kille : " << children[c] << endl;
      int success = kill(children[c], SIGKILL);
      cout << success << endl;
      
    }
  }
  
    cout << "kille nun: " << getpid() << endl;
    
    quick_exit(EXIT_SUCCESS);
    
}

void print_process(){

  cout << "I am Prozess: " << getpid() << endl;
  cout << "Parent id is : " << getppid() << endl;
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

int main(int argc, char **argv) {
  signal(SIGTERM, signalHandler);
 
  CLI::App app{"Process Tree, project_1"};

  int n;
  int m;

  app.add_option("children", n, "Number of children");
  app.add_option("leaves", m, "Number of leaves");
  CLI11_PARSE(app, argc, argv);

  cout << "main process" << endl;
  print_process();

  fork_process(n, m, 0);

}