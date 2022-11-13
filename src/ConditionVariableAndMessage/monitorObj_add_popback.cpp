#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <algorithm>

class Vehicle
{
public:
    Vehicle(int id) : _id(id) {}
    int getID() { return _id; }

private:
    int _id;
};


class WaitingVehicle{

public:
    WaitingVehicle(){}

    int getNumVeh() 
    { 
        std::lock_guard<std::mutex> uLock(_mutex);
        return _numVeh; 
    }

    bool dataIsAvailable(){
        std::lock_guard<std::mutex> mylock(_mutex);
        return !_vehicles.empty();
    }

    Vehicle popBack(){
        std::lock_guard<std::mutex> ulock(_mutex);
        Vehicle v = std::move(_vehicles.back());
        _vehicles.pop_back();
        --_numVeh;
        return v;
    }


    // void printIDs(){
    //     std::lock_guard<std::mutex> mylock(_mutex);
    //     for(auto v: _vehicles){
    //         std::cout << "   Vehicle #" << v.getID() << " is now waiting in the queue" << std::endl;
    //         std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    //     }

    // }

    void pushBack(Vehicle && v){
        std::lock_guard<std::mutex> ulock(_mutex);
        std::cout << "   Vehicle #" << v.getID() << " will be added to the queue" << std::endl; 
        _vehicles.emplace_back(std::move(v));

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        ++_numVeh;
    }

private:
    std::vector<Vehicle> _vehicles;
    std::mutex _mutex;
    int _numVeh;
};


int main(){
    std::shared_ptr<WaitingVehicle> queue(new WaitingVehicle);
    //std::weak_ptr<WaitingVehicle> queue(new WaitingVehicle);


    std::cout <<"Spawning threads ..."<<std::endl;
    std::vector<std::future<void>> futures;

    for(int i = 0; i < 10; i++){
        Vehicle v(i);
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicle::pushBack, queue, std::move(v)));
    }


      
    std::cout << "Collecting result ..." << std::endl;
    //queue ->printIDs();

    while(true){
        if(queue->dataIsAvailable()){
            Vehicle v = queue->popBack();
              std::cout << "   Vehicle #" << v.getID() << " has been removed from the queue" << std::endl;

            if(queue->getNumVeh()<=0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                break;
            }              
        }
    }

    std::for_each(futures.begin(),futures.end(), [](std::future<void> &ftr){
        ftr.wait();
        }
    );

     std::cout << "Finished processing queue" << std::endl;
     std::cout << "Finished : " << queue->getNumVeh() << " vehicle(s) left in the queue" << std::endl;


     return 0;

}