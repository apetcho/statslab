#include "statslab.hpp"
#include<iostream>
#include<cstdlib>

namespace statslab{

/**
 * @brief CenterInfo::mean()
 * Compute the sample arithemic mean of data.
 * 
 * @return double 
 */
double CenterInfo::mean(){
    double result = 0.0;
    auto N = data_.size();

    if (N < 1){
        std::cerr << "mean() requires at least one data point"
            << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    for(auto elt: data_){
        result += elt;
    }
    result /= (double)N;

    return result;
}


/**
 * @brief CenterInfo::geometric_mean()
 * Compute the geometric mean.
 * 
 * @return double 
 */
double CenterInfo::geometric_mean(){
    //
    double result = 0.0;
    auto transformed =  data_.apply(std::log);
    auto meanfunc = [&transformed]() -> double {
        auto n = transformed.size();
        double res = 0.0;
        for(auto elt: transformed){
            res += elt;
        }
        res /= (double)n;
        return res;
    };
    result = std::exp(meanfunc());

    return result;
}
//

//
}