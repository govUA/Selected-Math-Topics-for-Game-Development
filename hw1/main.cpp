#include <iostream>

#include "convert.h"

int main(){
    std::cout<<float32ToBits(3.14)<<std::endl;
    std::cout<<float64ToBits(3.141592)<<std::endl;
    std::cout<<bitsToFloat32(1078523331)<<std::endl;
    std::cout<<bitsToFloat64(4614256655080292474)<<std::endl;
    return 0;
}