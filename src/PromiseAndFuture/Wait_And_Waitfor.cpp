#include <iostream>
#include <thread>
#include <future>
#include <cmath>

void computeSqrt(std::promise<double> && prms, double input){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    double output = sqrt(input);
    prms.set_value(output);
}

int main(){
    double inputData = 42.0;

    std::promise<double> prms;
    std::future<double> ftr = prms.get_future();

    std::thread t(computeSqrt, std::move(prms), inputData);
    auto status = ftr.wait_for(std::chrono::seconds(4));

    if(status == std::future_status::ready){
         std::cout << "Result is ready, value is: " << ftr.get() << std::endl;
    }

    if(status == std::future_status::timeout){
         std::cout << "Result is timeout " << ftr.get() << std::endl;
    }

    if(status == std::future_status::deferred){
         std::cout << "Result is deferred " << ftr.get() << std::endl;
    }

    t.join();

    return 0;
}