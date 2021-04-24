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

//
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

//
double CenterInfo::median_high(){
    double result = 0.0;
    auto N = data_.size();
    if (N == 0){
        std::cerr << "No median for empty data." << std::endl;
        std::exit(EXIT_FAILURE); 
    }

    std::vector<double> values(N, 0.0);
    for(auto elt: data_){
        values.push_back(elt);
    }
    std::sort(values.begin(), values.end());

    if(N % 2 == 1){
        result = data_[i];
    }
    else {
        result = data[i-1];
    }

    return result;
}//

//
double CenterInfo::median_high(){
    double result = 0.0;
    auto N = data_.size();
    if (N == 0){
        std::cerr << "No median for empty data." << std::endl;
        std::exit(EXIT_FAILURE); 
    }

    std::vector<double> values(N, 0.0);
    for(auto elt: data_){
        values.push_back(elt);
    }
    std::sort(values.begin(), values.end());

    result = data_[N/2];

    return result;
}//

double CenterInfo::median_grouped(double interval){
    //
    using T = std::vector<double>;
    //
    auto find_lteq_ = [](const T& a, double x) -> int {
        int index = -1;
        auto ans = std::find(std::begin(a), std::begin(a), x);
        if(ans = std::end(a)){
            std::cerr << x << " not in data." << std::endl;
            std::exit(EXIT_FAILURE);
        }
        for(auto i=0; i < a.size(); i++){
            if (a[i] == x){
                index = i;
            }
        }

        if(index == -1){
            std::cerr << x << "not in data." << std::endl;
        }
        return index;
    };
    //
    
    auto bisectRight = [](const T& arr, double x, int lo, int hi=-1) -> int {
        int index = -1;
        if (lo < 0 || lo >= (arr.size()-1)){
            std::cerr << "bisectRight():: lo must be non-negative "
                    << "or less than the number of item data array\n";
            std::exit(EXIT_FAILURE);
        }
        if (hi==-1){
            hi = arr.size();
        }

        while(lo < hi){
            auto mid = (lo + hi) / 2;
            if (x < arr[mid]){
                hi = mid;
            }else{
                lo = mid + 1;
            }
        }
        index = lo;
        return index;
    };

    auto find_rteq_ = [](const T& arr, int lo, double x) -> int {
        index = -1;
        auto hi = arr.size();
        auto i = bisectRight(a, x, lo);
        if(i != (arr.size() + 1) && arr[i-1] == x){
            index = i - 1;
        }
        return index;
    };
    
    //
    double result = 0.0;
    auto N = data_.size();
    std::vector<double> values(N, 0.0);
    std::copy(std::begin(data_), std::end(data_), values.begin());
    if (N == 0){
        std::cerr << "No median for empty data." << std::endl;
        std::exit(EXIT_FAILURE);
    }else if(N == 1){
        result = values[0];
        return result;
    }

    auto item = values[N/2];
    auto lower =  item - interval / 2.0;
    auto l1 = find_lteq_(values, item);
    auto l2 = find_rteq_(values, l1, x);
    auto cf = l1;
    auto f = l2 - l1 + 1;
    result = lower + interval * (N / 2.0 - cf) / f;

    return result;
}//

}// namespace statslab