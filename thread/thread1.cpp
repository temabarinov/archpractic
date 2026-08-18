#include <Wt/Dbo/Dbo.h>
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <variant>
using namespace std;
using namespace std::chrono_literals;

once_flag flag;
mutex m;
void client(int &x) {
  lock_guard<mutex> lock(m);
  if (x < 10) {
    x++;
    cout << x << endl;
    this_thread::sleep_for(1s);
  }
}
void operator_(int &x) {
  x--;
  cout << x << endl;
  this_thread::sleep_for(2s);
}

int main() {
  for (std::string line; std::getline(std::cin, line);) { // get the line
    int xyl[3];
    int i = 0;
    int start = 0;
    int indx = 0;
    xyl[2] = 0;
    while (i <= line.size()) {
      std::string temp = line;

      if (line[i] == ' ') {
        xyl[indx] = std::stoi(temp.substr(start, i - start));

        start = i + 1;
        indx++;
      }
      if (indx == 2) {
        temp = line;
        xyl[2] = std::stoi(temp.substr(i + 1, temp.size() - 1 - i));
        break;
      }
      i++;
    }

    int gip = (xyl[0] * xyl[0] + xyl[1] * xyl[1]);
    if (xyl[0] <= xyl[1]) {
      std::cout << '1' << std::endl;
      return 0;
    }
    if (xyl[0] > xyl[1]) {
      if (gip <= (xyl[2] * xyl[2])) {
        std::cout << '2' << std::endl;
        return 0;
      } else {
        if (xyl[0] <= (xyl[1] + (gip - xyl[2] * xyl[2]))) {
          std::cout << '1' << std::endl;
          return 0;

        } else {
          std::cout << '2' << std::endl;
          return 0;
        }
      }
    }
  }
  return 0;
}
