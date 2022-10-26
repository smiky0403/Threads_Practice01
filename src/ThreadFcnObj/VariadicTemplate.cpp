#include <iostream>
#include <thread>
#include <string>

void printID(int id){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "ID = "<< id <<std::endl;
}

void printIDandName(int id, std::string name){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "ID = "<< id << ", name = "<< name <<std::endl;
}

int main(){
    int id = 5;
    std::thread t1(printID, id);
    std::thread t2(printIDandName, ++id, "Mystring");

    t1.join();
    t2.join();
    //std::this_thread::sleep_for(std::chrono::seconds(3));

}