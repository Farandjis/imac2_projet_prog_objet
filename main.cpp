#include <iostream>
#include <vector>

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

class Frame3D {
    public:
        std::vector<Vector> vecteurs;

    /*
     * j'ai rencontré un pb, explication par gémini :
    * Quand tu mets origine = parOrigine; à l'intérieur des accolades { } du constructeur, C++ considère que c'est une assignation.
    * Juste avant d'entrer dans ces accolades, C++ a déjà appelé en cachette le constructeur vide Vector() pour créer origine, axeX, axeY et axeZ.
    * Il crée donc des objets vides pour ensuite les écraser avec tes paramètres.
    *
    * Pour faire une vraie initialisation (ce que ton erreur réclame et qui est plus performant),
    * il faut utiliser une liste d'initialisation avec la syntaxe des deux-points : juste avant les accolades.
    */
    Frame3D()
    {
        vecteurs = std::vector<Vector>();
    }

    Frame3D(Frame3D const& frame) {
        vecteurs = frame.vecteurs;
    }

    ~Frame3D() {
    }

    Frame3D& operator=(const Frame3D& autre) {
        if (this != &autre) {
            vecteurs = autre.vecteurs; // ça copie très bien selon Gemini, pas besoin de faire une boucle
        }
        return *this;
    }

    int size() {
        return vecteurs.size();
    }
};


// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the <b>lang</b> variable name to see how CLion can help you rename it.


    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}