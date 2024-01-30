#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "grid.h"
#include "factory.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBoxEnv_currentIndexChanged(int s);
    void on_pushBtnStart_clicked();
    void on_pushBtnResetPath_clicked();
    void on_pushBtnResetEnv_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_comboBoxAlg_currentIndexChanged(int s);
    void updateInfoBox(QString text);
    bool areEndPointsSet();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QList<QGraphicsRectItem*> tiles;
    Grid* grid = new Grid();
    int cellLength = 25;
    AlgName comboBoxAlgValue;
};
#endif // MAINWINDOW_H
