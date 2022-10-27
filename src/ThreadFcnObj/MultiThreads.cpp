#include <iostream>
#include <thread>
#include <vector>


void printHello(){
    std::cout << "Hello from thread #" << std::this_thread::get_id() << std::endl; 
}

int main(){
    //Sec 1, Multi threads
    std::vector<std::thread> threads;

    for(size_t i = 0; i < 5; ++i){

        // std::thread t(printHello);
        // threads.emplace_back(t);  //not working

        //threads.push_back(std::thread(printHello)); //also works
        
        threads.emplace_back(std::thread(printHello));
    }


    std::cout << "Hello from Main thread #"<< std::this_thread::get_id() << std::endl; 

    for(auto& t: threads)
        t.join();


    //Sec 2 First Concurrency Bug
    std::vector<std::thread> threads1;
    for(size_t i=0; i < 10; ++i){
        threads1.emplace_back(
            [i]({    //must pass by value, cannot use &i 
                std::this_thread::sleep_for(std::chrono::seconds(i));
                std::cout << "Hello from thread # "<< i << std::endl; 
            }
       );
    }

    for(auto& t: threads1)
        t.join();

    return 0;
}