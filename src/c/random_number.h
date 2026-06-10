#ifndef RANDOM_NUMBER_H
#define RANDOM_NUMBER_H

/**
 * @brief generates pseudorandom number from normal distribution with mean=0 and given variance
 * it uses Marsaglia polar method.
 * @param variance given variance
 * @return real pseudorandom number from distribution mean=0 and given variancee
 */

double generate_normal_zero_mean(double variance);

#endif