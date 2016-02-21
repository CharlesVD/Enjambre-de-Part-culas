#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSliderSocDec_valueChanged(int value)
{
    ui->doubleSpinBoxSocDec->setValue(value*0.01);
}

void MainWindow::on_doubleSpinBoxSocDec_valueChanged(double arg1)
{
    ui->horizontalSliderSocDec->setValue(arg1*100);
    if(arg1==0)
    {
        ui->labelSocAjuste->setText("Constante");
    }
    if(arg1<0)
    {
        ui->labelSocAjuste->setText("Decremento");
    }
    if(arg1>0)
    {
        ui->labelSocAjuste->setText("Incremento");
    }
}

void MainWindow::on_horizontalSliderSocVal_valueChanged(int value)
{
    ui->doubleSpinBoxSocVal->setValue(value*0.01);
}

void MainWindow::on_horizontalSliderVel_valueChanged(int value)
{
    ui->spinBoxVel->setValue(value);
}

void MainWindow::on_spinBoxVel_valueChanged(int arg1)
{
    ui->horizontalSliderVel->setValue(arg1);
}

void MainWindow::on_horizontalSliderIneVal_valueChanged(int value)
{
    ui->doubleSpinBoxIneVal->setValue(value*0.01);
}

void MainWindow::on_doubleSpinBoxIneVal_valueChanged(double arg1)
{
    ui->horizontalSliderIneVal->setValue(arg1*100);
}

void MainWindow::on_doubleSpinBoxSocVal_valueChanged(double arg1)
{
    ui->horizontalSliderSocVal->setValue(arg1*100);
}

void MainWindow::on_horizontalSliderIneDec_valueChanged(int value)
{
    ui->doubleSpinBoxIneDec->setValue(value*0.01);
}

void MainWindow::on_doubleSpinBoxIneDec_valueChanged(double arg1)
{
    ui->horizontalSliderIneDec->setValue(arg1*100);
    if(arg1==0)
    {
        ui->labelIneAjuste->setText("Constante");
    }
    if(arg1<0)
    {
        ui->labelIneAjuste->setText("Decremento");
    }
    if(arg1>=0)
    {
        ui->labelIneAjuste->setText("Incremento");
    }
}

void MainWindow::on_horizontalSliderCogVal_valueChanged(int value)
{
    ui->doubleSpinBoxCogVal->setValue(value*0.01);
}

void MainWindow::on_doubleSpinBoxCogVal_valueChanged(double arg1)
{
    ui->horizontalSliderCogVal->setValue(arg1*100);
}

void MainWindow::on_horizontalSliderCogDec_valueChanged(int value)
{
    ui->doubleSpinBoxCogDec->setValue(value*0.01);
}

void MainWindow::on_doubleSpinBoxCogDec_valueChanged(double arg1)
{
    ui->horizontalSliderCogDec->setValue(arg1*100);
    if(arg1==0)
    {
        ui->labelCogAjuste->setText("Constante");
    }
    if(arg1<0)
    {
        ui->labelCogAjuste->setText("Decremento");
    }
    if(arg1>0)
    {
        ui->labelCogAjuste->setText("Incremento");
    }
}

void MainWindow::on_pushButtonEjecutar_clicked()
{
    plot = new Plot();
    plot->setAlgVel(ui->spinBoxVel->value());
    plot->setIteraciones(ui->checkBoxMaxIter->isChecked(),ui->spinBoxMaxIter->value());
    plot->setConstriccion(ui->radioButtonConstriccion->isChecked());
    plot->setDec((ui->doubleSpinBoxCogDec->value()*0.01)+1,
                 (ui->doubleSpinBoxSocDec->value()*0.01)+1,
                 (ui->doubleSpinBoxIneDec->value()*0.01)+1);
    plot->setFuncion(ui->comboBoxFunciones->currentText());
    plot->setMinimo(ui->radioButtonMin->isChecked());
    plot->setValores(ui->doubleSpinBoxCogVal->value(),ui->doubleSpinBoxSocVal->value(),ui->doubleSpinBoxIneVal->value());
    plot->setNoParticulas(ui->spinBoxNoParticulas->value());
    plot->setVelocidadPart(ui->spinBoxVelPart->value());
    plot->Graficar(200);
    plot->exec();
    plot->~Plot();
}

void MainWindow::on_radioButtonConstriccion_toggled(bool checked)
{
    ui->doubleSpinBoxIneDec->setDisabled(checked);
    ui->doubleSpinBoxIneVal->setDisabled(checked);
    ui->horizontalSliderIneDec->setDisabled(checked);
    ui->horizontalSliderIneVal->setDisabled(checked);
}

void MainWindow::on_horizontalSliderVelPart_valueChanged(int value)
{
    ui->spinBoxVelPart->setValue(value);
}

void MainWindow::on_spinBoxVelPart_valueChanged(int arg1)
{
    ui->horizontalSliderVelPart->setValue(arg1);
}
