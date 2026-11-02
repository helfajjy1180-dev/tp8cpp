
#include <iostream>
#include "SortieAudio.cpp"
using namespace std;

int main() {
    SortieAudio* sorties[3];

    sorties[0] = new HautParleur();
    sorties[1] = new CasqueBT();
    sorties[2] = new SortieHDMI();

    for (int i = 0; i < 3; i++) {
        cout << "\n--- Test du peripherique "
             << i + 1 << " ---" << endl;

        tester(sorties[i]);
    }

    for (int i = 0; i < 3; i++) {
        delete sorties[i];
    }

    return 0;
}
