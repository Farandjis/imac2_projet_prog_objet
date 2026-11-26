//
// Created by Matthieu on 26/11/2026.
//

#ifndef PROJET_FRAME3D_H
#define PROJET_FRAME3D_H
#include <vector>
#include <cassert>
#include "Vector.h"
#include <cmath>

class Frame3D {
    public:
        std::vector<Vector> vecteurs;

        Frame3D();
        Frame3D(Frame3D const& frame);
        ~Frame3D();

        Frame3D& operator=(const Frame3D& autre);
        Frame3D operator+(const Frame3D& autre) const;
        int size();
        void add(std::vector<double>& v);
        double quality_measure(const std::vector<double>& v);

};


#endif //PROJET_FRAME3D_H