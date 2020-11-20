#ifndef _STATSLAB_H
#define _STATSLAB_H

#include<valarray>
#include<vector>
#include<array>
#include<list>

/*Input type is either a:
    - array of type [T]. eg: int data[] = {1, 2, 3}
    - array type of type T. eg. array<int, size> data{1, 2}
    - list type of type T. eg. list<int> data{1, 2, 3}
    - vector type of type T. eg. vector<int> data{1, 2, 3}
*/

// TODO:
// Add documentation to each function as it is being developed and test them
// that function along the way.
// Add exception mechanisms to control possible failure.

namespace statslab {
    class NormalDist; // forward declaration

    // Basic Statistics class
    template<typename T>
    class StatsLab{
        template<typename T>
        using dtype = std::valarary<T>;

        dtype data;
        friend class NormalDist;
    public:

        // mean
        double mean();

        // geometric_mean
        double geometric_mean();

        // harmonic_mean
        double harmonic_mean();

        // median
        T median();

        // median_low
        T median_low();

        // median_high
        T median_high();

        // median_grouped
        double median_grouped();

        // mode
        T mode();
        // maybe add a function return a map of the individual items
        // and their corresponding frequency for categorial data.

        // multimode
        std::vector<T> multimode();

        // pstdev
        double pstdev(double mu=0.0);

        // pvariance
        double pvariance(double mu=0.0);

        // stdev
        double stdev(double xbar=0.0);

        // variance
        double variance(double xbar=0.0);

        // quantiles
        std::vector<T> quantiles(size_t n=4,
            std::string method="exclusive");
    };


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
        std::array<double> quantiles(int n=4);
        double zscore(double x);

        // TODO: Load appropriate operators
        // +, -, *, /, copy ctor, negation, ++, --,
        // __hash__, to_string (aka ostream)  

    private:
        double mean;
        double median;
        double mode;
        double stdev;
        double variance;
    };
}

#endif // _STATSLAB_H
