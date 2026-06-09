#include <stdlib.h>
#include <math.h>
#include "random_number.h"

double generate_normal_zero_mean(double variance) {
    double u, v, s;
    
    do {
        u = 2.0 * ((double)rand() / RAND_MAX) - 1.0; 
        v = 2.0 * ((double)rand() / RAND_MAX) - 1.0; 
        s = u * u + v * v;
    } while (s >= 1.0 || s == 0.0);

    double standard_normal = u * sqrt(-2.0 * log(s) / s);

    return sqrt(variance) * standard_normal;
}