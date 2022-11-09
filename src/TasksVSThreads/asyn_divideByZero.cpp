#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <memory>

double divideByZero(double num, double denom){
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    if(denom == 0){
        throw std::runtime_error ("Exception from thread: Division by zero! -------");
    }
    return num/denom;
}

int main(){
    double num = 42.0, denom = 0.0;
    std::future<double> ftr = std::async(divideByZero, num, denom);

    try
    {
        double result = ftr.get();
        std::cout <<"Result = " << result << std::endl;
    }
    catch(const std::runtime_error e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}