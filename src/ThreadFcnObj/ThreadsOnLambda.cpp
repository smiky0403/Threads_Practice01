#include <iostream>
#include <thread>

int main(){
    int id = 0;

    auto f0 = [&id](){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "a) ID in threads by reference = " << id << std::endl;
    };

    std::thread t1(f0);
    std::thread t2([id](){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "b) ID in threads by value = " << id << std::endl;        
    });

    ++id;
    std::cout <<"c) ID in Main by value = " << id << std::endl;       

    //std::thread t2
     ++id;
     ++id;
    t1.join();
    t2.join();


}