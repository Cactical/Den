/*

devenv (version 0.1) by Cactical
devenv (short for "developer environment", can be shortened to "den"), by Cactical
devenv is a developer environment that you can develop code in, basically a mini IDE in the terminal.
Made with love :)

*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <signal.h>
#include "CppColors/cppcolors.hpp"
#include "Domptero.hpp"

int main() {

    // Activate    
    activate();   
    
    if (username == "NO USERNAME") {
     
        std::cout << primarycolor << "Goodbye.\n";
    
    } else {
     
        std::cout << primarycolor << "Goodbye, " << semiimportantcolor << username << "\n";

    }
    
    return(0);
}