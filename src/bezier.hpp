#ifndef BEZIER_H
#define BEZIER_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <glm/vec4.hpp>

glm::vec4 interpol(glm::vec4 p1, glm::vec4 p2, float t)
{
    glm::vec4 pR = p1+t*(p2-p1);

    return pR;
}

glm::vec4 cubicBezier(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3, glm::vec4 p4, float t)
{
    glm::vec4 p12, p23, p34, p123, p234, pR;

    p12 = interpol(p1, p2, t);
    p23 = interpol(p2, p3, t);
    p34 = interpol(p3, p4, t);
    p123 = interpol(p12, p23, t);
    p234 = interpol(p23, p34, t);
    pR = interpol(p123, p234, t);

    return pR;
}

#endif
