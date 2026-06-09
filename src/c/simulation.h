#ifndef SIMULATION_H
#define SIMULATION_H

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