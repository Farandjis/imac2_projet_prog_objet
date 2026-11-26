//
// Created by Matthieu on 26/11/2026.
//

#include "Frame3D.h"




/*
 * j'ai rencontré un pb, explication par gémini :
* Quand tu mets origine = parOrigine; à l'intérieur des accolades { } du constructeur, C++ considère que c'est une assignation.
* Juste avant d'entrer dans ces accolades, C++ a déjà appelé en cachette le constructeur vide Vector() pour créer origine, axeX, axeY et axeZ.
* Il crée donc des objets vides pour ensuite les écraser avec tes paramètres.
*
* Pour faire une vraie initialisation (ce que ton erreur réclame et qui est plus performant),
* il faut utiliser une liste d'initialisation avec la syntaxe des deux-points : juste avant les accolades.
*/
Frame3D::Frame3D()
{
    vecteurs = std::vector<Vector>();
}

Frame3D::Frame3D(Frame3D const& frame) {
    vecteurs = frame.vecteurs;
}

Frame3D::~Frame3D() {
}

Frame3D& Frame3D::operator=(const Frame3D& autre) {
    if (this != &autre) {
        vecteurs = autre.vecteurs; // ça copie très bien selon Gemini, pas besoin de faire une boucle
    }
    return *this;
}

Frame3D Frame3D::operator+(const Frame3D& autre) const{
    Frame3D temp = Frame3D(*this);
    temp.vecteurs.insert(temp.vecteurs.end(), autre.vecteurs.begin(), autre.vecteurs.end());
    return temp;
}

int Frame3D::size() {
    return vecteurs.size();
}

void Frame3D::add(std::vector<double>& v) {
    assert(v.size() == 3);
    assert(v[0] != 0.0 || v[1] != 0.0 || v[2] != 0.0);

    Vector vecXYZ = Vector();
    vecXYZ.x = v[0];
    vecXYZ.y = v[1];
    vecXYZ.z = v[2];

    vecteurs.push_back(vecXYZ);
}

double Frame3D::quality_measure(const std::vector<double>& v) {
    assert(v.size() == 3);
    assert(v[0] != 0.0 || v[1] != 0.0 || v[2] != 0.0);

    double max = -2;

    for (Vector d :vecteurs) {
        double num = ((d.x * v[0]) + (d.y * v[1]) + (d.z * v[2]));
        double denum = sqrt((d.x * d.x) + (d.y * d.y) + (d.z * d.z)) * sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));;
        double res = num / denum;


        if (res > max) {
            max = res;
        }
    }

    return max;
}