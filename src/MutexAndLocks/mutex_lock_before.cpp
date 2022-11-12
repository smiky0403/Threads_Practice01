#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <algorithm>

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
        std::cout << "#Veh = " << _tempVeh <<std::endl;
    }

    void pushBack(Vehicle &&v){
        int oldNum = _tempVeh;
        std::this_thread::sleep_for(std::chrono::microseconds(10));
        _tempVeh = oldNum + 1;
    }
private:
    std::vector<Vehicle> _vehicles;
    int _tempVeh;

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