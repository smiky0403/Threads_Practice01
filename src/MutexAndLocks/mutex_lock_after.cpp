#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <algorithm>

#include <mutex>  //after

class Vehicle{

public: 
    Vehicle(int id):_id(id){}

private:
    int _id;
};

class WaitingVehicles{

public:
    WaitingVehicles(): _tempVeh(0){}

    void printSize(){
        _mutex.lock();//after
        std::cout << "#Veh = " << _tempVeh <<std::endl;
        _mutex.unlock();//after
    }

    void pushBack(Vehicle &&v){

         _mutex.lock();//after
        int oldNum = _tempVeh;
        std::this_thread::sleep_for(std::chrono::microseconds(10));
        _tempVeh = oldNum + 1;
        _mutex.unlock();//after
    }
private:
    std::vector<Vehicle> _vehicles;
    int _tempVeh;

    std::mutex _mutex; //after

};

int main(){
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
    std::vector<std::future<void>> ftrs;

    for(int i = 0; i < 1e3; i++){
        Vehicle v(i);
        ftrs.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, 
        queue, std::move(v)));
    }

    std::for_each(ftrs.begin(), ftrs.end(), [](std::future<void> &ftr){
        ftr.wait();
    }    
    );

    queue->printSize();

}