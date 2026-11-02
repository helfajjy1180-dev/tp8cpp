
#include "Lumiere.cpp"

int main() {
    lumieres.push_back(
        make_unique<LumiereDirectionnelle>(Vec3{0, -1, 0}, 2.0f)
    );

    lumieres.push_back(
        make_unique<LumierePonctuelle>(Vec3{0, 0, 0}, 0.1f)
    );

    lumieres.push_back(
        make_unique<LumiereSpot>(
            Vec3{0, 0, 5},
            Vec3{0, 0, -1},
            30.0f
        )
    );

    Vec3 points[] = {
        {1, 0, 0},
        {0, 0, 2},
        {0, 0, 4}
    };

    for (int i = 0; i < 3; i++) {
        cout << "Eclairage du point " << i + 1 << " : "
             << calculerEclairage(points[i]) << endl;
    }

    return 0;
}
