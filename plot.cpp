#include "plot.h"
#include "ui_plot.h"

#include "qwt3d/qwt3d_enrichment.h"

Plot::Plot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Plot)
{
    ui->setupUi(this);

    actualiza = new QTimer(this);
    plot = new Qwt3D::GridPlot(ui->widgetPlot);

    func="Parabolic";
    noPart=10;
    iter=0;
}

Plot::~Plot()
{
    delete ui;
}

void Plot::setFuncion(QString funcion)
{
    func=funcion;
}

void Plot::setAlgVel(int velocidad)
{
    velAlg = velocidad;
}

void Plot::setVelocidadPart(int velocidad)
{
    velPart=velocidad;
}

void Plot::setNoParticulas(int noParticulas)
{
    noPart=noParticulas;
}

void Plot::setValores(float cognitiva,float social,float inercia)
{
    cog=cognitiva;
    soc=social;
    ine=inercia;
}

void Plot::setMinimo(bool minimo)
{
    min=minimo;
}

void Plot::setDec(float decCognitiva,float decSocial,float decInercia)
{
    decCog=decCognitiva;
    decSoc=decSocial;
    decIne=decInercia;
}

void Plot::setConstriccion(bool constriccion)
{
    constric = constriccion;
}

void Plot::setIteraciones(bool Limite,int Maximo)
{
    limIter=Limite;
    maxIter=Maximo;
}

void Plot::Graficar(int resolucion)
{
    Function *funcion;
    plot->setTitle(func);
    if(ui->radioButtonPuntos->isChecked())
    {
        plot->setPlotStyle(Qwt3D::POINTS);
    }
    if(ui->radioButtonMallaColor->isChecked())
    {
        plot->setPlotStyle(Qwt3D::FILLEDMESH);
    }
    if(ui->radioButtonMallaSColor->isChecked())
    {
        plot->setPlotStyle(Qwt3D::WIREFRAME);
    }
    plot->setFloorStyle(Qwt3D::FLOORISO);
    plot->setCoordinateStyle(Qwt3D::FRAME);
    plot->setRotation(45,0,45);

    for (unsigned i=0; i!=plot->coordinates()->axes.size(); ++i)
    {
      plot->coordinates()->axes[i].setMajors(5);
      plot->coordinates()->axes[i].setMinors(5);
      plot->coordinates()->axes[i].setLabelColor(RGBA(0,0,0.4));
    }

    if(func=="Parabolic")
    {
        particulas = new ParticulasParabolic();
        plot->setScale(2.5,2.5,0.5);
        funcion = new Parabolic(*plot);
    }

    if(func=="Ackley")
    {
        particulas = new ParticulasAckley();
        plot->setScale(1,1,1.5);
        funcion = new Ackley(*plot);
    }

    if(func=="Circles")
    {
        particulas = new ParticulasCircles();
        plot->setScale(1,1,2);
        funcion = new Circles(*plot);
    }

    if(func=="Rastrigin")
    {
        particulas = new ParticulasRastrigin();
        plot->setScale(5,5,0.5);
        funcion = new Rastrigin (*plot);
    }

    if(func=="Equal Peaks")
    {
        particulas = new ParticulasEqualPeaks();
        plot->setScale(1,1,7);
        funcion = new EqualPeaks(*plot);
    }

    if(func=="Himmelblaus")
    {
        particulas = new ParticulasHimmelblaus();
        plot->setScale(1,1,1);
        funcion = new Himmelblaus(*plot);
    }

    if(func=="Schaffer")
    {
        particulas = new ParticulasSchaffer();
        plot->setScale(1,1,10);
        funcion = new Schaffer(*plot);
    }

    if(func=="Peaks")
    {
        particulas = new ParticulasPeaks();
        plot->setScale(1,1,1);
        funcion = new Peaks(*plot);
    }

    if(func=="Rosenbrock 1")
    {
        particulas = new ParticulasBananaRosenbrock();
        plot->setScale(5000,5000,0.9);

        funcion = new BananaRosenbrock(*plot);
    }

    if(func=="Rosenbrock 2")
    {
        particulas = new ParticulasHardRosenbrock();
        plot->setScale(1,1,3);
        funcion = new HardRosenbrock(*plot);
    }

    funcion->setMesh(resolucion,resolucion);
    funcion->setDomain(-5,5,-5,5);
    funcion->create();
    plot->coordinates()->setTicLength(0,0);
    plot->updateGL();
}

