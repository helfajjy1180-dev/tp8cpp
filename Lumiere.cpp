
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cmath>
using namespace std;

struct Vec3 {
    float x, y, z;
};

class Lumiere {
public:
    virtual float intensite(const Vec3& position) = 0;
    virtual ~Lumiere() {}
};

class LumiereDirectionnelle : public Lumiere {
private:
    Vec3 direction;
    float couleur;

public:
    LumiereDirectionnelle(Vec3 d, float c) {
        direction = d;
        couleur = c;
    }

    float intensite(const Vec3& position) override {
        return couleur;
    }
};

class LumierePonctuelle : public Lumiere {
private:
    Vec3 position;
    float attenuation;

public:
    LumierePonctuelle(Vec3 p, float a) {
        position = p;
        attenuation = a;
    }

    float intensite(const Vec3& point) override {
        float dx = point.x - position.x;
        float dy = point.y - position.y;
        float dz = point.z - position.z;

        float distance = sqrt(dx * dx + dy * dy + dz * dz);

        return 1.0f / (1.0f + attenuation * distance * distance);
    }
};

class LumiereSpot : public Lumiere {
private:
    Vec3 position;
    Vec3 direction;
    float angle;

public:
    LumiereSpot(Vec3 p, Vec3 d, float a) {
        position = p;
        direction = d;
        angle = a;
    }

    float intensite(const Vec3& point) override {
        float dx = point.x - position.x;
        float dy = point.y - position.y;
        float dz = point.z - position.z;

        float distance = sqrt(dx * dx + dy * dy + dz * dz);

        if (distance == 0)
            return 1.0f;

        float produit = dx * direction.x
                      + dy * direction.y
                      + dz * direction.z;

        float cosAngle = produit / distance;

        if (cosAngle >= cos(angle * 3.14159f / 180.0f))
            return 1.0f / (1.0f + distance * distance);

        return 0.0f;
    }
};

vector<unique_ptr<Lumiere>> lumieres;

float calculerEclairage(const Vec3& point) {
    float total = 0;

    for (const auto& lumiere : lumieres) {
        total += lumiere->intensite(point);
    }

    return total;
}
