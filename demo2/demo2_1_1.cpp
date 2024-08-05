#include <chrono>
#include <iostream>
#include <thread>
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
void oops()
{
    int local_state = 0;
    func my_func(local_state);
    std::thread my_thread(my_func);
    my_thread.detach();
}
int main()
{
    oops();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}