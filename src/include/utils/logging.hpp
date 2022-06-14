#pragma once
#include <iostream>
#include "out_decor.hpp"

// Przykładowe użycie: własny szablon
template <typename T> void log(int mode, T output) {
    std::string prefix;
    switch (mode) {
        case 0:
            prefix = "[INFO]";
            break;
        case 1:
            prefix = "[WARN]";
            break;
        case 2:
            prefix = "[ERROR]";
            break;
        default:
            std::cout<<"Wrong log mode given\n";
            return;
    }

    #ifdef _WIN32
        std::cout<<prefix<<" >> log value: "<<info_output<<std::endl;
        return;
    #endif
    std::cout<<bold_on<<prefix<<" >> log value: "<<bold_off<<output<<std::endl;
}

