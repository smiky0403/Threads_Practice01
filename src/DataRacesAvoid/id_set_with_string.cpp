#include <iostream>
#include <thread>
#include <future>

class Vehicle{
public:
    Vehicle() : _id(0), _name(new std::string("Default Name")){
        std::cout << "Vehicle # " << _id << " Default constructor called" << std::endl;
    }
    Vehicle(int id, std::string name): _id(id), _name(new std::string(name)) {
        std::cout << "Vehicle #" << _id << " Initializing constructor called" << std::endl;
    }

    void setID(int id) { _id = id; }
    int getID() { return _id; }
    void setName(std::string name) { *_name = name; }
    std::string getName() { return *_name; }

    //copy constructor
    Vehicle(Vehicle const &src){
        _id = src._id;
        if(src._name != nullptr){
            _name = new std::string;
            *_name = *src._name;
        }
        std::cout << "Vehicle #" << _id << " copy constructor called" << std::endl;
    };

    Vehicle(Vehicle && src){
        _id = src.getID();
        _name = new std::string(src.getName());

        src.setID(0);
        src.setName("Default Name");

        std::cout << "Vehicle #" << _id << " move constructor called" << std::endl;
    };

private:
    int _id;
    std::string *_name;
};

int main(){

    Vehicle v0;
    Vehicle v1(1, "Vehicle 1");
    std::cout <<"0"<<std::endl;
    std::future<void> ftr = std::async(
        [](Vehicle v){
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work
            v.setName("Vehicle 2");
        },

    //v0//compare
    std::move(v0)//compare
    );

    std::cout <<"1"<<std::endl;
    v0.setName("Vehicle 3");
    std::cout <<"2"<<std::endl;

    //ftr.wait(); //compare
    ftr.wait(); //compare
    
    std::cout <<"3"<<std::endl;
    std::cout <<v0.getName() <<std::endl;
    std::cout <<"4"<<std::endl;

    return 0;

}