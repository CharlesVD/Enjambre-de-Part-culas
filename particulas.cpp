#include "particulas.h"

using namespace Qwt3D;

Particulas::Particulas()
{
    configurar(true,5,-5,5,-5,5,2,1,2,1,1.4,0.9,false,10);
}

Particulas::~Particulas()
{

}

void Particulas::drawBegin()
{

}

void Particulas::drawEnd()
{

}

void Particulas::draw(const Triple &)
{
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(1,0,0);
    glVertex3f(xGlob,yGlob,zGlob);
    glEnd();

    if(!opt)
    {
        glPointSize(4);
        glBegin(GL_POINTS);

        for(int part=0;part<cantParticulas;part++)
        {
            glColor3f(aleatorio(0,1),aleatorio(0,1),aleatorio(0,1));
            glVertex3f(x[part],y[part],z[part]);
        }
        glEnd();
    }

    glPointSize(2);
//    glBegin(GL_POINTS);
//    glColor3f(0,0,0);

//    for(float i=infx;i<supx;i++)
//    {
//        for(float j=infy;j<supy;j++)
//        {
//            glVertex3f(i,j,funcion(i,j));
//        }
//    }
//    glEnd();

}

void Particulas::dibujarSoloOptimo(bool optimo)
{
    opt=optimo;
}

void Particulas::configurar(bool minima, int noParticulas, float minX, float maxX, float minY, float maxY, float cognitiva, float decCognitiva, float social, float decSocial, float inercia, float decInercia,bool constriccion,int reductorVelocidad)
{
    redVel = reductorVelocidad;
    float ajusteV=100;
    constric = constriccion;

    ine=inercia;
    cog=cognitiva;
    soc=social;

    decIne=decInercia;
    decCog=decCognitiva;
    decSoc=decSocial;

    indexE=0;

    minimo=minima;

    cantParticulas = noParticulas;
    double optimo;
    for(int part=0;part<noParticulas;part++)
    {
        infx=minX;
        supx=maxX;
        infy=minY;
        supy=maxY;

        x.append(aleatorio(infx,supx));
        y.append(aleatorio(infy,supy));
        z.append(funcion(x[x.length()-1],y[y.length()-1]));
        velx.append(aleatorio(infx/ajusteV,supx/ajusteV));
        vely.append(aleatorio(infy/ajusteV,supy/ajusteV));

        xLoc.append(x[x.length()-1]);
        yLoc.append(y[y.length()-1]);
        zLoc.append(z[z.length()-1]);

        if(part==0)
        {
            optimo=z[z.length()-1];
        }

        if(minimo)
        {
            if(z[z.length()-1]<optimo)
            {
                optimo=z[z.length()-1];
                xGlob=x[x.length()-1];
                yGlob=y[y.length()-1];
                zGlob=z[z.length()-1];
            }
        }
        else
        {
            if(z[z.length()-1]>optimo)
            {
                optimo=z[z.length()-1];
                xGlob=x[x.length()-1];
                yGlob=y[y.length()-1];
                zGlob=z[z.length()-1];
            }
        }
    }
}

float Particulas::funcion(float x,float y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    return 1;
}

void Particulas::actualizaVelocidad(int particula)
{
    float cogX=cog*aleatorio(0,1)*(xLoc[particula]-x[particula]);
    float cogY=cog*aleatorio(0,1)*(yLoc[particula]-y[particula]);
    float socX=soc*aleatorio(0,1)*(xGlob-x[particula]);
    float socY=soc*aleatorio(0,1)*(yGlob-y[particula]);

    if(constric)
    {
        float constriccion=2.0/abs(2-(cog+soc)-sqrt(pow(cog+soc,2)-4*(cog+soc)));
        velx[particula]=(constriccion*(velx[particula]+cogX+socX));
        vely[particula]=(constriccion*(vely[particula]+cogY+socY));
    }
    else
    {
        velx[particula]=(ine*velx[particula]+cogX+socX);
        vely[particula]=(ine*vely[particula]+cogY+socY);
    }

}

void Particulas::actualizaPosicion(int particula)
{
    x[particula]=x[particula]+(velx[particula]/redVel);
    y[particula]=y[particula]+(vely[particula]/redVel);

    if(x[particula]>supx)
    {
        x[particula]=supx;
    }
    if(x[particula]<infx)
    {
        x[particula]=infx;
    }
    if(y[particula]>supy)
    {
        y[particula]=supy;
    }
    if(y[particula]<infy)
    {
        y[particula]=infy;
    }
}

void Particulas::decremento()
{
    ine*=decIne;
    cog*=decCog;
    soc*=decSoc;
}

void Particulas::calcularVelMedia(int iMedia)
{
    double e=0.0;
    for(int v=0;v<velx.length()-1;v++)
    {
        e+=((velx[v]+vely[v])/2);
    }
    energia[iMedia]=e/velx.length();
}

void Particulas::actualizaParticulas()
{
    for(int part=0;part<cantParticulas;part++)
    {
        actualizaVelocidad(part);
        actualizaPosicion(part);

        z[part]=funcion(x[part],y[part]);

        if(minimo)
        {
            if(z[part]>zLoc[part])
            {
                z[part]=zLoc[part];
            }

            if(zGlob>z[part])
            {
                zGlob=z[part];
            }
        }
        else
        {
            if(z[part]<zLoc[part])
            {
                z[part]=zLoc[part];
            }

            if(zGlob<z[part])
            {
                zGlob=z[part];
            }
        }
    }

    //dispersion();
    decremento();

    draw(Qwt3D::Triple(0,0,0));
}

float Particulas::aleatorio(float min, float max)
{
    int minI = min*100000;
    int maxI = max*100000;

    float num = qrand()%( maxI-minI )+minI;
    num = num*0.00001;

    return num;
}

void Particulas::dispersion()
{
        if(indexE==5)
        {
            indexE=0;
            sEnergia=true;
        }
        calcularVelMedia(indexE);
        indexE++;

        if(sEnergia==true && energia[0]==energia[1])
        {
            dispersar=true;
            ine=1.4;
            cog=2;
        }

        if(sEnergia==true && (energia[0]>0.001 && energia[1]>0.001 && energia[2]>0.001 && energia[3]>0.001  && energia[4]>0.001) )
        {
            dispersar=false;
        }

        if(dispersar==false)
        {
            ine-=ine/100;
            cog-=cog/100;
        }
        else
        {
            ine+=ine/100;
            cog+=cog/100;
        }
}

void Particulas::redicirEspacio(double espacio)
{
    infx*=espacio;
    infy*=espacio;

    supx*=espacio;
    supy*=espacio;

    infx= xGlob-infx;
    supx= xGlob+supx;

    infy= yGlob-infy;
    supy= yGlob+supy;
}

float Particulas::getMejor()
{
    return zGlob;
}
