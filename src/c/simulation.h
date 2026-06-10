#ifndef SIMULATION_H
#define SIMULATION_H
/**
 * @brief calculates xG (expected goals) using Monte Carlo simulation, simulates `n_iterations`
 * of shots taking situation on pitch and choosing optimal shot that varies with offset taken
 * from normal distribution with mean equal to 0 and given variance, for each shot it checks
 * if it ends with goal and in the end it divides number of scored goals by total number of iterations.
 * @param shooter_x x coordinate of shooter
 * @param shooter_y y coordinate of shooter
 * @param shot_variance variance of normal distribution representing shot inaccuracy
 * @param defender_xs x coordinates of defenders
 * @param defender_ys y coordinates of defenders
 * @param n_defenders number of defenders
 * @param defender_body_r radius of defender body
 * @param defender_reach_r radius of circle representing defended area by defender
 * @param goalkeeper_x x coordinate of goalkeeper
 * @param goalkeeper_y y coordinate of goalkeeper
 * @param goalkeeper_body_r radius of goalkeeper body
 * @param goalkeeper_reach_r radius of circle representing defended area by goalkeeper
 * @param n_iterations number of iterations 
 * * @return double The estimated probability of scoring a goal (xG value), ranging from 0.0 to 1.0.
 */
double calculate_xg
(double shooter_x, double shooter_y,
 double shot_variance,
 double* defender_xs, double* defender_ys,
 int n_defenders,
 double defender_body_r, double defender_reach_r,
 double goalkeeper_x, double goalkeeper_y,
 double goalkeeper_body_r, double goalkeeper_reach_r,
 int n_iterations);

#endif