#include <iostream>
#include <thread>
#include <mutex>
 
std::mutex mutex1, mutex2;
 
void ThreadA()
{
    // Creates deadlock problem
    std::lock_guard<std::mutex> lck2(mutex2);
    std::cout << "Thread A" << std::endl;
    std::lock_guard<std::mutex> lck1(mutex1);

    
}
 
void ThreadB()
{
    // Creates deadlock problem
    std::lock_guard<std::mutex> lck1(mutex1);
    std::cout << "Thread B" << std::endl;
    std::lock_guard<std::mutex> lck2(mutex2);

}
 
void ExecuteThreads()
{
    std::thread t1( ThreadA );
    std::thread t2( ThreadB );
 
    t1.join();
    t2.join();
 
    std::cout << "Finished" << std::endl;
}
 
int main()
{
    ExecuteThreads();
 
    return 0;
}