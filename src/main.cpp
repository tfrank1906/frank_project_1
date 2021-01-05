#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <cstdlib>
#include <sys/wait.h>
#include "CLI11.hpp"

using namespace std;

void print_process()
{
  cout << "I am Prozess: " << getpid() << endl;
  cout << "parent id is " << getppid() << endl;
  cout << endl;
}
void fork_process(int n)
{
  int i = 0;

  while (i < n)
  {
    auto pid{fork()};
    if (pid == -1)
    {
      cerr << "forking failed : " << errno << endl;
      exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
      print_process();
      sleep(1);
      quick_exit(EXIT_SUCCESS);
    }
    else
    {
      int status;
      waitpid(pid, &status, 0);
    }
    i++;
  }
}

int main()
{
  cout << "main process" << endl;
  print_process();
  int i = 1;

  while (i < 3)
  {
    auto pid{fork()};
    if (pid == -1)
    {
      cerr << "forking failed : " << errno << endl;
      exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
      print_process();
      fork_process(2);
      sleep(1);
      quick_exit(EXIT_SUCCESS);
    }
    else
    {

      int status;
      waitpid(pid, &status, 0);
      //cout << "child terminated w / exit code " << status << endl;
    }
    i++;
  }
}