include <iostream>
#include <unistd.h>	#include <unistd.h>
#include <cerrno>    	#include <cerrno>
#include <cstdlib>   	#include <cstdlib>
#include <sys/wait.h>	#include <sys/wait.h>
#include "CLI11.hpp"

using namespace std;	using namespace std;
int main(){	
  auto pid{fork()};	int main()
  if (pid == -1){	{
    cerr << "forking failed : " << errno << endl;	  int i = 1;
    exit(EXIT_FAILURE);	  while (i < 5)
  }	  {


  if (pid == 0){	    auto pid{fork()};
    cout << "child process here !"<< endl;	    if (pid == -1)
    cout << "child pid is " << getpid() << endl;	    {
    cout << "parent id is " << getppid() << endl;	      cerr << "forking failed : " << errno << endl;
    sleep(3);	      exit(EXIT_FAILURE);
    quick_exit(EXIT_SUCCESS);	    }
  } else {	
    cout << "child pid is " << pid << endl;	    if (pid == 0)
    cout << "waiting for child..." << endl;	    {
    int status;	      cout << "I am Prozess: "<< i << endl;
    waitpid(pid, &status, 0); // 0...options	      cout << "parent id is " << getppid() << endl;
    cout << "child terminated w / exit code " << status << endl;	      sleep(3);
    exit(EXIT_SUCCESS);	      quick_exit(EXIT_SUCCESS);
    }
    else
    {
      cout << "child pid is " << pid << endl;
      int status;
      waitpid(pid, &status, 0);
      cout << "child terminated w / exit code " << status << endl;

    }
    i++;
  }	  }
} 	} 