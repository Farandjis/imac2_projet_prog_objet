#include <cassert>
#include <iostream>
#include <vector>
#include <cmath>

#include "fonctionsTests.h"
#include "Frame3D.h"
#include "Vector.h"

/* USAGE DE L'IA :
 * J'ai respecté la consigne et développé moi même ce projet.
 * Toutefois, j'ai utilisé Gemini pour certaines tâches tels que :
 *      - retrouver plus facilement les lignes de code générant des plantages et autres problèmes
 *      - créer des fonctions de test
 *
 **/








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
    // test_p2_bool();
    // test_p2d();
    test_p2e();
    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}