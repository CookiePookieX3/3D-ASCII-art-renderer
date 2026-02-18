#include <iostream>


int main(){

    char arr[] = {'$','8','W','@','H','9','Z','4','{','r','[','(','/','!','"',' '};

    for(int i = 0; i<60; i++){
        for(int j = 0; j<16; j++){
            for(int a = 0; a<12; a++){
                std::cout << arr[j];
            }
        }
        std::cout << '\n';
    }

    return 0;
}