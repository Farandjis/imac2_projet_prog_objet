#include <cassert>
#include <iostream>
#include <vector>
#include <cmath>

/* USAGE DE L'IA :
 * J'ai respecté la consigne et développé moi même ce projet.
 * Toutefois, j'ai utilisé Gemini pour certaines tâches tels que :
 *      - retrouver plus facilement les lignes de code générant des plantages et autres problèmes
 *      - créer des fonctions de test
 *
 **/


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
        assert(v.size() == n);

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

void test_p2_quality_measure() {
    std::cout << "\n=============================================" << std::endl;
    std::cout << "--- TESTS PARTIE 2 : TEMPLATE FRAME<T, n> ---" << std::endl;
    std::cout << "=============================================\n" << std::endl;

    // On recrée F1 de la partie 1, mais avec la classe générique
    Frame<double, 3> f1_gen;
    std::vector<double> v1_1 = {1.0, 0.0, 0.0};   f1_gen.add(v1_1);
    std::vector<double> v1_2 = {-1.0, 0.0, 0.0};  f1_gen.add(v1_2);
    std::vector<double> v1_3 = {0.0, 1.0, 0.0};   f1_gen.add(v1_3);
    std::vector<double> v1_4 = {0.0, -1.0, 0.0};  f1_gen.add(v1_4);
    std::vector<double> v1_5 = {0.0, 0.0, 1.0};   f1_gen.add(v1_5);
    std::vector<double> v1_6 = {0.0, 0.0, -1.0};  f1_gen.add(v1_6);

    // On recrée F2 de la partie 1, avec la classe générique
    Frame<double, 3> f2_gen;
    std::vector<double> v2_1 = {1.0, 0.0, 0.0}; f2_gen.add(v2_1);
    std::vector<double> v2_2 = {0.0, 1.0, 0.0}; f2_gen.add(v2_2);
    std::vector<double> v2_3 = {0.0, 0.0, 1.0}; f2_gen.add(v2_3);
    std::vector<double> v2_4 = {-1.0/sqrt(3.0), -1.0/sqrt(3.0), -1.0/sqrt(3.0)}; f2_gen.add(v2_4);

    // Les mêmes cibles que dans la partie 1
    std::vector<double> cible1 = {1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0)};
    std::vector<double> cible2 = {1.0 - 1.0/sqrt(3.0), -1.0/sqrt(3.0), -1.0/sqrt(3.0)};

    std::cout << "--- Cible 1 : Comparaison des scores ---" << std::endl;
    std::cout << "Attendu (F1) : 0.57735  |  Obtenu : " << f1_gen.quality_measure(cible1) << std::endl;
    std::cout << "Attendu (F2) : 0.57735  |  Obtenu : " << f2_gen.quality_measure(cible1) << std::endl;

    std::cout << "\n--- Cible 2 : Comparaison des scores ---" << std::endl;
    std::cout << "Attendu (F1) : 0.627963 |  Obtenu : " << f1_gen.quality_measure(cible2) << std::endl;
    std::cout << "Attendu (F2) : 0.459701 |  Obtenu : " << f2_gen.quality_measure(cible2) << std::endl;

    std::cout << "\n(Si les resultats 'Attendu' et 'Obtenu' sont identiques, ta boucle for de dimension n est validee !)\n" << std::endl;
}

void test_comparaison_frame3d_vs_frame() {
    std::cout << "\n=== TEST COMPARATIF : Frame3D vs Frame<double, 3> ===" << std::endl;

    // 1. On instancie les deux versions
    Frame3D f_ancienne;
    Frame<double, 3> f_nouvelle;

    // 2. On crée quelques vecteurs de test
    std::vector<double> vec1 = {1.5, -2.0, 3.1};
    std::vector<double> vec2 = {4.0, 0.5, -1.0};
    std::vector<double> vec3 = {-0.5, 2.2, 5.0};

    // 3. On les ajoute aux DEUX cadres
    f_ancienne.add(vec1);
    f_ancienne.add(vec2);
    f_ancienne.add(vec3);

    f_nouvelle.add(vec1);
    f_nouvelle.add(vec2);
    f_nouvelle.add(vec3);

    // 4. On crée un vecteur cible pour tester la mesure de qualité
    std::vector<double> cible = {2.0, 2.0, 2.0};

    // 5. On calcule avec les deux méthodes
    double resultat_ancien = f_ancienne.quality_measure(cible);
    double resultat_nouveau = f_nouvelle.quality_measure(cible);

    // 6. On affiche le face-à-face
    std::cout << "Resultat avec Frame3D (ancienne methode) : " << resultat_ancien << std::endl;
    std::cout << "Resultat avec Frame (nouvelle methode)   : " << resultat_nouveau << std::endl;

    if (std::abs(resultat_ancien - resultat_nouveau) < 0.000001) {
        std::cout << "-> SUCCES : Les deux classes fonctionnent EXACTEMENT pareil !" << std::endl;
    } else {
        std::cout << "-> ERREUR : Il y a une difference de calcul." << std::endl;
    }
}

void test_p2_bool() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "--- TESTS PARTIE 2.c : FRAME<bool, n> (6D et 8D) ---" << std::endl;
    std::cout << "=======================================================\n" << std::endl;

    // --- TEST 1 : En 6 dimensions (n = 6) ---
    Frame<bool, 6> f_bool_6d;

    std::vector<bool> d1 = {true, false, true, true, false, false};  // {0, 2, 3}
    std::vector<bool> d2 = {true, true, false, true, true, false};   // {0, 1, 3, 4}
    std::vector<bool> d3 = {false, false, false, false, false, true}; // {5}

    f_bool_6d.add(d1);
    f_bool_6d.add(d2);
    f_bool_6d.add(d3);

    std::vector<bool> cible_6d = {true, true, false, true, false, false}; // {0, 1, 3}
    // d1 vs cible : inter = {0, 3} (2), union = {0, 1, 2, 3} (4) -> 2/4 = 0.5
    // d2 vs cible : inter = {0, 1, 3} (3), union = {0, 1, 3, 4} (4) -> 3/4 = 0.75
    // d3 vs cible : inter = {} (0), union = {0, 1, 3, 5} (4) -> 0/4 = 0.0
    std::cout << "Test 1 (Dimension 6) -> Attendu : 0.75 | Obtenu : "
              << f_bool_6d.quality_measure_bool(cible_6d) << std::endl;


    // --- TEST 2 : En 8 dimensions (n = 8) ---
    Frame<bool, 8> f_bool_8d;

    std::vector<bool> v1 = {true, false, false, false, true, false, false, true};  // {0, 4, 7}
    std::vector<bool> v2 = {false, true, true, false, false, true, true, false};   // {1, 2, 5, 6}

    f_bool_8d.add(v1);
    f_bool_8d.add(v2);

    std::vector<bool> cible_8d = {true, false, false, false, false, false, false, true}; // {0, 7}
    // v1 vs cible : inter = {0, 7} (2), union = {0, 4, 7} (3) -> 2/3 = 0.666667
    // v2 vs cible : inter = {} (0), union = 6 -> 0.0
    std::cout << "Test 2 (Dimension 8) -> Attendu : ~0.666667 | Obtenu : "
              << f_bool_8d.quality_measure_bool(cible_8d) << std::endl;
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

    // test_p1h();
    // test_p2_quality_measure();
    // test_comparaison_frame3d_vs_frame();
    test_p2_bool();
    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}