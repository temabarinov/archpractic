#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

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
  cout << "aaa";
  int x = 5;
  for (int i = 0; i < 10; i++) {
    thread t1(client, ref(x));
    thread t2(operator_, ref(x));
    t1.join();
    t2.join();
  }
  return 0;
}