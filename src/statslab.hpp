#ifndef _STATSLAB_H
#define _STATSLAB_H

#include<valarray>

// TODO:
// Input data is a numeric container of type array, vector, list or
// valarray.
// Make sure to take into consideration each of these types.
// Numeric here mean, int, float or double at least

namespace statslab {
    // mean
    template<typename T>
    T mean(std::valarray<T>&);

    // geometric_mean
    template<typename T>
    T geometric_mean(std::valarray<T>&);

    // harmonic_mean
    template<typename T>
    T harmonic_mean(std::valarray<T>&);

    // median
    template<typename T>
    T median(std::valarray<T>&);

    // median_low
    template<typename T>
    T median_low(std::valarray<T>&);

    // median_high
    template<typename T>
    T median_high(std::valarray<T>&);

    // median_grouped
    template<typename T>
    T median_grouped(std::valarray<T>&);

    // mode
    template<typename T>
    T mode(std::valarray<T>&);

    // multimode
    template<typename T>
    T multimode(std::valarray<T>&);

    // pstdev
    template<typename T>
    T pstdev(std::valarray<T>&);

    // pvariance
    template<typename T>
    T pvariance(std::valarray<T>&);

    // stdev
    template<typename T>
    T stdev(std::valarray<T>&);

    // variance
    template<typename T>
    T variance(std::valarray<T>&);

    // quantiles
    template<typename T>
    T quantiles(std::valarray<T>&);

    // NormalDist
    class NormalDist{
    public:
        NormalDist(double mu=0.0, double sigma=1.0);
        /* properties */
        double get_mean();
        double get_median();
        double get_mode();
        double get_stdev();
        double get_variance();
        /* methods */
        NormalDist from_samples(std::valarray<double>&);
        std::valarray<double> samples(int n, int seed=0);
        double pdf(double x);
        double cdf(double x);
        double inv_cdf(double p);
        double overlap(NormalDist&);
        std::valarray<double> quantiles(int n=4);
        double zscore(double x);

    private:
        double mean;
        double median;
        double mode;
        double stdev;
        double variance;
    };
}

#endif // _STATSLAB_H
