#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "factory.h"

#include <QDebug>
#include <QScreen>
#include <iostream>
#include <chrono>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto const rec = QGuiApplication::screens().first()->size();
    auto const height = rec.height() * 0.8;
    auto const width = rec.width() * 0.8;

    setMinimumSize(width, height);
    ui->radioButtonEnv->setChecked(false);
    ui->comboBoxEnv->setDisabled(true);
    ui->comboBoxEnv->addItems({"Start", "Goal", "Obstacle"});

    ui->horizontalSlider->setSingleStep(5);
    ui->horizontalSlider->setTickInterval(5);

    QGraphicsView *view = ui->graphicsView;
    view->setMinimumSize(width-400, height);
    grid = new Grid(0, 0, view->width(), view->height());

    view->setScene(grid);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    grid->setupGrid(this->cellLength);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_radioButtonEnv_clicked()
{
    if(ui->radioButtonEnv->isChecked()) {
        ui->comboBoxEnv->setEnabled(true);
        grid->setRadioBtn(true);
    } else {
        ui->comboBoxEnv->setEnabled(false);
        grid->setRadioBtn(false);
    }
}


void MainWindow::on_comboBoxEnv_currentIndexChanged(int s) {
    grid->setComboBox(s);
}


void MainWindow::on_pushBtnStart_clicked() {
    grid->resetPath();
    std::unique_ptr<PathAlgorithm> alg = Factory::makeInstance(AlgName::ASTAR);

    alg->initialize(ui->graphicsView->width(),
                    ui->graphicsView->height(),
                    this->cellLength,
                    grid->getObstacles());
    alg->setStart(grid->getStart());
    alg->setGoal(grid->getGoal());

    auto t1 = std::chrono::high_resolution_clock::now();
    Path path = alg->computePath();
    auto t2 = std::chrono::high_resolution_clock::now();
    alg->stats.setCalcTime(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1));

    updateInfoBox(QString::fromStdString(alg->stats.getStats()));

    QList<QPointF> l;
    for (Cell p : path.path) {
        QPointF temp;
        p = alg->cellLocal2cellGlobal(p);
        temp.setX(p.x);
        temp.setY(p.y);
        l.push_back(temp);
    }
    grid->drawPath(l);
}


void MainWindow::on_pushBtnResetPath_clicked() {
    grid->resetPath();
}


void MainWindow::on_pushBtnResetEnv_clicked() {
    grid->resetObstacles();
}


void MainWindow::on_horizontalSlider_valueChanged(int value) {
    int roundedValue = (value / 10) * 10;
    if (roundedValue != this->cellLength) {
        grid->setupGrid(roundedValue);
        this->cellLength = roundedValue;
    }
}


void MainWindow::updateInfoBox(QString text) {
    ui->infoBox->setText(text);
}


