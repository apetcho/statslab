#ifndef _STATSLAB_H
#define _STATSLAB_H

#include<valarray>
#include<vector>
#include<array>
#include<string>
#include<exception>
#include<list>


namespace statslab {
class NormalDist; // forward declaration

class CenterInfo;
class DispersionInfo;
class ShapeInfo;
class SummaryTable;

class DescStats{
    friend class CenterInfo;
    friend class DispersionInfo;
    friend class ShapeInfo;
    friend class SummaryTable;

public:
    DescStats();

private:
    std::valarray<double> data;
    CenterInfo center;
    DispersionInfo dispersion;
    ShapeInfo shapeOfDist;
};

//
class CenterInfo{
public:
    explicit CenterInfo()
        : data_(std::valarray<double>()){}
    explicit CenterInfo(std::valarray<double> &observation)
        : data_{observation}{}
    CenterInfo(const CenterInfo& centerObj) = delete;
    CenterInfo(CenterInfo&& centerObj) = delete;
    CenterInfo operator=(const CenterInfo& centerObj) = delete;
    CenterInfo operator=(CenterInfo&& centerObj) = delete;

    ~CenterInfo(){}

    double mean();
    double geometric_mean();
    double harmonic_mean(std::vector<double>& weights);
    double median();
    double mode();
    //double multimode();

private:
    //
    std::valarray<double> data_;
};

//
class DispersionInfo{};

//
class ShapeInfo{};

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
    //std::array<double> quantiles(int n=4);
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

} // namespace statslab

#endif // _STATSLAB_H
