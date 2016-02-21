#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_horizontalSliderSocDec_valueChanged(int value);

    void on_doubleSpinBoxSocDec_valueChanged(double arg1);

    void on_horizontalSliderSocVal_valueChanged(int value);

    void on_horizontalSliderVel_valueChanged(int value);

    void on_spinBoxVel_valueChanged(int arg1);


    void on_horizontalSliderIneVal_valueChanged(int value);

    void on_doubleSpinBoxIneVal_valueChanged(double arg1);

    void on_doubleSpinBoxSocVal_valueChanged(double arg1);

    void on_horizontalSliderIneDec_valueChanged(int value);

    void on_doubleSpinBoxIneDec_valueChanged(double arg1);

    void on_horizontalSliderCogVal_valueChanged(int value);

    void on_doubleSpinBoxCogVal_valueChanged(double arg1);

    void on_horizontalSliderCogDec_valueChanged(int value);

    void on_doubleSpinBoxCogDec_valueChanged(double arg1);

    void on_pushButtonEjecutar_clicked();

    void on_radioButtonConstriccion_toggled(bool checked);

    void on_horizontalSliderVelPart_valueChanged(int value);

    void on_spinBoxVelPart_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    Plot *plot;
};

#endif // MAINWINDOW_H
