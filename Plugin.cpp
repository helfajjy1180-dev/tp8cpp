
#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Plugin {
public:
    virtual string nom() const = 0;
    virtual string traiter(const string& texte) = 0;

    virtual ~Plugin() {}

    static unique_ptr<Plugin> creerPlugin(const string& type);
};

class CorrecteurOrthographique : public Plugin {
public:
    string nom() const override {
        return "Correcteur orthographique";
    }

    string traiter(const string& texte) override {
        string resultat = texte;
        string::size_type pos;

        while ((pos = resultat.find("bonjor")) != string::npos)
            resultat.replace(pos, 6, "bonjour");

        while ((pos = resultat.find("salu")) != string::npos)
            resultat.replace(pos, 4, "salut");

        while ((pos = resultat.find("mercie")) != string::npos)
            resultat.replace(pos, 6, "merci");

        return resultat;
    }
};

class TraducteurAnglais : public Plugin {
public:
    string nom() const override {
        return "Traducteur anglais";
    }

    string traiter(const string& texte) override {
        string resultat = texte;
        string::size_type pos;

        while ((pos = resultat.find("bonjour")) != string::npos)
            resultat.replace(pos, 7, "hello");

        while ((pos = resultat.find("merci")) != string::npos)
            resultat.replace(pos, 5, "thank you");

        while ((pos = resultat.find("salut")) != string::npos)
            resultat.replace(pos, 5, "hi");

        while ((pos = resultat.find("monde")) != string::npos)
            resultat.replace(pos, 5, "world");

        return resultat;
    }
};

class AnalyseurStyle : public Plugin {
public:
    string nom() const override {
        return "Analyseur de style";
    }

    string traiter(const string& texte) override {
        string resultat = texte;
        int phrasesLongues = 0;
        int longueur = 0;

        for (char c : texte) {
            if (c == '.' || c == '!' || c == '?') {
                if (longueur > 80)
                    phrasesLongues++;

                longueur = 0;
            } else {
                longueur++;
            }
        }

        if (longueur > 80)
            phrasesLongues++;

        resultat += "\n[Analyse de style] ";
        resultat += "Nombre de phrases trop longues : ";
        resultat += to_string(phrasesLongues);

        return resultat;
    }
};

unique_ptr<Plugin> Plugin::creerPlugin(const string& type) {
    if (type == "correcteur")
        return make_unique<CorrecteurOrthographique>();

    if (type == "traducteur")
        return make_unique<TraducteurAnglais>();

    if (type == "analyseur")
        return make_unique<AnalyseurStyle>();

    return nullptr;
}

