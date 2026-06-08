#include "geometry.h"
#include "constants.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) > (b) ? (b) : (a))

#define LESS -1
#define EQUAL 0
#define GREATER 1

int compare(double a, double b) 
{
    if (fabs(a - b) <= EPS) //a == b
        return EQUAL;
    if (a + EPS < b) //a < b
        return LESS;
    //b < a
    return GREATER;
}

double dist_point_point(Point a, Point b)
{
    return hypot(b.x - a.x, b.y - a.y);
}

Vector vector_between(Point start, Point end) {
    return (Vector){end.x - start.x, end.y - start.y};
}

Vector scale_vector(double scalar, Vector vector)
{
    return (Vector){scalar * vector.x, scalar * vector.y};
}

Vector unit_vector(Point start, Point end)
{
    Vector out_vector;
    out_vector = vector_between(start, end);
    double length = hypot(out_vector.x, out_vector.y);
    if (compare(length, 0) != EQUAL)
    {
        out_vector = scale_vector(1/length, out_vector);
    }
    else
    {
        out_vector.x = 0.0;
        out_vector.y = 0.0;
    }
    

    return out_vector;
}

Vector unit_vector_with_oriented_angle(double oriented_angle) {
    return (Vector) {cos(oriented_angle), sin(oriented_angle)};
}

Ray ray_through_points(Point origin, Point target)
{
    return (Ray) {origin, unit_vector(origin, target)};
}

Ray ray_with_oriented_angle(Point origin, double oriented_angle) {
    return (Ray) {origin, unit_vector_with_oriented_angle(oriented_angle)};
}

double oriented_angle_of_ray(Ray ray)
{
    return atan2(ray.vector.y, ray.vector.x);
}

double ray_intersection_with_y_0(Ray ray)
{
    Vector vector = ray.vector;
    Point origin = ray.origin;

    if (compare(origin.y, 0) == EQUAL) 
        return origin.x;

    if (compare(vector.y, 0) == EQUAL)
    {
        // vector.x jest albo okolo 1.0 albo okolo -1.0
        if (vector.x > 0) return INFINITY;
        return -INFINITY;
    }
    if (vector.y > 0) 
    {
        if (vector.x > 0) return INFINITY;
        return -INFINITY;
    }

    double t = -origin.y / vector.y;

    double x0 = origin.x + t * vector.x;   
    return x0;
}

double interval_length(Interval interval)
{
    return interval.right - interval.left;
}

double interval_midpoint(Interval interval)
{
    return (interval.left + interval.right) / 2;
}

int compare_Intervals(const void* interval1, const void* interval2)
{
    double left1 = ((const Interval*) interval1) -> left;
    double left2 = ((const Interval*) interval2) -> left;
    if (left1 < left2) return LESS;
    if (left1 > left2) return GREATER;
    return EQUAL;
}

Union_Of_Intervals create_union(Interval* intervals, size_t n) 
{
    if (n == 0)
    {
        return (Union_Of_Intervals) {NULL, 0};
    } // n >= 1
    
    Interval* out_intervals = (Interval*) malloc(sizeof(Interval) * n);

    if(!out_intervals) return(Union_Of_Intervals) {NULL, 0};

    memcpy(out_intervals, intervals, sizeof(Interval) * n);

    qsort(out_intervals, n, sizeof(Interval), compare_Intervals);
    // przedzialy posortoowane po lewym koncu rosnaco

    size_t last_out = 0;
    for (size_t i = 1; i < n; i++)
    {

        if (compare(out_intervals[i].left, out_intervals[last_out].right) != GREATER)
            out_intervals[last_out].right = MAX(out_intervals[last_out].right, out_intervals[i].right);
        else 
        {
            last_out++;
            out_intervals[last_out] = out_intervals[i];
        }
    }
    Union_Of_Intervals out_union;
    out_union.n = last_out+1;
    Interval* temp = (Interval*) realloc(out_intervals, sizeof(Interval) * out_union.n);
    if (temp) 
        out_union.intervals = temp;
    else
        out_union.intervals = out_intervals;
    return out_union;
}

Interval trim_interval(Interval interval, double left_limit, double right_limit) {
    return (Interval) {MAX(interval.left, left_limit), MIN(interval.right, right_limit)};
}

Union_Of_Intervals trim_union(Union_Of_Intervals union_of_intervals, double left_limit, double right_limit) {
    if (union_of_intervals.n == 0)
        return (Union_Of_Intervals) {NULL, 0};
    
    Interval* out_intervals = (Interval*) malloc(sizeof(Interval) * union_of_intervals.n);

    if (!out_intervals)
        return (Union_Of_Intervals) {NULL, 0};

    size_t count = 0;
    for (size_t i = 0; i < union_of_intervals.n; i++) {
        Interval curr_interval = union_of_intervals.intervals[i];

        if (curr_interval.right < left_limit) continue;
        if (curr_interval.left > right_limit) break;

        out_intervals[count] = trim_interval(curr_interval, left_limit, right_limit);
        count++;
    }

    Union_Of_Intervals out_union;
    out_union.n = count;
    if (count > 0) {
        Interval* temp = (Interval*) realloc(out_intervals, sizeof(Interval) * out_union.n);
        if (temp)
            out_union.intervals = temp;
        else
            out_union.intervals = out_intervals;
    
    }
    else {
        free(out_intervals);
        out_union.intervals = NULL;
    }

    return out_union;
}

void delete_union(Union_Of_Intervals union_of_intervals)
{
    free(union_of_intervals.intervals);
    union_of_intervals.intervals = NULL;
    union_of_intervals.n = 0;
}

Interval circle_coverage_on_y_0(Circle circle, Point point)
{
    Interval interval_out;
    double beta;
    double distance = dist_point_point(point, circle.center);

    if (distance <= circle.radius)
        return (Interval) {-INFINITY, INFINITY};

    beta = asin(circle.radius / distance);

    Ray center_ray = ray_through_points(point, circle.center);

    double oriented_angle = oriented_angle_of_ray(center_ray);

    Ray left_ray = ray_with_oriented_angle(point ,oriented_angle - beta);
    Ray right_ray = ray_with_oriented_angle(point, oriented_angle + beta);

    interval_out.left = ray_intersection_with_y_0(left_ray);
    interval_out.right = ray_intersection_with_y_0(right_ray);

    return interval_out;
}