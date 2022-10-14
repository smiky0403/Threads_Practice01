#include <iostream>
#include <thread>

void threadFcn(){
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout<<"Finished work in thread 1\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout<<"Finished work in thread 2\n";
}


int main(){

    std::thread t(threadFcn);
    //t.join();  //add gere to wait for only thread to get finished then main start 

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout<<"Finished work in main 1\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout<<"Finished work in main 2\n";

    t.join();

}