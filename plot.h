#ifndef PLOT_H
#define PLOT_H

#include "funciones.h"
#include <QDialog>
#include <QTimer>
#include <QFile>

namespace Ui {
class Plot;
}

class Plot : public QDialog
{
    Q_OBJECT

public:
    explicit Plot(QWidget *parent = 0);
    ~Plot();

    void setFuncion(QString funcion);
    void setAlgVel(int velocidad);
    void setVelocidadPart(int velocidad);
    void setNoParticulas(int noParticulas);
    void setMinimo(bool minimo);
    void setDec(float decCognitiva,float decSocial,float decInercia);
    void setConstriccion(bool constriccion);
    void setIteraciones(bool Limite,int Maximo);
    void setValores(float cognitiva,float social,float inercia);
    void Graficar(int resolucion);

private slots:
    void actualizar();
    void on_pushButtonEjecutar_clicked();

    void on_radioButtonPuntos_clicked();

    void on_radioButtonMallaColor_clicked();

    void on_radioButtonMallaSColor_clicked();

    void on_horizontalSliderRes_valueChanged(int value);

    void on_doubleSpinBoxRes_valueChanged(double arg1);

private:
    Ui::Plot *ui;

    QString resultados;
    float promedio;
    int numIni;

    QString func;
    int velAlg;
    int iter;
    int maxIter;
    bool limIter;

    int noPart;
    bool min;
    float ine;
    float cog;
    float soc;
    int velPart;

    bool constric;

    float decIne;
    float decCog;
    float decSoc;

    QTimer *actualiza;
    Qwt3D::GridPlot *plot;

    Parabolic *parabolic;
    Particulas *particulas;

    void resizeEvent(QResizeEvent * event);
};

#endif // PLOT_H
