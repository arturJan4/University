#include <stdexcept>
#include <cmath>
#include "geometria.h"

constexpr double ACCEPTABLE_ERROR = 0.0000001;

//KONSTRUKTORY PUNKTU
punkt::punkt(const double x, const double y)
        : x(x), y(y){}

punkt::punkt(const punkt &point, const wektor &vector)
: x(point.x + vector.dx), y(point.y + vector.dy){}

//KONSTRUKTORY WEKTORA

wektor::wektor(const double dx, const double dy)
: dx(dx), dy(dy) {}

//KONSTRUKTORY PROSTEJ

prosta::prosta(const punkt &p1, const punkt &p2) {
    /*
    a = y2 - y1
    b = x1 - x2
    c = x2 * y1 - x1 * y2
 prosta przechodzaca prez dwa punkty
 */

    if(p1.x == p2.x && p1.y == p2.y)
    {
        throw std::invalid_argument("nie można jednoznacznie utworzyć prostej");
    }
    this->a = p2.y - p1.y;
    this->b = p1.x - p2.x;
    this->c = p2.x * p1.y - p1.x * p2.y;

    normalizuj();
}

prosta::prosta(double A, double B, double C)
: a(A), b(B), c(C)
{
    if(a == 0 && b == 0)
        throw std::invalid_argument("nie można jednoznacznie utworzyć prostej(A=B=0)");

    normalizuj();
}

 prosta::prosta(const wektor &vector)
{
    if(vector.dx == 0 && vector.dy == 0)
        throw std::invalid_argument("nie można jednoznacznie utworzyć prostej(wektor 0,0)");
    /*
     prosta prostopadla do wektora
    */
    double wsp_prostopadlej = (-1 * (vector.dx / vector.dy));
    this->a = wsp_prostopadlej;
    this->b = -1;
    this->c = 0;
    normalizuj();
}
prosta::prosta(const prosta &line, const wektor &vector)
{
    /*
    * przesuniecie o wektor
    * y = a(x-x0) + (b + y0)
    */
    this->a = line.getA();
    this->b = line.getB();
    this->c = line.getC() - (line.getA() * vector.dx + vector.dy);
    normalizuj();
}

prosta::prosta()
{
    this->a = 1;
    this->b = 1;
    this->c = 0;
}

//METODY PROSTEJ
double prosta::getA() const {
    return this->a;
}

double prosta::getB() const {
    return this->b;
}

double prosta::getC() const {
    return this->c;
}


bool prosta::czyProstopadly(const wektor &vector) {

    /*
     * y = - (a/b)x - (a/b)c
     * a1 * a2 = -1
     */
    double aVectora = vector.dy/vector.dx;
    double aLinii = wsp_kierunkowy_prostej(*this);

    return porownaj(aVectora * aLinii,  -1.0, ACCEPTABLE_ERROR);
}

bool prosta::czyRownolegly(const wektor &vector) {
    /*
    * y = - (a/b)x - (a/b)c
    * a1 = a2
     */
    double aVectora = vector.dy/vector.dx;
    double aLinii = wsp_kierunkowy_prostej(*this);

    return porownaj(aVectora, aLinii, ACCEPTABLE_ERROR);
}

bool prosta::czyLezyNaProstej(const punkt &point) {
    /*
     * Ax + By + C < eps
     */
    return porownaj(this->a * point.x + this->b * point.y + this->c, 0.0, ACCEPTABLE_ERROR);
}

void prosta::normalizuj()
{
    if(this->a == 0 && this->b == 0)
        throw std::invalid_argument("A = 0, B = 0 nie ma takiej prostej");
    int factor;
    if(this->c < 0)
        factor = 1;
    else
        factor = -1;

    double mnoznik = factor / sqrt((this->a * this->a) + (this->b * this->b));
    this->a *= mnoznik;
    this->b *= mnoznik;
    this->c *= mnoznik;
}

//FUNKCJE GLOBALNE
wektor dodaj_wektory(const wektor &vec1, const wektor &vec2) {
    return wektor(vec1.dx + vec2.dx, vec1.dy + vec2.dy);
}

punkt punktPrzeciecia(const prosta &ln1, const prosta &ln2) {
   /*
    * D = A1 * B2 - A2 * B1
    * D < eps -> sa rownolegle
    * w p.p
    * x = (B1*C2 - B2*C1)/D
    * y = -(A1*C2 - A2*C1)/D
    */

   double D = ln1.getA() * ln2.getB() - ln2.getA() * ln1.getB();

   if(porownaj(D,0.0,ACCEPTABLE_ERROR))
       throw std::invalid_argument("linie sa rownolegle");

   double x = (ln1.getB() * ln2.getC() - ln2.getB() * ln1.getC())/D;
   double y = -((ln1.getA() * ln2.getC() - ln2.getA() * ln1.getC())/D);

   return punkt(x,y);
}

bool czyRownolegle(const prosta &ln1, const prosta &ln2) {
    double D = ln1.getA() * ln2.getB() - ln2.getA() * ln1.getB();

    return(porownaj(D,0.0,ACCEPTABLE_ERROR));
}

bool czyProstopadle(const prosta &ln1, const prosta &ln2) {
    /*
     * A1*A2 + B1*B2 < eps
     */
    double rownanie = ln1.getA() * ln2.getA() + ln1.getB() * ln2.getB();

    return(porownaj(rownanie, 0.0, ACCEPTABLE_ERROR));
}

bool porownaj(const double& arg1,const double& arg2,const double epsError)
{
    return std::abs(arg1 - arg2) < epsError;
}

double wsp_kierunkowy_prostej(const prosta &ln)
{
    if(ln.getB() == 0.0)
        throw std::invalid_argument("B = 0, dzielenie przez zero");
    //przeksztalcenie By = -Ax - C
    return -1 * (ln.getA()/ln.getB());
}



