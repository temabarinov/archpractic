#include <algorithm>
#include <chrono>
#include <iostream>
#include <locale>
#include <mutex>
#include <ratio>
#include <thread>
#include <vector>
using namespace std;

class threads {
protected:
  vector<int> data;
  vector<int>::iterator it;
  size_t size;
  vector<int>::iterator endit;

public:
  virtual void threadsv() {}
  threads(vector<int> V)
      : data(std::move(V)), it(data.begin()), endit(data.end()),
        size(data.size()) {}
  void print() {
    for (const auto &i : data) {
      cout << i << " " << endl;
    }
  }
};

class sort2v : public threads {

public:
  using threads::threads;
  void threadsv() override {
    auto start = chrono::steady_clock::now();
    thread t1([this]() { sort(it, it + size / 2); });
    thread t2([this]() { sort(it + size / 2, endit); });
    t1.join();
    t2.join();
    inplace_merge(it, it + size / 2, endit);
    auto end = chrono::steady_clock::now();
    chrono::duration<double, milli> time = end - start;
    cout << time.count();
  }
};

class sort4v : public threads {
public:
  using threads::threads;
  void threadsv() override {
    auto start = chrono::steady_clock::now();
    thread t1([this]() { sort(it, it + size / 4); });
    thread t2([this]() { sort(it + size / 4, it + size / 2); });
    thread t3([this]() { sort(it + size / 2, it + 3 * size / 4); });
    thread t4([this]() { sort(it + 3 * size / 4, endit); });
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    inplace_merge(it, it + size / 4, it + size / 2);
    inplace_merge(it + size / 2, it + 3 * size / 4, endit);
    inplace_merge(it, it + size / 2, endit);
    auto end = chrono::steady_clock::now();
    chrono::duration<double, milli> time = end - start;
    cout << time.count();
  }
};

class sort8v : public threads {
public:
  using threads::threads;
  void threadsv() override {
    auto start = chrono::steady_clock::now();
    thread t1([this]() { sort(it, it + size / 8); });
    thread t2([this]() { sort(it + size / 8, it + size / 4); });
    thread t3([this]() { sort(it + size / 4, it + 3 * size / 8); });
    thread t4([this]() { sort(it + 3 * size / 8, it + size / 2); });
    thread t5([this]() { sort(it + size / 2, it + 5 * size / 8); });
    thread t6([this]() { sort(it + 5 * size / 8, it + 6 * size / 8); });
    thread t7([this]() { sort(it + 6 * size / 8, it + 7 * size / 8); });
    thread t8([this]() { sort(it + 7 * size / 8, endit); });
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    inplace_merge(it, it + size / 8, it + size / 4);
    inplace_merge(it + size / 4, it + 3 * size / 8, it + size / 2);
    inplace_merge(it + size / 2, it + 5 * size / 8, it + 6 * size / 8);
    inplace_merge(it + 6 * size / 8, it + 7 * size / 8, endit);
    inplace_merge(it, it + size / 4, it + size / 2);
    inplace_merge(it + size / 2, it + 6 * size / 8, endit);
    inplace_merge(it, it + size / 2, endit);
    auto end = chrono::steady_clock::now();
    chrono::duration<double, milli> time = end - start;
    cout << time.count();
  }
};

class sort16v : public threads {
public:
  using threads::threads;
  void threadsv() override {
    auto start = chrono::steady_clock::now();
    thread t1([this]() { sort(it, it + size / 16); });
    thread t2([this]() { sort(it + size / 16, it + size / 8); });
    thread t3([this]() { sort(it + size / 8, it + 3 * size / 16); });
    thread t4([this]() { sort(it + 3 * size / 16, it + size / 4); });
    thread t5([this]() { sort(it + size / 4, it + 5 * size / 16); });
    thread t6([this]() { sort(it + 5 * size / 16, it + 6 * size / 16); });
    thread t7([this]() { sort(it + 6 * size / 16, it + 7 * size / 16); });
    thread t8([this]() { sort(it + 7 * size / 16, it + 8 * size / 16); });
    thread t9([this]() { sort(it + size / 2, it + 9 * size / 16); });
    thread t10([this]() { sort(it + 9 * size / 16, it + 10 * size / 16); });
    thread t11([this]() { sort(it + 10 * size / 16, it + 11 * size / 16); });
    thread t12([this]() { sort(it + 11 * size / 16, it + 12 * size / 16); });
    thread t13([this]() { sort(it + 12 * size / 16, it + 13 * size / 16); });
    thread t14([this]() { sort(it + 13 * size / 16, it + 14 * size / 16); });
    thread t15([this]() { sort(it + 14 * size / 16, it + 15 * size / 16); });
    thread t16([this]() { sort(it + 15 * size / 16, endit); });
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();
    t11.join();
    t12.join();
    t13.join();
    t14.join();
    t15.join();
    t16.join();
    inplace_merge(it, it + size / 16, it + size / 8);
    inplace_merge(it + size / 8, it + 3 * size / 16, it + size / 4);
    inplace_merge(it + size / 4, it + 5 * size / 16, it + 6 * size / 16);
    inplace_merge(it + 6 * size / 16, it + 7 * size / 16, it + 8 * size / 16);
    inplace_merge(it + 8 * size / 16, it + 9 * size / 16, it + 10 * size / 16);
    inplace_merge(it + 10 * size / 16, it + 11 * size / 16,
                  it + 12 * size / 16);
    inplace_merge(it + 12 * size / 16, it + 13 * size / 16,
                  it + 14 * size / 16);
    inplace_merge(it + 14 * size / 16, it + 15 * size / 16, endit);
    inplace_merge(it, it + size / 8, it + size / 4);
    inplace_merge(it + size / 4, it + 6 * size / 16, it + 8 * size / 16);
    inplace_merge(it + 8 * size / 16, it + 10 * size / 16, it + 12 * size / 16);
    inplace_merge(it + 12 * size / 16, it + 14 * size / 16, endit);
    inplace_merge(it, it + size / 4, it + size / 2);
    inplace_merge(it + size / 2, it + 12 * size / 16, endit);
    inplace_merge(it, it + size / 2, endit);

    auto end = chrono::steady_clock::now();
    chrono::duration<double, milli> time = end - start;
    cout << time.count() << endl;
  }
};

int main() {

  vector<int> V{1, 2, 6, 5, 4, 8, 10, 3, 4, 5, 7, 5, 3, 2, 12, 3, 5, 6, 7, 8};
  vector<int> V1{1, 2, 6, 5, 4, 8, 10, 3, 4, 5, 7, 5, 3, 2, 12, 3, 5, 6, 7, 8};
  vector<int> V2{1, 2, 6, 5, 4, 8, 10, 3, 4, 5, 7, 5, 3, 2, 12, 3, 5, 6, 7, 8};
  vector<int> V3{1, 2, 6, 5, 4, 8, 10, 3, 4, 5, 7, 5, 3, 2, 12, 3, 5, 6, 7, 8};
  vector<threads *> Vf;
  sort2v s2(V);
  sort4v s4(V1);
  sort4v s8(V2);
  sort4v s16(V3);
  Vf.push_back(&s2);
  Vf.push_back(&s4);
  Vf.push_back(&s8);
  Vf.push_back(&s16);

  cout << "2 potoka \t\t 4 potoka \t\t 8 potokov \t\t 16 potokov" << endl;
  Vf[0]->threadsv();
  cout << " \t\t ";
  Vf[1]->threadsv();
  cout << " \t\t ";
  Vf[2]->threadsv();
  cout << " \t\t ";
  Vf[3]->threadsv();

  return 0;
}