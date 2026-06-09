#include <stdlib.h>

#include "football.h"
#include "constants.h"

Circle get_body_circle(Defending_Player player) {
    return (Circle) {player.position, player.body_radius};
}

Circle get_reach_circle(Defending_Player player) {
    return (Circle) {player.position, player.reach_radius};
}

Positions create_positions(double shooter_x, double shooter_y,
 double* defender_xs, double* defender_ys,
 int n_defenders,
 double defender_body_r, double defender_reach_r,
 double goalkeeper_x, double goalkeeper_y,
 double goalkeeper_body_r, double goalkeeper_reach_r
) {
    Positions positions;
    
    positions.shooter = (Point) {shooter_x, shooter_y};
    positions.goalkeeper = (Point) {goalkeeper_x, goalkeeper_y};
    positions.defender_body_r = defender_body_r;
    positions.defender_reach_r = defender_reach_r;
    positions.goalkeeper_body_r = goalkeeper_body_r;
    positions.goalkeeper_reach_r = goalkeeper_reach_r;

    Point* defenders = (Point*) malloc(sizeof(Point) * n_defenders);
    if (n_defenders == 0 || !defenders) {
        positions.defenders = NULL;
        positions.n_defenders = 0;
        return positions;
    }

    for (int i = 0; i < n_defenders; ++i) {
        Point defender = {defender_xs[i], defender_ys[i]};
        defenders[i] = defender;
    }
    positions.defenders = defenders;
    positions.n_defenders = n_defenders;

    return positions;
}

void delete_positions(Positions positions) {
    free(positions.defenders);
}

int is_defender_in_front(Point defender, Point shooter) {
    return defender.y < shooter.y;
}

double choose_target(Positions positions) {
    Interval* covered = (Interval*) malloc(sizeof(Interval) * (positions.n_defenders + 1));
    int number_of_covers = 0;
    for (int i = 0; i < positions.n_defenders; i++) {
        Point defender = positions.defenders[i];
        if (!is_defender_in_front(defender, positions.shooter)) continue;
        Circle defender_body = {defender, positions.defender_body_r};
        covered[number_of_covers] = circle_coverage_on_y_0(defender_body, positions.shooter);
        number_of_covers++;
    }
    if (is_defender_in_front(positions.goalkeeper, positions.shooter)) {
        Circle goalkeeper_body = {positions.goalkeeper, positions.goalkeeper_body_r};
        covered[number_of_covers] = circle_coverage_on_y_0(goalkeeper_body, positions.shooter);
        number_of_covers++;
    }

    Union_Of_Intervals union_of_covers = create_union(covered, number_of_covers);
    Union_Of_Intervals free_spaces = subtract_union_from_interval(union_of_covers, X_LEFT_GOAL, X_RIGHT_GOAL);
    
    Interval target_interval = biggest_interval(free_spaces);

    double target = interval_midpoint(target_interval);

    free(covered);
    delete_union(union_of_covers);
    delete_union(free_spaces);

    return target;
}

int is_goal(Ray actual_shot, Positions positions) {
    double actual_target = ray_intersection_with_y_0(actual_shot);
    if (actual_target < X_LEFT_GOAL || actual_target > X_RIGHT_GOAL) return 0;

    Interval* covered = (Interval*) malloc(sizeof(Interval) * (positions.n_defenders + 1));
    int number_of_covers = 0;
    for (int i = 0; i < positions.n_defenders; i++) {
        Point defender = positions.defenders[i];
        if (!is_defender_in_front(defender, positions.shooter)) continue;
        Circle defender_reach = {defender, positions.defender_reach_r};
        covered[number_of_covers] = circle_coverage_on_y_0(defender_reach, positions.shooter);
        number_of_covers++;
    }
    if (is_defender_in_front(positions.goalkeeper, positions.shooter)) {
        Circle goalkeeper_reach = {positions.goalkeeper, positions.goalkeeper_reach_r};
        covered[number_of_covers] = circle_coverage_on_y_0(goalkeeper_reach, positions.shooter);
        number_of_covers++;
    }
    
    Union_Of_Intervals union_of_covers = create_union(covered, number_of_covers);
    Union_Of_Intervals union_of_covers_trimmed = trim_union(union_of_covers, X_LEFT_GOAL, X_RIGHT_GOAL);

    int result = !is_point_in_union(union_of_covers_trimmed, actual_target);
    delete_union(union_of_covers);
    delete_union(union_of_covers_trimmed);
    free(covered);
    
    return result;
}


// Simulation create_simulation(Point shooter, DefendingPlayer* defenders, int n_defenders) {
//     Simulation sim;
//     sim.shooter = shooter;
    
//     if (n_defenders > 0 && defenders != NULL) {
//         sim.defending_players = (DefendingPlayer*) malloc(n_defenders * sizeof(DefendingPlayer));
//         if (sim.defending_players) {
//             memcpy(sim.defending_players, defenders, n_defenders * sizeof(DefendingPlayer));
//             sim.n_defending_players = n_defenders;
//         } else {
//             // Obsługa błędu alokacji pamięci
//             sim.defending_players = NULL;
//             sim.n_defending_players = 0;
//         }
//     } else {
//         sim.defending_players = NULL;
//         sim.n_defending_players = 0;
//     }
    
//     return sim;
// }

// void free_simulation(SimulationState sim) {
//     if (sim.defending_players != NULL) {
//         free(sim.defending_players);
//         // Dobra praktyka, chociaż sim to tylko kopia na stosie
//         sim.defending_players = NULL; 
//         sim.n_defending_players = 0;
//     }
// }