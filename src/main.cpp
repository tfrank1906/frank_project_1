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



void signalHandler(int signal){
  cout << "signal erhalten " << signal << endl;

    quick_exit(EXIT_SUCCESS);
}

void kill_helper(pid_t pid, int depth){
  if(depth == 0){
    int success = kill(pid, SIGTERM);
    if(success == 0){
      cout << "Kind " << pid << " wurde getötet!" << endl; 
    } else {
      cout << "Kind konnte nicht getötet werden." << endl;
    }
  }  else if (depth == 1){
    int success = kill(pid, SIGTERM);
    //cout << success << endl;
    if(success == 0){
      cout << "Blatt " << pid << " wurde getötet!" << endl; 



  }
}
}
void print_process(){
  cout << "I am Prozess: " << getpid() << endl;
  cout << "Parent id is : " << getppid() << endl;
  cout << endl;
}
void fork_process(int n, int m, int depth){

  vector<pid_t> children;
  vector<pid_t> leaves;
  
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
        sleep(5);
        //quick_exit(EXIT_SUCCESS);
      } else { 
        children.push_back(pid);
        /*
        int status;
      
        waitpid(pid, &status, 0);
        */
      }
      
      i++;
    }
    //main Prozess nach dem alle Prozesse erstellt wurden
    int status;
    sleep(2);
    for(size_t k = 0; k < children.size(); k++){
     
      kill_helper(children[k], depth);
      cout << children[k] << endl;
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
        //quick_exit(EXIT_SUCCESS);
      } else {
        /*
        int status;
        waitpid(pid, &status, 0);
        */
        leaves.push_back(pid);
      }
      i++;
      
    }

/*
    for(size_t k = 0; k < leaves.size(); k++){
      //kill_helper(leaves[k], depth);
      cout << leaves[k] << endl;
      waitpid(leaves[k], &status, 0);
    }
    */
  } else {
    return;
  }
}

int main(int argc, char** argv) {
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
  /*
  sleep(2);
  cout << children.size() << endl;
  for(size_t c = 0; c < children.size(); c++){
    cout << children.size() << endl;
    cout << children[c] << endl;
  }
  int pid;
  cout << "pid: ";
  cin >> pid;

  kill(pid, SIGKILL);
  */




}