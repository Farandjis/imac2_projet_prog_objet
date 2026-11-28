//
// Created by Matthieu on 26/11/2026.
//

#ifndef PROJET_FRAME_H
#define PROJET_FRAME_H
#include <cassert>
#include <vector>
#include <exception>
#include <string>
#include <cmath>

class AddFrameException : public std::exception {
    private:
        std::string m_what;

    public:
        AddFrameException(const std::string& message) noexcept : m_what(message) {

        }

        const char* what() const noexcept override {
            return m_what.c_str();
        }
};

template < typename T, int n >
 class Frame {
    public:
        std::vector<std::vector<T>> vecteurs;

    /*
     * j'ai rencontré un pb, explication par gémini :
    * Quand tu mets origine = parOrigine; à l'intérieur des accolades { } du constructeur, C++ considère que c'est une assignation.
    * Juste avant d'entrer dans ces accolades, C++ a déjà appelé en cachette le constructeur vide Vector() pour créer origine, axeX, axeY et axeZ.
    * Il crée donc des objets vides pour ensuite les écraser avec tes paramètres.
    *
    * Pour faire une vraie initialisation (ce que ton erreur réclame et qui est plus performant),
    * il faut utiliser une liste d'initialisation avec la syntaxe des deux-points : juste avant les accolades.
    */
    Frame()
    {
        vecteurs = std::vector<std::vector<T>>();
    }

    Frame(Frame const& frame) {
        vecteurs = frame.vecteurs;
    }

    ~Frame() {
    }

    Frame& operator=(const Frame& autre) {
        if (this != &autre) {
            vecteurs = autre.vecteurs; // ça copie très bien selon Gemini, pas besoin de faire une boucle
        }
        return *this;
    }

    Frame operator+(const Frame& autre) const{
        Frame temp = Frame(*this);
        temp.vecteurs.insert(temp.vecteurs.end(), autre.vecteurs.begin(), autre.vecteurs.end());
        return temp;
    }

    int size() {
        return vecteurs.size();
    }

    void add(std::vector<T>& v) {
        if (v.size() != n) {
            throw AddFrameException(
            "Erreur : la taille du vecteur (" + std::to_string(v.size()) +
            ") ne correspond pas a la dimension du frame (" + std::to_string(n) + ")."
            );
        }

        // on vérifie que le vecteur ne soit pas nul
        bool vecteurEstNul = true;
        for (int i = 0; i < n; i++) {

            if (v[i] != 0) {
                vecteurEstNul = false;
                break;
            }
        }

        assert(!vecteurEstNul);

        vecteurs.push_back(v);
    }

    // A CONTINUER =========================================================================

    double quality_measure(const std::vector<T>& v) {

        // on vérifie que le vecteur ne soit pas nul
        bool vecteurEstNul = true;
        for (int i = 0; i < n; i++) {

            if (v[i] != 0) {
                vecteurEstNul = false;
                break;
            }
        }
        assert(!vecteurEstNul);

        double max = -2;

        assert(v.size() == n);
        for (std::vector<T> d :vecteurs) {
            assert(d.size() == v.size());
            double num = 0;
            double denum_d = 0; // je ne sais pas trop comment expliquer mais c'est la première partie de notre calcul (cf plus haut dans le code pour la version Frame3D plus clair)
            double denum_v = 0;
            for (int i = 0; i < n; i++) {
                num += (d[i] * v[i]);
                denum_d += (d[i] * d[i]);
                denum_v += (v[i] * v[i]);
            }

            double denum = sqrt(denum_d) * sqrt(denum_v);
            double res = num / denum;

            if (res > max) {
                max = res;
            }
        }

        return max;
    }

    double quality_measure_bool(const std::vector<bool>& v) {

        // on vérifie que le vecteur ne soit pas nul
        bool vecteurEstNul = true;
        for (int i = 0; i < n; i++) {

            if (v[i] != 0) {
                vecteurEstNul = false;
                break;
            }
        }
        assert(!vecteurEstNul);

        double max = -2;

        assert(v.size() == n);
        for (std::vector<T> d :vecteurs) {
            assert(d.size() == v.size());

            int interDV = 0; // nb de cases true en commun
            int unionDV = 0; // nb cases true en faisant l'union de d et v
            for (int i = 0; i < n; i++) {
                interDV += (d[i] == v[i] && d[i] == true) ? 1 : 0; // +1 si en commun
                unionDV += (d[i] == true || v[i] == true) ? 1 : 0; // +1 si l'un des deux a true
            }

            double res = 0;
            if (unionDV != 0) {
                res = (double) interDV / (double) unionDV;
            }

            if (res > max) {
                max = res;
            }
        }

        return max;
    }
};

#endif //PROJET_FRAME_H