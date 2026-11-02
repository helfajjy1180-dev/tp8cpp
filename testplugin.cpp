#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;    
#include "Plugin.cpp"

int main() {
    string texte;

    cout << "Entrez un texte : ";
    getline(cin, texte);

    vector<unique_ptr<Plugin>> plugins;

    plugins.push_back(Plugin::creerPlugin("correcteur"));
    plugins.push_back(Plugin::creerPlugin("traducteur"));
    plugins.push_back(Plugin::creerPlugin("analyseur"));

    for (const auto& plugin : plugins) {
        if (plugin != nullptr) {
            texte = plugin->traiter(texte);

            cout << "\nPlugin applique : "
                 << plugin->nom() << endl;

            cout << "Texte transforme :\n"
                 << texte << endl;
        }
    }

    return 0;
}
