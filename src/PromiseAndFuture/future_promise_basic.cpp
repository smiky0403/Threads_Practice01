#include <iostream>
#include <thread>
#include <future>

void printMessage(std::string message)
{
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    std::cout << "Thread 1:" << message << std::endl;
}

void modifyMessage(std::promise<std::string> && promise01, std::string message01){
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::string modifiedMessage = message01 + " has been modified\n";
    promise01.set_value(modifiedMessage);
}

int main(){

    //page 4 - 1
    std::string message = "My Message 01";

    std::thread t1(printMessage, message);

    std::thread t2([message](){
        std::this_thread::sleep_for(std::chrono::microseconds(10));
         std::cout << "Thread 2:" << message << std::endl;
        }
    );

    t1.join();
    t2.join();

    //page 4 - 2

    std::promise<std::string> prms;
    std::future<std::string> ftr;
    ftr = prms.get_future();

    std::string messageToThread = "My Message 02";
    std::thread t3(modifyMessage, std::move(prms),  messageToThread);
    

    std::cout << "Original message from main(): " << messageToThread << std::endl;
    std::string messageFromThread = ftr.get();  // this will wait
    std::cout << "Original message from main(): " << messageFromThread << std::endl;
    t3.join();

    return 0;
}