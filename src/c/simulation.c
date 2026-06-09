#include "football.h"
#include "random_number.h"

double calculate_xg
(double shooter_x, double shooter_y,
 double shot_variance,
 double* defender_xs, double* defender_ys,
 int n_defenders,
 double defender_body_r, double defender_reach_r,
 double goalkeeper_x, double goalkeeper_y,
 double goalkeeper_body_r, double goalkeeper_reach_r,
 int n_iterations) 
{
    int goals = 0;

    Positions positions = create_positions(shooter_x, shooter_y, defender_xs, defender_ys,
                        n_defenders, defender_body_r, defender_reach_r, goalkeeper_x, goalkeeper_y,
                        goalkeeper_body_r, goalkeeper_reach_r);
    double target_x = choose_target(positions); 
    Point target = {target_x, 0.0};
    Point shooter = positions.shooter;
    Ray ideal_shot = ray_through_points(shooter, target);
    double ideal_angle = oriented_angle_of_ray(ideal_shot);

    for(int i = 0; i < n_iterations; i++) {
        double offset = generate_normal_zero_mean(shot_variance);
        double actual_angle = ideal_angle + offset;
        Ray actual_shot = ray_with_oriented_angle(shooter, actual_angle);
        
        if (is_goal(actual_shot, positions)) {
            goals++;
        }
    }
    
    delete_positions(positions);
    return (double)goals / n_iterations;
}