#include <iostream>
#include <thread>

class Vehicle {
    public:
        Vehicle(int id): _id(id){
           // std::this_thread::sleep_for(std::chrono::seconds(id*0.1)); //can't do it on constructor
        }
        void operator()(){
            std::cout << "Vehicle Object has been created: " <<"id = "<< _id<< std::endl;
        }
    private:
        int _id;
};

int main(){

    //std::thread t0(Vehicle(ax)); //vexing parsings - can't compile

    //three way to force compile think as a variable definition for variable t of class std::thread
    int a1 = 1, a2 = 2, a3 =3;
    std::thread t1((Vehicle(a1)));//force parenthesis
    std::thread t2 = std::thread(Vehicle(a2));//copy initialization
    std::thread t3{Vehicle(a3)}; //uniform initialization with braces

    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Work in Main Finished"<< std::endl;

    //t0.join();  //can't compile
    t1.join();
    t2.join();
    t3.join();

    return 0;


}