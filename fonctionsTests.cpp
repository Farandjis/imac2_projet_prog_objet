//
// Created by Matthieu on 26/11/2026.
//


#include <iostream>
#include <cmath>
#include "Frame3D.h"
#include "Frame.h"
#include "fonctionsTests.h"

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