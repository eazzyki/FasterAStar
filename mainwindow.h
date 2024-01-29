#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>

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

    qint32 HEIGHT_W= 1550;
    qint32 WIDTH_W = 2000;
    qint32 OFFSET_MOUSEPOS_W = 160;
    qint32 OFFSET_MOUSEPOS_H = 120;

private slots:
    void on_radioButtonEnv_clicked();
    void on_comboBoxEnv_currentIndexChanged(int s);
    void on_pushBtnStart_clicked();
    void on_pushBtnResetPath_clicked();
    void on_pushBtnResetEnv_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_comboBoxAlg_currentIndexChanged(int s);
    void updateInfoBox(QString text);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QList<QGraphicsRectItem*> tiles;
    Grid* grid = new Grid();
    int cellLength = 25;
    AlgName comboBoxAlgValue;

};
#endif // MAINWINDOW_H