void Plot::resizeEvent(QResizeEvent *event)
{
    if(event->isAccepted())
    {
        plot->setFixedWidth(ui->widgetPlot->width());
        plot->setFixedHeight(ui->widgetPlot->height());
    }
}

void Plot::on_pushButtonEjecutar_clicked()
{
    resultados="";
    promedio=0;
    numIni=ui->spinBoxExec->value();
    Graficar(5);
    particulas->configurar(min,noPart,-5,5,-5,5,cog,decCog,soc,decSoc,ine,decIne,constric,velPart);
    if(!actualiza->isActive())
    {
        connect(actualiza, SIGNAL(timeout()), this, SLOT(actualizar()));
        actualiza->setInterval(abs(100-velAlg));
        actualiza->start();
        ui->pushButtonEjecutar->setText("Detener");
        ui->groupBoxGra->setEnabled(false);
    }
    else
    {
        actualiza->stop();
        iter=0;
        ui->pushButtonEjecutar->setText("Ejecutar");
        particulas->dibujarSoloOptimo(true);
        plot->addEnrichment(*particulas);
        particulas->dibujarSoloOptimo(false);
        ui->groupBoxGra->setEnabled(true);
        Graficar(ui->doubleSpinBoxRes->value());
    }
}

void Plot::actualizar()
{
    iter++;
    particulas->actualizaParticulas();
    plot->setPlotStyle(*particulas);
    plot->updateData();
    plot->updateGL();
    ui->labelIteraciones->setText("Iteraciones: "+QString::number(iter));
    ui->labelOptimo->setText("Óptimo: "+QString::number(particulas->getMejor()));
    if(limIter)
    {
        if(iter==maxIter)
        {
            promedio+=particulas->getMejor();
            resultados+=QString::number(particulas->getMejor())+"\n";
            ui->spinBoxExec->setValue(ui->spinBoxExec->value()-1);
            if(ui->spinBoxExec->value()==0)
            {
                resultados+="*"+QString::number(promedio/numIni);
                QFile archivo;
                archivo.setFileName("Resultados/"+func+".csv");
                archivo.open(QIODevice::Append | QIODevice::Text);
                archivo.write(resultados.toUtf8());
                archivo.close();

                actualiza->stop();
                iter=0;
                ui->pushButtonEjecutar->setText("Ejecutar");
                particulas->dibujarSoloOptimo(true);
                plot->addEnrichment(*particulas);
                particulas->dibujarSoloOptimo(false);
                ui->groupBoxGra->setEnabled(true);
                Graficar(ui->doubleSpinBoxRes->value());
            }
        Graficar(5);
        particulas->configurar(min,noPart,-5,5,-5,5,cog,decCog,soc,decSoc,ine,decIne,constric,velPart);
        iter=0;
        }
    }
}

void Plot::on_radioButtonPuntos_clicked()
{
    Graficar(ui->doubleSpinBoxRes->value());
}

void Plot::on_radioButtonMallaColor_clicked()
{
    Graficar(ui->doubleSpinBoxRes->value());
}

void Plot::on_radioButtonMallaSColor_clicked()
{
    Graficar(ui->doubleSpinBoxRes->value());
}

void Plot::on_horizontalSliderRes_valueChanged(int value)
{
    ui->doubleSpinBoxRes->setValue(value);
}

void Plot::on_doubleSpinBoxRes_valueChanged(double arg1)
{
    ui->horizontalSliderRes->setValue(arg1);
    Graficar(ui->doubleSpinBoxRes->value());
}
