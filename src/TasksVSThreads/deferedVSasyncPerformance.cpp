#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <vector>
#include <chrono>

void workerFunction(int n){

    std::cout << "Worker thread id = " << std::this_thread::get_id() << std::endl;
    for(int i =0; i < n; i++){
        sqrt(12345.6789);
    }
}

int main(){

     std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

     std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

     std::vector<std::future<void>> futures;

     //int nloops = 1e7;//compare
     int nloops = 10; //compare

     int nThreads = 4;

     for(int i = 0; i < nThreads; i++){
        futures.emplace_back(std::async(std::launch::async, workerFunction, nloops)); //compare
        //futures.emplace_back(std::async(std::launch::deferred, workerFunction, nloops)); //compare
     }
     
     for(auto & ftr : futures){
        ftr.wait();
     }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Execution finished after " << duration <<" microseconds" << std::endl;

    return 0;


}