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

/**
 * @brief Creates structure Positions that represents situation on pitch
 * @param shooter_x x coordinate of shooter
 * @param shooter_y y coordinate of shooter
 * @param defender_xs x coordinates of defenders
 * @param defender_ys y coordinates of defenders
 * @param n_defenders number of defenders
 * @param defender_body_r radius of defender body
 * @param defender_reach_r radius of circle representing defended area by defender
 * @param goalkeeper_x x coordinate of goalkeeper
 * @param goalkeeper_y y coordinate of goalkeeper
 * @param goalkeeper_body_r radius of goalkeeper body
 * @param goalkeeper_reach_r radius of circle representing defended area by goalkeeper
 * @return structure Positions
 */
Positions create_positions(double shooter_x, double shooter_y,
 double* defender_xs, double* defender_ys,
 int n_defenders,
 double defender_body_r, double defender_reach_r,
 double goalkeeper_x, double goalkeeper_y,
 double goalkeeper_body_r, double goalkeeper_reach_r);

/**
 * @brief Deletes structure Positions and frees memory
 * @param positions structure to be deleted
 */
void delete_positions(Positions positions);

/**
 * @brief Chooses target x coordinate on goal line that striker should aim for based on
 * situation on pitch
 * @param positions situation on pitch 
 * @return x coordinate on goal line 
 */
double choose_target(Positions positions);

/**
 * @brief Verifies if shot ends with scored goal
 * @param actual_shot ray representing taken shot
 * @param positions situation on pitch 
 * @return 1 if it ends with goal else 0 
 */
int is_goal(Ray actual_shot, Positions positions);


#endif