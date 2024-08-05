//利用 RALL 过程等待线程完结
#include <chrono>
#include <thread>
#include <iostream>
class thread_guard
{
    std::thread& t;
    public:
    explicit thread_guard(std::thread& t_): t(t_){}
    ~thread_guard()
    {
        if (t.joinable()) {
            // t.join();
            t.detach();// 引发未定义行为
        }
    }
    thread_guard(thread_guard const &) = delete;
    thread_guard operator=(thread_guard const &)=delete;
};
void change_i(int &i)
{
    i++;
    std::cout << i << std::endl;
}
struct func{
    int &i;
    func (int& i_):i(i_){}
    void operator() ()
    {
        for (int j=0; j<1000000; j++) {
            // std::this_thread::sleep_for(std::chrono::nanoseconds(1));
            change_i(i);
        }
    }
};
int main()
{   
    int local_state = 0;
    func my_func(local_state);
    std::thread my_thread(my_func);
    thread_guard g(my_thread);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}