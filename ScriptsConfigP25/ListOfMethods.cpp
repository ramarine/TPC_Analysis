#include <iostream>

int SayHelloWorld()
{

  cout << " Hello world " << endl;
  return 0;
}


// returns the mean, std and the number of entries of a sample
std::vector<double> GetMean_STD_NEntries(std::vector<double> & intg_a_values){
 
   
    auto v = intg_a_values;
    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    double mean = sum / v.size(); 
    
    std::vector<double> diff(v.size());
    std::transform(v.begin(), v.end(), diff.begin(), std::bind2nd(std::minus<double>(), mean));
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / v.size());
    
    std::vector<double> dummy(3,0);
    dummy[0] = mean;
    dummy[1] = stdev;
    dummy[2] = v.size();
    
    return dummy;

}
// gives the error of the number of photons detected
