#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QScreen>
#include <iostream>
#include <chrono>

#include <numeric>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // get size of screen and adjust size of gui
    auto const rec = QGuiApplication::screens().first()->size();
    auto const height = rec.height() * 0.8;
    auto const width = rec.width() * 0.8;
    setMinimumSize(width, height);

    ui->comboBoxEnv->addItems({"Start", "Goal", "Obstacle"});
    ui->horizontalSlider->setSingleStep(5);
    ui->horizontalSlider->setTickInterval(5);
    ui->comboBoxAlg->addItems({"A* (Fast)", "A* (Heap)", "Dijkstra"});

    QGraphicsView *view = ui->graphicsView;
    view->setMinimumSize(width-400, height);

    grid = new Grid(0, 0, view->width(), view->height());
    view->setScene(grid);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    grid->setupGrid(this->cellLength);
}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_comboBoxEnv_currentIndexChanged(int s) {
    grid->setComboBox(s);
}


void MainWindow::on_pushBtnStart_clicked() {
    grid->resetPath();
    grid->resetAnalyzedCells();

    if (areEndPointsSet()) {
        std::unique_ptr<PathAlgorithm> alg = Factory::makeInstance(this->comboBoxAlgValue);

        alg->initialize(ui->graphicsView->width(),
                        ui->graphicsView->height(),
                        this->cellLength,
                        grid->getObstacles());

        alg->setStart(grid->getStart());
        alg->setGoal(grid->getGoal());

//        std::vector<float> times;
//        for (int i = 0; i < 10; i++) {
            Path shortesPath;
            std::vector<Cell> visited;

            auto t1 = std::chrono::high_resolution_clock::now();
            alg->computePath(shortesPath, visited);
            auto t2 = std::chrono::high_resolution_clock::now();

            alg->stats.setCalcTime(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1));
            updateInfoBox(QString::fromStdString(alg->stats.getStats()));

//            times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count());

            if (ui->checkBoxDrawVisited->isChecked()) {
                QList<QPointF> l1;
                for (Cell p : visited) {
                    QPointF temp;
                    p = alg->cellLocal2cellGlobal(p);
                    temp.setX(p.x);
                    temp.setY(p.y);
                    l1.push_back(temp);
                }
                grid->drawVisitedCells(l1, QBrush(QColor(0, 180, 252, 50)));
            }

            QList<QPointF> l;
            for (Cell p : shortesPath.path) {
                QPointF temp;
                p = alg->cellLocal2cellGlobal(p);
                temp.setX(p.x);
                temp.setY(p.y);
                l.push_back(temp);
            }
            grid->drawPath(l, QBrush(Qt::blue));
//            }
//        auto const count = static_cast<float>(times.size());
//        std::cout << "Time (avg): ";
//        std::cout << std::accumulate(times.begin(), times.end(), 0) / count << std::endl;
    }
}


void MainWindow::on_pushBtnResetPath_clicked() {
    grid->resetPath();
    grid->resetAnalyzedCells();
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


void MainWindow::on_comboBoxAlg_currentIndexChanged(int s) {
    AlgName algname;
    switch (s) {
    case 0:
        algname = ASTARFAST;
        break;
    case 1:
        algname = ASTARHEAP;
        break;
    case 2: algname = DIJKSTRA;
        break;
    default:
        algname = ASTARFAST;
        break;
    }
    this->comboBoxAlgValue = algname;
}


void MainWindow::updateInfoBox(QString text) {
    ui->infoBox->setText(text);
}

bool MainWindow::areEndPointsSet() {
    QPointF start = this->grid->getStart();
    QPointF goal= this->grid->getGoal();
    std::string txt = "";
    bool areSet = true;

    if (start.x() == -1 || start.y() == -1) {
        txt += "!Please set Start cell!\n";
        areSet = false;
    }
    if (goal.x() == -1 || goal.y() == -1) {
        txt += "!Please set Goal cell!\n";
        areSet = false;
    }
    if (goal == start && start.x() != -1) {
        txt += "!Start and Goal are the same Cell!";
        areSet = false;
    }
    updateInfoBox(QString::fromStdString(txt));
    return areSet;
}

