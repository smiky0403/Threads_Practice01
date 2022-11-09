#include <iostream>
#include <thread>
#include <future>
#include <cmath>
//#include <memory>

double divideByNumber(double num, double denom){

    std::cout << "Worker thread id = "<<std::this_thread::get_id()<<std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(2));

    if(denom == 0){
        throw std::runtime_error("Exception from thread#: Division by zero!");

    }
    return num /denom;
}

int main(){
    std::cout << "Main thread id = "<<std::this_thread::get_id()<<std::endl;
    double num = 42.0, denom = 0.0;

    //std::future<double> ftr = std::async(std::launch::deferred, divideByNumber, num, denom);  //compare
    std::future<double> ftr = std::async(std::launch::async, divideByNumber, num, denom);  //compare
    //std::future<double> ftr = std::async(divideByNumber, num, denom);  //compare


    try
    {
        double result = ftr.get();
        std::cout << "Result = "<< result << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;


}