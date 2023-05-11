#include<iostream>
#include"sha256.h"

int main()
{   
    std::cout<<"Welcome to SHA-256 Hash Generator!\n"<<endl;

    std::cout<<"Enter the message : ";
    string inputString ;
    std:: cin>>inputString;

    std:: cout<<"SHA-256 hash : "<<Hash(inputString)<<endl;
    std::cout<<"Hash computed successfully!"<<endl;
}