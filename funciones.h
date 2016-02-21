/*
-------------------------------------------------
# particulas.h y particulas.cpp están basados en el código funete de:
# Inteligencia artificial avanzada por Raúl Benítez, Gerard Escudero y Samir Kanaan
# pag. 199-201
#-------------------------------------------------
*/
#ifndef FUNCIONES
#define FUNCIONES

#include "particulas.h"

using namespace Qwt3D;

class Parabolic : public Function
{
public:

    Parabolic(GridPlot& pw):Function(pw)
    {

    }

    double operator()(double x, double y)
    {
        return pow(x,2)+pow(y,2);
    }
};

class ParticulasParabolic : public Particulas
{
public:
    ParticulasParabolic()
    {

    }

    float funcion(float x, float y)
    {
        return pow(x,2)+pow(y,2);
    }
};

class Ackley : public Function
{
public:

    Ackley(GridPlot& pw):Function(pw)
    {

    }

    double operator()(double x, double y)
    {
        const double e = std::exp(1.0);
        return -20*std::exp(-0.2*sqrt(0.5*((pow(x,2)+pow(y,2)))))-std::exp(0.5*(cos(2*Qwt3D::PI*x)+cos(2*Qwt3D::PI*y)))+e+20;
    }
};

class ParticulasAckley : public Particulas
{
public:
    ParticulasAckley()
    {

    }

    float funcion(float x, float y)
    {
        const double e = std::exp(1.0);
        return -20*std::exp(-0.2*sqrt(0.5*((pow(x,2)+pow(y,2)))))-std::exp(0.5*(cos(2*Qwt3D::PI*x)+cos(2*Qwt3D::PI*y)))+e+20;
    }
};

class Circles : public Function
{
public:

    Circles(GridPlot& pw):Function(pw)
    {

    }

    double operator()(double x, double y)
    {
        return pow(pow(x,2)+pow(y,2),0.25)*(pow(sin( 50*pow((pow(x,2)+pow(y,2)),0.1) ),2)+1);
    }
};

class ParticulasCircles : public Particulas
{
public:
    ParticulasCircles()
    {

    }

    float funcion(float x, float y)
    {
        return pow(pow(x,2)+pow(y,2),0.25)*(pow(sin( 50*pow((pow(x,2)+pow(y,2)),0.1) ),2)+1);
    }
};

class Rastrigin : public Function
{
public:

    Rastrigin(GridPlot& pw):Function(pw)
    {

    }

    double operator()(double x, double y)
    {
        return (20+(pow(x,2)-(10*cos(2*Qwt3D::PI*x)))+pow(y,2)-(10*cos(2*Qwt3D::PI*y)));
    }
};

class ParticulasRastrigin: public Particulas
{
public:
    ParticulasRastrigin()
    {

    }

    float funcion(float x, float y)
    {
        return (20+(pow(x,2)-(10*cos(2*Qwt3D::PI*x)))+pow(y,2)-(10*cos(2*Qwt3D::PI*y)));
    }
};

class EqualPeaks : public Function
{
public:

    EqualPeaks(GridPlot& pw):Function(pw)
    {

    }

    double operator()(double x, double y)
    {
        return pow(cos(x),2)+pow(sin(y),2);
    }
};

class ParticulasEqualPeaks : public Particulas
{
public:
    ParticulasEqualPeaks()
    {

    }

    float funcion(float x, float y)
    {
        return pow(cos(x),2)+pow(sin(y),2);
    }
};

class Himmelblaus : public Function
{
public:

    Himmelblaus(GridPlot& pw):Function(pw)
    {

    }

    double operator()(double x, double y)
    {
        return -0.01*(200-pow((pow(x,2)+pow(y,2)-11),2)-pow((x+pow(y,2)-7),2));
    }
};

class ParticulasHimmelblaus : public Particulas
{
public:
    ParticulasHimmelblaus()
    {

    }

    float funcion(float x, float y)
    {
        return -0.01*(200-pow((pow(x,2)+pow(y,2)-11),2)-pow((x+pow(y,2)-7),2));
    }
};

class Peaks : public Function
{
public:

    Peaks(GridPlot& pw):Function(pw)
    {

    }

    double operator()(double x, double y)
    {
        const double e = std::exp(1.0);
        return 3*pow((1-x),2)*pow(e,-1*(pow(x,2)+pow(y+1,2)))-10*((x/5)-pow(x,3)-pow(y,5))*pow(e,-1*(pow(x,2)+pow(y,2)))-(1/3)*pow(e,-1*(pow(x+1,2)+pow(y,2)));
    }
};

class ParticulasPeaks : public Particulas
{
public:
    ParticulasPeaks()
    {

    }

    float funcion(float x, float y)
    {
        const double e = std::exp(1.0);
        return 3*pow((1-x),2)*pow(e,-1*(pow(x,2)+pow(y+1,2)))-10*((x/5)-pow(x,3)-pow(y,5))*pow(e,-1*(pow(x,2)+pow(y,2)))-(1/3)*pow(e,-1*(pow(x+1,2)+pow(y,2)));
    }
};

class Schaffer : public Function
{
public:

    Schaffer(GridPlot& pw):Function(pw)
    {

    }

    double operator()(double x, double y)
    {
        return 0.5+(  (pow( sin(sqrt( pow(x,2)+pow(y,2) )),2)-0.5 )  /  (pow((1+0.02*(pow(x,2)+pow(y,2))),2)));
    }
};

class ParticulasSchaffer : public Particulas
{
public:
    ParticulasSchaffer()
    {

    }

    float funcion(float x, float y)
    {
        return 0.5+(  (pow( sin(sqrt( pow(x,2)+pow(y,2) )),2)-0.5 )  /  (pow((1+0.02*(pow(x,2)+pow(y,2))),2)));
    }
};

class BananaRosenbrock : public Function
{
public:

    BananaRosenbrock(GridPlot& pw):Function(pw)
    {

    }

    double operator()(double x, double y)
    {
        return 100*pow((y-pow(x,2)),2)+(1-pow(x,2));
    }
};

class ParticulasBananaRosenbrock : public Particulas
{
public:
    ParticulasBananaRosenbrock()
    {

    }

    float funcion(float x, float y)
    {
        return 100*pow((y-pow(x,2)),2)+pow(1-x,2);
    }
};

class HardRosenbrock : public Function
{
public:

    HardRosenbrock(GridPlot& pw):Function(pw)
    {

    }

    double operator()(double x, double y)
    {
        return 0.7 * log10((1-x)*(1-x) + 10 * (y - x*x)*(y - x*x));
    }
};

class ParticulasHardRosenbrock : public Particulas
{
public:
    ParticulasHardRosenbrock()
    {

    }

    float funcion(float x, float y)
    {
        return 0.7 * log10((1-x)*(1-x) + 10 * (y - x*x)*(y - x*x));
    }
};

//class HardRosenbrock : public Function
//{
//public:

//    HardRosenbrock(GridPlot& pw):Function(pw)
//    {

//    }

//    double operator()(double x, double y)
//    {
//        return 0.7 * log10((1-x)*(1-x) + 10 * (y - x*x)*(y - x*x));
//    }
//};

//class ParticulasHardRosenbrock : public Particulas
//{
//public:
//    ParticulasHardRosenbrock()
//    {

//    }

//    float funcion(float x, float y)
//    {
//        return 0.7 * log10((1-x)*(1-x) + 10 * (y - x*x)*(y - x*x));
//    }
//};
#endif // FUNCIONES

