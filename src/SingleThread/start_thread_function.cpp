#include <iostream>
#include <thread>

using std::thread;

void threadFcn(){
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "Finished work in Thread Fcn\n";
}

int main(){

    thread t(threadFcn);
    std::cout<< "Finished work in Main\n"; 

    //t.join(); //without it, main thread will excuted terminate, leaving thread t unfinished

    return 0;
}