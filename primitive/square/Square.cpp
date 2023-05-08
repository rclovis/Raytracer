/*
** EPITECH PROJECT, 2023
** square
** File description:
** square
*/

#include "Square.hpp"
#include "Matrix.hpp"

Square::Square(libconfig::Setting &conf)
{
    int px_inf = conf.lookup("x1");
    int py_inf = conf.lookup("y1");
    int pz_inf = conf.lookup("z1");
    int px_sup = conf.lookup("x2");
    int py_sup = conf.lookup("y2");
    int pz_sup = conf.lookup("z2");
    int xr = conf.lookup("xr");
    int yr = conf.lookup("yr");
    int zr = conf.lookup("zr");
    conf.lookupValue("material", _materialName);
    point_inf = {{(float) px_inf, (float) py_inf, (float) pz_inf}};
    point_sup = {{(float) px_sup, (float) py_sup, (float) pz_sup}};
    rotation = {{(float) xr, (float) yr, (float) zr}};
}

Square::~Square()
{
}

std::vector<normalRay> Square::computeIntersection (cameraRay ray)
{
    ray = transformRay(ray, {{0.0f, 0.0f, 0.0f}}, rotation);
    std::vector<normalRay> rays;

    mat::Matrix<float, 1, 3> min;
    mat::Matrix<float, 1, 3> max;

    min(0, 0) = std::min(point_inf(0, 0), point_sup(0, 0));
    min(0, 1) = std::min(point_inf(0, 1), point_sup(0, 1));
    min(0, 2) = std::min(point_inf(0, 2), point_sup(0, 2));
    max(0, 0) = std::max(point_inf(0, 0), point_sup(0, 0));
    max(0, 1) = std::max(point_inf(0, 1), point_sup(0, 1));
    max(0, 2) = std::max(point_inf(0, 2), point_sup(0, 2));

    for (double i : {min(0, 0), max(0, 0)}) {
        if (ray.direction(0, 0) == 0)
            continue;
        float t = (i - ray.origin(0, 0)) / ray.direction(0, 0);
        if (t < 0) continue;
        mat::Matrix<float, 1, 3> p = ray.origin + ray.direction * t;
        if (p(0, 1) >= min(0, 1) && p(0, 1) <= max(0, 1) && p(0, 2) >= min(0, 2) && p(0, 2) <= max(0, 2)) {
            normalRay r;
            r.origin = p;
            r.direction = {{1.0f, 0.0f, 0.0f}};
            if (mat::dotProduct(r.direction, ray.direction) > 0)
                r.direction *= -1;
            r = convertHit(r, {{0.0f, 0.0f, 0.0f}}, rotation);
            rays.push_back(r);
        }

    }
    for (double i : {min(0, 1), max(0, 1)}) {
        if (ray.direction(0, 1) == 0)
            continue;
        float t = (i - ray.origin(0, 1)) / ray.direction(0, 1);
        if (t < 0) continue;
        mat::Matrix<float, 1, 3> p = ray.origin + ray.direction * t;
        if (p(0, 0) >= min(0, 0) && p(0, 0) <= max(0, 0) && p(0, 2) >= min(0, 2) && p(0, 2) <= max(0, 2)) {
            normalRay r;
            r.origin = p;
            r.direction = {{0.0f, 1.0f, 0.0f}};
            if (mat::dotProduct(r.direction, ray.direction) > 0)
                r.direction *= -1;
            r = convertHit(r, {{0.0f, 0.0f, 0.0f}}, rotation);
            rays.push_back(r);
        }
    }
    for (double i : {min(0, 2), max(0, 2)}) {
        if (ray.direction(0, 2) == 0)
            continue;
        float t = (i - ray.origin(0, 2)) / ray.direction(0, 2);
        if (t < 0) continue;
        mat::Matrix<float, 1, 3> p = ray.origin + ray.direction * t;
        if (p(0, 0) >= min(0, 0) && p(0, 0) <= max(0, 0) && p(0, 1) >= min(0, 1) && p(0, 1) <= max(0, 1)) {
            normalRay r;
            r.origin = p;
            r.direction = {{0.0f, 0.0f, 1.0f}};
            if (mat::dotProduct(r.direction, ray.direction) > 0)
                r.direction *= -1;
            r = convertHit(r, {{0.0f, 0.0f, 0.0f}}, rotation);
            rays.push_back(r);
        }
    }
    return rays;
}

/*
def ray_rect_prism_intersection(p1, p2, o, d):
    # Find the equations for the six planes that define the rectangular prism
    x_min = np.min([p1[0], p2[0]])
    x_max = np.max([p1[0], p2[0]])
    y_min = np.min([p1[1], p2[1]])
    y_max = np.max([p1[1], p2[1]])
    z_min = np.min([p1[2], p2[2]])
    z_max = np.max([p1[2], p2[2]])

    # Find the equation for the line that defines the ray
    l = lambda t: o + t*d

    # Find the distance from o to each intersection point with the six planes
    t_vals = []
    for x in [x_min, x_max]:
        if d[0] != 0:
            t = (x - o[0])/d[0]
            y = l(t)[1]
            z = l(t)[2]
            if y_min <= y <= y_max and z_min <= z <= z_max:
                t_vals.append(t)
    for y in [y_min, y_max]:
        if d[1] != 0:
            t = (y - o[1])/d[1]
            x = l(t)[0]
            z = l(t)[2]
            if x_min <= x <= x_max and z_min <= z <= z_max:
                t_vals.append(t)
    for z in [z_min, z_max]:
        if d[2] != 0:
            t = (z - o[2])/d[2]
            x = l(t)[0]
            y = l(t)[1]
            if x_min <= x <= x_max and y_min <= y <= y_max:
                t_vals.append(t)

    # If there are no intersection points, return None
    if len(t_vals) == 0:
        return None, None, None

    # Find the closest intersection point and the normal vector of the surface that was hit
    t_min = min(t_vals)
    p_min = l(t_min)
    if p_min[0] == x_min:
        n_min = np.array([-1, 0, 0])
    elif p_min[0] == x_max:
        n_min = np.array([1, 0, 0])
    elif p_min[1] == y_min:
        n_min = np.array([0, -1, 0])
    elif p_min[1] == y_max:
        n_min = np.array([0, 1, 0])
    elif p_min[2] == z_min:
        n_min = np.array([0, 0, -1])
    elif p_min[2] == z_max:
        n_min = np.array([0, 0, 1])

    return t_min, p_min, n_min

*/