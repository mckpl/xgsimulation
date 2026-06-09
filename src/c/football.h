#ifndef FOOTBALL_H
#define FOOTBALL_H

#include "geometry.h"

typedef struct _Positions {
    Point shooter;
    Point* defenders;
    int n_defenders;
    double defender_body_r;
    double defender_reach_r;
    Point goalkeeper;
    double goalkeeper_body_r;
    double goalkeeper_reach_r;
} Positions;

Positions create_positions(double shooter_x, double shooter_y,
 double* defender_xs, double* defender_ys,
 int n_defenders,
 double defender_body_r, double defender_reach_r,
 double goalkeeper_x, double goalkeeper_y,
 double goalkeeper_body_r, double goalkeeper_reach_r);

void delete_positions(Positions positions);

double choose_target(Positions positions);
int is_goal(Ray actual_shot, Positions positions);


#endif