#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <cstdlib>
#include <sys/wait.h>
#include <csignal>
#include <vector>
#include <signal.h>
#include <csignal>
#include "fmt/core.h"
#include "fmt/format.h"
#include "fmt/format-inl.h"
#include "format.cc"
#include "fmt/color.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "CLI11.hpp"



using namespace std;

int cnt1 = 1;
int cnt2 = 1;
vector<pid_t> children;

void signalHandler(int signal) {

 if(signal == 15){
  if (children.size() > 0){
    for(size_t c = 0; c < children.size(); c++){
      fmt::print(fg(fmt::color::green), "Process {1} here, got Signal, delegating it to leaf {0} \n \n", children[c], getpid());
      kill(children[c], SIGKILL);
      fmt::print(fg(fmt::color::red), "{} killed because of signal \n \n", children[c]);
    }
  }
  fmt::print(fg(fmt::color::gold), "Finished killing leaves per signal. \n");
  fmt::print(fg(fmt::color::red), "-> Now killing child {} \n \n \n", getpid());
  quick_exit(EXIT_SUCCESS);
    
  } else {
    cout << "Got bad signal!" << endl;
    return;
  }
}

void print_process(){
  fmt::print(fg(fmt::color::gray), "I am Process:         {} \n", getpid());
  fmt::print(fg(fmt::color::gray), "Id from my parent is: {} \n ", getppid());
  
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
        fmt::print(fg(fmt::color::red), "{0} \n", cnt1);
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
    fmt::print(fg(fmt::color::gold), "Finished creating tree. \n \n \n");
    int status;
    for (size_t k = 0; k < children.size(); k++) {
      fmt::print(fg(fmt::color::light_blue), "Sending Signal to: {0}", children[k]);
      cout << endl;
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
        fmt::print(fg(fmt::color::red), "{0}.{1} \n", cnt1, cnt2);
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
  bool logBool;

  app.add_option("children", n, "Number of children")->check(CLI::PositiveNumber);
  app.add_option("leaves", m, "Number of leaves")->check(CLI::PositiveNumber);
  app.add_flag("--killsignal, --k", signalBool, "kill leaves with signal");
  app.add_flag("--log, --l", logBool, "create a log");

  CLI11_PARSE(app, argc, argv);

   if(logBool){
    try {
     auto logger = spdlog::basic_logger_mt("processTree_logger", "logs/log_processTree.txt");
     fmt::print(fg(fmt::color::light_blue), "Writing logs... \n");
    }
    catch (const spdlog::spdlog_ex &ex){
     std::cout << "Log init failes: " << ex.what() << endl;
   }
  } else {
    fmt::print(fg(fmt::color::light_blue), "Writing NO logs... \n");
  }

  fmt::print("\nStart building process tree with {0} children and {1} leaves: \n\n", n, m);
  fmt::print(fg(fmt::color::red), "Main Process \n");
  print_process();

 
  if(signalBool){
    fork_process(n, m, 0);
  } else {
    fork_process_auto(n, m, 0);
  }


}