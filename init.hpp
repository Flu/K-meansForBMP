/* Here are all the declarations of the functions and structs/classes necesarry 
for the k-means initialization algorithm for cluster centres. It uses the k-means++
algorithm for improved cluster initialization (not random, but probabilistic), and in the
long run it will converge far quicker with more optimal results.
Fluturel Adrian, (c) 2018
*/

#include <random>

std::default_random_engine generator(rand());
std::uniform_int_distribution<int> distributionI(0,1419*1001 - 1);
std::uniform_real_distribution<long double> distributionR(0.l,1.l);

auto genI = std::bind(distributionI, generator);
auto genR = std::bind(distributionR, generator);

long chooseClosestCentroid(Pixel &, const Centroid*, const short &);
void normalizeVector(long double*, const long &, const long double&);
long double sumDistances(Pixel*, const long &, double long*, Centroid*, short &);
long computeDistance(const Pixel &, const Pixel &);
Centroid* chooseCentroids(Pixel*, const long &, const short &);