#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>

double truncated_sum(std::vector<double> &a)
{
    auto naive_sum = 0.0;
    auto max_a = -1.0e32;
    for (auto& n : a) {
        naive_sum += n;
        auto abs_n = std::abs(n);
        if ( abs_n > max_a ) max_a = abs_n;
    }

    unsigned int num_remainder_digit = 16 - ( std::floor( std::log10(max_a) ) - std::floor( std::log10(std::abs(naive_sum)) ) );
    std::cerr << "\nmag of max_a = " << std::log10(max_a) << std::endl;
    std::cerr << "mag of abs(naive_sum) = " << std::log10(std::abs(naive_sum)) << std::endl;
    std::cerr << "num_remainder_digit = " << num_remainder_digit << std::endl;

    int    factor_exponent = -std::floor( std::log10(std::abs(naive_sum)) ) + (num_remainder_digit - 1);
    double factor = std::pow( 10.0, factor_exponent );
    double factor_inv = std::pow( 10.0, -factor_exponent );
    double truncated_sum = std::trunc( naive_sum * factor ) * factor_inv;

    std::cerr << std::setprecision(21) << std::trunc( naive_sum * factor ) << " " << factor << " " 
              << truncated_sum << std::endl;

    return truncated_sum;
}
    

int main()
{
    double array_a[] = {-114297066905.23395, 151806225744.30453, -148883528399.31354, 96497905815.673676, 14876463744.569481};
    double array_b[] = {14876463744.569481, -114297066905.23395, 151806225744.30453, -148883528399.31354, 96497905815.673676};
    //double array_a[] = {5333584975.097, -14062500000.0, 23686629790.07, -14062500000.0, 4729785234.829, -5625000000.0};
    //double array_b[] = {-5625000000.0, 5333584975.097 -14062500000.0, 23686629790.07, -14062500000.0, 4729785234.829};
    std::vector<double> a (array_a, array_a + sizeof(array_a) / sizeof(double) );
    std::vector<double> b (array_b, array_b + sizeof(array_b) / sizeof(double) );

    double naive_sum_a = 0.0;
    double naive_sum_b = 0.0;
    for (auto& n : a)
        naive_sum_a += n;

    for (auto& n : b)
        naive_sum_b += n;

    std::cerr<< std::setprecision(17) << "\nnaive_sums:\n" << naive_sum_a <<"\n"<< naive_sum_b << std::endl;

    double tsum_a = truncated_sum(a);
    double tsum_b = truncated_sum(b);

    std::cerr<< std::setprecision(17) << "\ntruncated_sums:\n" << tsum_a <<"\n"<< tsum_b << std::endl;

    return 0;
}
