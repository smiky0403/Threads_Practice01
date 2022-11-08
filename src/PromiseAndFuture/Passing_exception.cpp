#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <memory>

void divideByNumber(std::promise<double> && prms, double num, double denom){

    std::this_thread::sleep_for(std::chrono::seconds(1));
    try
    {
        if(denom == 0){
            throw std::runtime_error("Divide by 0 -----!");
        }else{
            prms.set_value( num/ denom );
        }
    }
    catch(const std::exception& e){
        //std::cerr << e.what() << '\n';
        prms.set_exception(std::current_exception());
    }
    
}

int main(){

    std::promise<double> prms;
    std::future<double> ftr = prms.get_future();

    double num = 42.0, denom = 0.0;
    std::thread t(divideByNumber, std::move(prms), num, denom);

    try
    {
        double result = ftr.get();
        std::cout << "Result = " <<result <<std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    t.join();

}