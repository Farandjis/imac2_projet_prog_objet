#include <cassert>
#include <iostream>
#include <vector>
#include <cmath>

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

    Frame3D operator+(const Frame3D& autre) const{
        Frame3D temp = Frame3D(*this);
        temp.vecteurs.insert(temp.vecteurs.end(), autre.vecteurs.begin(), autre.vecteurs.end());
        return temp;
    }

    int size() {
        return vecteurs.size();
    }

    void add(std::vector<double>& v) {
        assert(v.size() == 3);
        assert(v[0] != 0.0 || v[1] != 0.0 || v[2] != 0.0);

        Vector vecXYZ = Vector();
        vecXYZ.x = v[0];
        vecXYZ.y = v[1];
        vecXYZ.z = v[2];

        vecteurs.push_back(vecXYZ);
    }

    double quality_measure(const std::vector<double>& v) {
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
};


int test_p1f() {
    Frame3D f1;

    // 1. On remplit notre cadre avec deux vecteurs très simples
    std::vector<double> vec1 = {1.0, 0.0, 0.0}; // Axe X
    std::vector<double> vec2 = {0.0, 1.0, 0.0}; // Axe Y

    f1.add(vec1);
    f1.add(vec2);

    std::cout << "=== TESTS DE LA MESURE DE QUALITE ===" << std::endl;

    // --- TEST 1 : Un vecteur parfait ---
    // Ce vecteur est identique à vec1, l'alignement est total.
    std::vector<double> cible_parfaite = {1.0, 0.0, 0.0};
    double res1 = f1.quality_measure(cible_parfaite);

    std::cout << "\nTest 1 (Cible alignee sur X) : " << res1 << std::endl;
    std::cout << "-> Attendu : 1.0 (car l'angle est de 0 degre, cos(0) = 1)" << std::endl;


    // --- TEST 2 : Un vecteur intermédiaire ---
    // Ce vecteur pointe à 45 degrés (pile entre X et Y).
    std::vector<double> cible_diagonale = {1.0, 1.0, 0.0};
    double res2 = f1.quality_measure(cible_diagonale);

    std::cout << "\nTest 2 (Cible a 45 degres) : " << res2 << std::endl;
    std::cout << "-> Attendu : ~0.707 (ce qui correspond a 1/sqrt(2), le cosinus de 45 degres)" << std::endl;


    // --- TEST 3 : Le vecteur de ton énoncé (Question h) ---
    // Ton énoncé demande de tester avec [1/sqrt(3), 1/sqrt(3), 1/sqrt(3)]
    std::vector<double> cible_enonce = {1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0)};
    double res3 = f1.quality_measure(cible_enonce);

    std::cout << "\nTest 3 (Vecteur de l'enonce) : " << res3 << std::endl;
    std::cout << "-> Attendu : ~0.577 (soit 1/sqrt(3))" << std::endl;

    return 0;
}


void test_p1h() {
    std::cout << "--- Initialisation des trames ---" << std::endl;

    Frame3D f1;
    std::vector<double> v1_1 = {1.0, 0.0, 0.0};   f1.add(v1_1);
    std::vector<double> v1_2 = {-1.0, 0.0, 0.0};  f1.add(v1_2);
    std::vector<double> v1_3 = {0.0, 1.0, 0.0};   f1.add(v1_3);
    std::vector<double> v1_4 = {0.0, -1.0, 0.0};  f1.add(v1_4);
    std::vector<double> v1_5 = {0.0, 0.0, 1.0};   f1.add(v1_5);
    std::vector<double> v1_6 = {0.0, 0.0, -1.0};  f1.add(v1_6);

    Frame3D f2;
    std::vector<double> v2_1 = {1.0, 0.0, 0.0}; f2.add(v2_1);
    std::vector<double> v2_2 = {0.0, 1.0, 0.0}; f2.add(v2_2);
    std::vector<double> v2_3 = {0.0, 0.0, 1.0}; f2.add(v2_3);
    std::vector<double> v2_4 = {-1.0/sqrt(3.0), -1.0/sqrt(3.0), -1.0/sqrt(3.0)}; f2.add(v2_4);

    Frame3D f3 = f1 + f2;

    std::vector<double> cible1 = {1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0)};
    std::vector<double> cible2 = {1.0 - 1.0/sqrt(3.0), -1.0/sqrt(3.0), -1.0/sqrt(3.0)};

    std::cout << "\n=== EVALUATION SUR LA CIBLE 1 ===" << std::endl;
    std::cout << "F1 -> Qualite : " << f1.quality_measure(cible1)
              << " | Normalisee : " << f1.quality_measure(cible1) / f1.size() << std::endl;
    std::cout << "F2 -> Qualite : " << f2.quality_measure(cible1)
              << " | Normalisee : " << f2.quality_measure(cible1) / f2.size() << std::endl;
    std::cout << "F3 -> Qualite : " << f3.quality_measure(cible1)
              << " | Normalisee : " << f3.quality_measure(cible1) / f3.size() << std::endl;

    std::cout << "\n=== EVALUATION SUR LA CIBLE 2 ===" << std::endl;
    std::cout << "F1 -> Qualite : " << f1.quality_measure(cible2)
              << " | Normalisee : " << f1.quality_measure(cible2) / f1.size() << std::endl;
    std::cout << "F2 -> Qualite : " << f2.quality_measure(cible2)
              << " | Normalisee : " << f2.quality_measure(cible2) / f2.size() << std::endl;
    std::cout << "F3 -> Qualite : " << f3.quality_measure(cible2)
              << " | Normalisee : " << f3.quality_measure(cible2) / f3.size() << std::endl;

    /*
     * https://www.ultralytics.com/fr/glossary/normalization
     * "La normalisation consiste à remettre les valeurs numériques à une échelle commune afin qu’aucune caractéristique
     * ne domine un modèle en raison de son unité"
     *
     *Ici la caratéristique qui domine, c'est la taille de la frame (le nombre de vecteur).
     *
     * Nous remarquons que pour la cible 1, la qualité de F1 F2 sont égaux, sauf sur la version normalisé où c'est F2 qui domine.
     * Même constat pour la cible 2, où F3 normalisé est loins derrière alors que c'était pareil pour F1 quand c'était non normalisé
     *
     * La version normalisé, sur une échelle commune aux trois Frame, nous montre vraiment quel est Frame est la meilleur
     */
}


// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the <b>lang</b> variable name to see how CLion can help you rename it.

    Frame3D frame;

    std::vector<double> v = {5.0, 2.0, 3.0};
    frame.add(v);
    v = {9,8,7};
    frame.add(v);

    Frame3D frame2 = Frame3D(frame);
    v = {5.5,10,7};
    frame2.add(v);

    frame = frame + frame2;

    test_p1h();
    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}