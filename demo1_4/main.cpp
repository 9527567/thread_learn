#include <chrono>
#include <exception>
#include <iostream>
#include <thread>
#include <ctime>
void hello(std::string input) {
for (int i=0; i<100; i++) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(2000000));
}
     std::cout << input << std::endl; }
int main() {
  std::thread t1(hello, std::string("hello world 1"));
  std::thread t2(hello, std::string("hello world 2"));

  t1.detach();
  t2.detach();
}