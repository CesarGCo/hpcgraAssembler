#include <iostream>
#include <cgra.h>
#include <utils.h>

int main(){

    CGRA cgra("../tests/JsonTst/6x6_systolic.json");

    int id = 1;
    int numIstream = cgra.getPE(id).getNumAluInputs();

    std::cout << numIstream << std::endl;


   return 0;

}
