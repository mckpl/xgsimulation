#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <stddef.h>

typedef struct _Point {
    double x;
    double y;
} Point;

typedef struct _Vector {
    double x;
    double y;
} Vector;

typedef struct _Ray {
    Point origin;
    Vector vector;
} Ray;

typedef struct _Circle {
    Point center;
    double radius;
} Circle;

typedef struct _Interval {
    double left;
    double right;
} Interval;

typedef struct _Union_Of_Intervals {
    Interval* intervals;
    size_t n;
} Union_Of_Intervals;

/**
 * @brief Checks if first is `LESS(-1)`, they are both `EQUAL(0)`, 
 * first is greater `GREATER(1)` using some epsilon to compensate for floating point errors
 * @param a first number
 * @param b second_number
 * @return `LESS (-1)` if +/- a < b, `EQUAL (0)` if +/- a = b, `GREATER (1)` if +/- a > b
 */
int compare(double a, double b);

/**
 * @brief Calculates distance betwee two points
 * @param a Point
 * @param b Point
 * @return distance between points
 */
double dist_point_point(Point a, Point b);

/**
 * @brief Creates 2d vector connecting two points
 * @param start start of vector
 * @param end end of vector
 * @return vector connecting points
 */
Vector vector_between(Point start, Point end);

/**
 * @brief Scales vector by scalar
 * @param scalar scalar
 * @param vector vector
 * @return scaled vector
 */
Vector scale_vector(double scalar, Vector vector);

/**
 * @brief Creates vector of length 1 that starts in `start` and points in direction of `end`,
 *  if points are almost equal then it returns `{0, 0}` vector
 * @param start point that is a start of vector
 * @param end point in which direction vector is pointed
 * @return unit vector
 */
Vector unit_vector(Point start, Point end);

/**
 * @brief Creates vector of length 1 with specified angle using trig functions
 * @param oriented_angle specified_angle
 * @return unit vector with specified angle
 */
Vector unit_vector_with_oriented_angle(double oriented_angle);

/**
 * @brief Creates `Ray` started at `origin` and going through `target
 * @param origin start of ray
 * @param target point of ray
 * @return ray going through specified points
 */
Ray ray_through_points(Point origin, Point target);

/**
 * @brief Creates `Ray` started at `origin` having specified oriented angle
 * @param origin start of ray
 * @param oriented_angle oriented angle of ray
 * @return ray starting at origin that has specified angle
 */
Ray ray_with_oriented_angle(Point origin, double oriented_angle);

/**
 * @brief Calculates oriented angle of given ray
 * @param ray ray
 * @return oriented angle of ray
 */
double oriented_angle_of_ray(Ray ray);

/**
 * @brief Calculates intersection with line y=0 of given ray
 * @param ray ray
 * @return x coordinate of point that is intersection
 */
double ray_intersection_with_y_0(Ray ray);

/**
 * @brief Calculates length of given interval
 * @param interval interval
 * @return length of given interval
 */
double interval_length(Interval interval);

/**
 * @brief Calculates value that is in the middle of interval
 * @param interval interval
 * @return middle of interval
 */
double interval_midpoint(Interval interval);

/**
 * @brief Creates structure `Union_Of_Intervals` that stores disjoint sorted intervals
 * @param intervals intervals to be unioned
 * @param n initial number of intervals
 * @return structure `Union_Of_Intervals`
 */
Union_Of_Intervals create_union(Interval* intervals, size_t n);

/**
 * @brief Trims structure `Union_Of_Intervals` so that all values are between `left_limit` and `right_limit`
 * @param union_of_intervals initial union
 * @param left_limit smaller limit for all values
 * @param right_limit greater limit for all values
 * @return trimmed union
 */
Union_Of_Intervals trim_union(Union_Of_Intervals union_of_intervals, double left_limit, double right_limit);

/**
 * @brief Subtracts given union from interval [`left_limit`, `right_limit`]
 * @param union_of_intervals given union
 * @param left_limit left end of interval
 * @param right_limit right end of interval
 * @return trimmed union
 */
Union_Of_Intervals subtract_union_from_interval(Union_Of_Intervals union_of_intervals, double left_limit, double right_limit);

/**
 * @brief Finds biggest interval from union
 * @param union_of_intervals given union
 * @return biggest interval
 */
Interval biggest_interval(Union_Of_Intervals union_of_intervals);

/**
 * @brief Checks if value `point` is present in union
 * @param union_of_intervals given union
 * @return 1 if it is in union, 0 otherwise
 */
int is_point_in_union(Union_Of_Intervals union_of_intervals, double point);

/**
 * @brief Frees memory that should be freed if union will not be used in future
 * @param union_of_intervals given union
 */
void delete_union(Union_Of_Intervals union_of_intervals);


/**
 * @brief Returns interval that ends are interstections of adjacent lines to circle 
 * with y=0 line started from `point`,
 * if point is located inside the circle, it returns an infinite interval.
 * @param circle given circle
 * @param point given point
 * @return interval
 */
Interval circle_coverage_on_y_0(Circle circle, Point point);

#endif