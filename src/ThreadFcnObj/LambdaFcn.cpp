#include <iostream>

int main()
{
    int id = 0;
    double x = 3.5;

    id++; x+=1; // capture list[...] take value when it's been declared, parameter (...) or capture list[&...] takes values when it's been used
    auto f1 = [id](double x){
        std::cout<<"a) ID = " << id << "; " <<"Parameter = "<< ++x<< "; " << std::endl;};
   

    
    id++;  id++;  id++;  id++;  x+=1;
    auto f2 = [id](double &x) mutable {
        std::cout<<"b) ID = " << ++id << "; " <<"Parameter = "<< ++x << "; " << std::endl;};


    id++;  id++;  id++;  id++; x+=1;
    auto f3 = [&id](double x){
        std::cout<<"d) ID = " << ++id << "; " <<"Parameter = "<< ++x << "; " << std::endl;};



    f1(x);
    std::cout<<"a) Main: ID = " << id << "; " <<"Parameter = "<< x << "; " << std::endl;
    f2(x);
    std::cout<<"b) Main: ID = " << id << "; " <<"Parameter = "<< x << "; " << std::endl;
    f3(x);
    std::cout<<"c) Main: ID = " << id << "; " <<"Parameter = "<< x << "; " << std::endl;


    //extra test
   
    auto f4 = [&id](const double x) {
    std::cout<<"d) ID = " << id++ << "; " <<"Parameter = "<< x << "; " << std::endl;};
    id+=10; x+=10;
    f4(x++);
    std::cout<<"d) Main: ID = " << id << "; " <<"Parameter = "<< x << "; " << std::endl;    

    return 0;
}