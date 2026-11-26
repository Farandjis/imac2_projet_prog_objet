//
// Created by Matthieu on 26/11/2026.
//

#ifndef PROJET_VECTOR_H
#define PROJET_VECTOR_H


class Vector {
public:
    double x, y, z;

    Vector() : x(0.0), y(0.0), z(0.0) {
    }

    Vector(double const& parX, double const& parY, double const& parZ) {
        x = parX;
        y = parY;
        z = parZ;

    }
};
#endif //PROJET_VECTOR_H