#include <iostream>
#include <thread>

int main(){

    unsigned int nThreads = std::thread::hardware_concurrency();

    std::cout << "This machine support concurrency with "<<nThreads << " threads available"<<std::endl;

    return 0;
}