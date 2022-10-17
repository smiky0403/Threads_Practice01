#include <iostream>
#include <thread>

using std::thread;

void threadFcn(){
    std::this_thread::sleep_for(std::chrono::microseconds(50000));
    std::cout<< "Finished work in Thread\n";
}

//Extra note from youtube:https://www.youtube.com/watch?v=q3-5sDe6lzg
void run(int count){
    while((count --)> 0){
        std::cout <<"CppNuts： " << count <<std::endl; 
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}


int main(){
    //---------t1-------------------
    thread t1(threadFcn);
    std::cout<<"Start work t1 in main\n";

    t1.detach();
   
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"Finished work t1 in main\n";

    //-----------t2-----------------
    std::cout<<"Start work t2 in main\n";
    thread t2(run, 10);

    t2.detach(); //toggle this line to see the difference

    if(t2.joinable())  //can't join twice
        t2.join();
    else
        std::cout <<"t2 already joined or not joinable"<<std::endl;

    std::cout << "main () after t2"<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5500));
    std::cout<<"Finished work t2 in main\n";

    return 0;
}