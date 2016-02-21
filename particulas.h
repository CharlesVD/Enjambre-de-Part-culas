/*
-------------------------------------------------
# particulas.h y particulas.cpp están basados en el código funete de:
# Inteligencia artificial avanzada por Raúl Benítez, Gerard Escudero y Samir Kanaan
# pag. 199-201
#-------------------------------------------------
*/
#ifndef PARTICULAS_H
#define PARTICULAS_H

#include <cmath>
#include "qwt3d/qwt3d_plot3d.h"
#include "qwt3d/qwt3d_parametricsurface.h"
#include "qwt3d/qwt3d_gridplot.h"
#include "qwt3d/qwt3d_function.h"
#include "qwt3d/qwt3d_color.h"

class Particulas: public Qwt3D::VertexEnrichment
{
private:

    bool minimo;
    bool constric;
    int cantParticulas;
    double energia[5];
    int indexE;
    bool sEnergia;
    bool dispersar;
    int redVel;

    //posicion y posición anterior de cada partícula
    QList <double> x;
    QList <double> y;
    QList <double> z;

    QList <double> xLoc;
    QList <double> yLoc;
    QList <double> zLoc;

    //velocidad de cada partícula
    QList <double> velx;
    QList <double> vely;

    float ine;
    float cog;
    float soc;

    float decIne;
    float decCog;
    float decSoc;

    //espacio de búsqueda
    double infx;
    double supx;
    double infy;
    double supy;


    //mejor
    bool opt;
    float xGlob;
    float yGlob;
    float zGlob;

    float aleatorio(float min, float max);
    virtual float funcion(float x,float y);
    void actualizaVelocidad(int particula);
    void actualizaPosicion(int particula);

    void calcularVelMedia(int iMedia);
public:
    Particulas();
    ~Particulas();

    Qwt3D::Enrichment* clone() const {return new Particulas(*this);}

    //void configure(double rad, double level);
    void drawBegin();
    void drawEnd();
    void draw(Qwt3D::Triple const&);
    void dibujarSoloOptimo(bool optimo);

    void actualizaParticulas();
    void decrementoInercia(bool porcentual,float decInercia);
    void decrementoCognitiva(bool porcentual,float decCognitiva);
    void decrementoSocial(bool porcentual,float decSocial);
    void decremento();
    void dispersion();
    void redicirEspacio(double espacio);

    void configurar(bool minima,int noParticulas,
                    float minX, float maxX, float minY, float maxY,
                    float cognitiva,float decCognitiva,
                    float social,float decSocial,
                    float inercia,float decInercia,bool constriccion,int reductorVelocidad);
    float getMejor();
};

#endif // PARTICULAS_H
