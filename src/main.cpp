#include <iostream> 
#include <unistd.h>
#include <cerrno>    
#include <cstdlib>   
#include <sys/wait.h>
using namespace std;
int main(){
  auto pid{fork()};
  if (pid == -1){
    cerr << "forking failed : " << errno << endl;
    exit(EXIT_FAILURE);
  }

  if (pid == 0){
    cout << "child process here !"<< endl;
    cout << "child pid is " << getpid() << endl;
    cout << "parent id is " << getppid() << endl;
    sleep(3);
    quick_exit(EXIT_SUCCESS);
  } else {
    cout << "child pid is " << pid << endl;
    cout << "waiting for child..." << endl;
    int status;
    waitpid(pid, &status, 0); // 0...options
    cout << "child terminated w / exit code " << status << endl;
    exit(EXIT_SUCCESS);
  }
} 