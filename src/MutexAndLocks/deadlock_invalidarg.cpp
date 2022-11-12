#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <algorithm>

std::mutex mtx; //
double result;

void printResult(int denom){
    std::cout << "for denom = " << denom << ", result = " << result <<std::endl;
}

void divideByNumber(double num, double denom){
    mtx.lock(); //
    try{

        if (denom != 0 ){
            result = num/denom;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            printResult(denom);

        }else{
            throw std::invalid_argument("Exception by 0!");
        }


    }catch(const std::invalid_argument &e ){
        std::cout << e.what()<<std::endl;
        return;
    }
    mtx.unlock(); //
}

int main(){

    std::vector<std::future<void>> ftrs;
    for(double i = -5; i <= 5; i++){
        ftrs.emplace_back(std::async(std::launch::async, 
        divideByNumber, 50.0, i));
    }

    std::for_each(ftrs.begin(), ftrs.end(), [](std::future<void> &ftr){
        ftr.wait();
    }
    );

    return 0;
}