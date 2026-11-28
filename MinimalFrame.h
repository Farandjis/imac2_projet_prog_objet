//
// Created by Matthieu on 28/11/2026.
//

#ifndef PROJET_MINIMALFRAME_H
#define PROJET_MINIMALFRAME_H
#include "Frame.h"

template < typename T, int n >
class MinimalFrame : public Frame<T,n> {
    public:

        // on doit la remettre même si elle paraît inutile (vu qu'on a le constructeur de la classe mère)
        // car on a un constructeur de copie. Le programme ne comprendrait pas pk on a un constructeur de copie mais pas
        // un constructeur normal
        MinimalFrame() {}

        MinimalFrame(Frame<T,n> const& frame) {
            for (std::vector<T> v : frame.vecteurs) {
                add(v);
            }
        }

        void add(std::vector<T>& v) {

            // on vérifie juste si le vecteur est déjà présent dans la liste.
            // si oui, erreur
            // si non, on appel la méthode add de la classe mère qui fait déjà très bien son travail toute seule

            for (std::vector<T> const& d : this->vecteurs ) {
                if (d == v) {
                    return; // le vecteur existe déjà
                }
            }

            Frame<T, n>::add(v);
        }
};


#endif //PROJET_MINIMALFRAME_H