#ifndef ZAD2_GEOMETRIA_H
#define ZAD2_GEOMETRIA_H

class punkt;
class wektor;
class prosta;

class punkt
{
public:
    const double x = 0.0;
    const double y = 0.0;

    punkt() = default;
    punkt(double x, double y);
    punkt(const punkt& point, const wektor& vector);//przesuniecie o wektor
    punkt(const punkt&) = default;

    punkt& operator= (const punkt&) = delete;
};

class wektor
{
public:
    const double dx = 0.0;
    const double dy = 0.0;

    wektor() = default;
    wektor(double dx, double dy);
    wektor(const wektor&) = default;
    wektor& operator= (const wektor&) = delete;
};

class prosta
{
public:
    prosta(const punkt& p1, const punkt& p2);
    explicit prosta(const wektor& vector);
    prosta(double A, double B, double C);
    prosta(const prosta& line, const wektor& vector);
    prosta();

    prosta(const prosta&) = delete;
    prosta& operator= (const prosta&) = delete;

    double getA() const;
    double getB() const;
    double getC() const;

    bool czyProstopadly(const wektor& vector);
    bool czyRownolegly(const wektor& vector);
    bool czyLezyNaProstej(const punkt& point);
    void normalizuj();
private:
    double a = 0;
    double b = 0;
    double c = 0;
};

wektor dodaj_wektory(const wektor& vec1, const wektor& vec2);
punkt punktPrzeciecia(const prosta& ln1, const prosta& ln2);
bool czyRownolegle(const prosta& ln1, const prosta& ln2);
bool czyProstopadle(const prosta& ln1, const prosta& ln2);
bool porownaj(const double& arg1,const double& arg2, double epsError);
double wsp_kierunkowy_prostej(const prosta& ln);

#endif //ZAD2_GEOMETRIA_H
