#include "statslab.hpp"
#include<iostream>
#include<cstdlib>
#include<algorithm>

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

/**
 * @brief CenterInfo::harmonic_mean()
 * Compute the harmonic mean of data.
 * 
 * The harmonic mean is the reciprocal of the arithmetic mean of the 
 * reciprocals of the data. It can be used for averarging ratios or 
 * rates, for example speeds.
 * 
 * @param weight 
 * @return double 
 */
double CenterInfo::harmonic_mean(std::vector<double> weights){
    //
    auto errmsg = "harmonic mean does not support negative values"
    auto N = data_.size();
    if(n < 1){
        std::cerr << "harmonic_mean() requires at least one data point"
            << std::endl;
        std::exit(EXIT_FAILURE);
    }
    else if(N == 1 && weights.empty()){
        auto x = data_[0];
        if(x < 0){
            std::cerr << errmsg << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return x;
    }

    double sumWeights = 0.0;
    if(weights.empty()){
        for(size_t i=0; i < N; ++i){
            weights.push_back(1.0);
        }
        sumWeights = (double)(N);
    }
    else{
        if(weights.size() != N){
            std::cerr << "Number of weight does not much data size"
                << std::endl;
        }
        //
        for(auto elt: weights){
            if(elt < 0.0){
                std::cerr << errmsg << std::endl;
                std::exit(EXIT_FAILURE);
            }
            sumWeights += elt;
        }
    }
    //
    double total = 0.0;
    if(data_.min() < 0.0){
        std::cerr << errmsg << std::endl;
        std::exit(EXIT_FAILURE);
    }
    try{
        for(size_t i=0; i < N; i++{
            auto w = weights[i];
            auto v = data_[i];
            total += w/x;
        }
    }
    catch(...){ // ZeroDivisionError
        return 0.0;
    }

    auto val = sumWeights / total;
    return val;
} //

double CenterInfo::median(){
    //
    auto N = data_.size();
    if (N==0){
        std::cerr << "No median for empty data." << std::endl;
    }
    std::vector<double> values(N, 0.0);
    for(auto elt: data_){
        values.push_back(elt);
    }
    std::sort(values.begin(), values.end());

    double result = 0.0;
    if(N % 2 == 1){
        result = values[N/2];
    }
    else {
        auto i = N/2;
        result = (values[i-1] + values[i])/2.0;
    }

    return result;
}

}// namespace statslab