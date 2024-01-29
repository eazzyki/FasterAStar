#include "grid.h"
#include <iostream>
#include <QDebug>

Grid::Grid()
{
    start = QPointF(-1, -1);
    goal = QPointF(-1, -1);
}


Grid::Grid(qreal x, qreal y, qreal w, qreal h) {
    setSceneRect(x, y, w, h);
    start = QPointF(-1, -1);
    goal = QPointF(-1, -1);
}


void Grid::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (this->isRadioBtnClicked) {
        QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
        if (item != nullptr) {
            QGraphicsRectItem* rec = (QGraphicsRectItem*) item;
            if (this->comboBoxIdx == 0) {
                if (this->start.x() != -1) {
                    coloringCell(this->start, QBrush(Qt::white));
                }
                coloringCell(rec, QBrush(Qt::red));
                this->start = rec->scenePos();
            } else if (this->comboBoxIdx == 1) {
                if (this->goal.x() != -1) {
                    coloringCell(this->goal, QBrush(Qt::white));
                }
                coloringCell(rec, QBrush(Qt::green));
                this->goal = rec->scenePos();
            } else if (this->comboBoxIdx == 2) {
                if (event->buttons() & Qt::LeftButton) {
                    coloringCell(rec, QBrush(Qt::black));
                    this->obstacles.push_back(rec->scenePos());
                } else if (event->buttons() & Qt::RightButton) {
                    coloringCell(rec, QBrush(Qt::white));
                    this->obstacles.erase(std::remove(this->obstacles.begin(), this->obstacles.end(), rec->scenePos()), this->obstacles.end());
                }
            } else {
                qDebug() << "Wrong ComboBox text!";
            }
        }
    }
}


void Grid::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (this->isRadioBtnClicked) {
        if (this->comboBoxIdx == 2) {
            QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
            if (item != nullptr) {
                QGraphicsRectItem* rec = (QGraphicsRectItem*) item;
                if (event->buttons() & Qt::LeftButton) {
                    if (rec->brush().color() == Qt::white) {
                        coloringCell(rec, QBrush(Qt::black));
                        this->obstacles.push_back(rec->scenePos());
                    }
                } else if (event->buttons() & Qt::RightButton) {
                    if (rec->brush().color() == Qt::black) {
                        coloringCell(rec, QBrush(Qt::white));
                        this->obstacles.erase(std::remove(this->obstacles.begin(), this->obstacles.end(), rec->scenePos()), this->obstacles.end());
                    }
                }
            }
        }
    }
}


void Grid::coloringCell(QPointF p, QBrush brush) {
    QGraphicsItem* temp = this->itemAt(p, QTransform());
    QGraphicsRectItem* point = (QGraphicsRectItem*) temp;
    point->setBrush(brush);
}


void Grid::coloringCell(QGraphicsRectItem* item, QBrush brush) {
    item->setBrush(brush);
}


void Grid::setComboBox(int id) {
    this->comboBoxIdx = id;
}


void Grid::setRadioBtn(bool b) {
    this->isRadioBtnClicked = b;
}


QPointF Grid::getStart() {
    return this->start;
}


QPointF Grid::getGoal() {
    return this->goal;
}


QList<QPointF> Grid::getObstacles() {
    return this->obstacles;
}


void Grid::draw(QList<QPointF>& points, QBrush brush) {
    for (QPointF point : points) {
        QGraphicsItem *item = itemAt(point, QTransform());
        if (item != nullptr) {
            QGraphicsRectItem* rec = (QGraphicsRectItem*) item;
            coloringCell(rec, brush);
        } else {
            std::cout << "Grid cannot draw the Cells!!!" << std::endl;
        }
    }
}

void Grid::drawPath(QList<QPointF> &points, QBrush brush) {
    draw(points, QBrush(Qt::blue));
    this->shortestPath = points;
}

void Grid::drawVisitedCells(QList<QPointF> &points, QBrush brush) {
    draw(points, QBrush(Qt::yellow));
    this->visitedCells = points;
}

void Grid::resetPath() {
    for (QPointF point : this->shortestPath) {
        QGraphicsItem *item = itemAt(point, QTransform());
        if (item != nullptr) {
            QGraphicsRectItem* rec = (QGraphicsRectItem*) item;
            coloringCell(rec, QBrush(Qt::white));
        }
    }
    this->shortestPath.clear();
}



void Grid::resetObstacles() {
    for (QPointF point : this->obstacles) {
        QGraphicsItem *item = itemAt(point, QTransform());
        if (item != nullptr) {
            QGraphicsRectItem* rec = (QGraphicsRectItem*) item;
            coloringCell(rec, QBrush(Qt::white));
        }
    }
    this->obstacles.clear();
}


void Grid::resetAnalyzedCells() {
    for (QPointF point : this->visitedCells) {
        QGraphicsItem *item = itemAt(point, QTransform());
        if (item != nullptr) {
            QGraphicsRectItem* rec = (QGraphicsRectItem*) item;
            coloringCell(rec, QBrush(Qt::white));
        }
    }
    this->visitedCells.clear();
}

void Grid::reset(QList<QPointF>& cont) {
    for (QPointF point : cont) {
        QGraphicsItem *item = itemAt(point, QTransform());
        if (item != nullptr) {
            QGraphicsRectItem* rec = (QGraphicsRectItem*) item;
            coloringCell(rec, QBrush(Qt::white));
        }
    }
    cont.clear();
}

void Grid::setupGrid(int cellLength) {
    this->clear();

    qint32 y_pos = 0;
    while (y_pos < this->height()) {
        qint32 x_pos = 0;
        while(x_pos < this->width()) {
            QGraphicsRectItem* rec = new QGraphicsRectItem(0, 0, cellLength, cellLength);
            rec->setPos(x_pos, y_pos);
            rec->setBrush(QBrush(Qt::white));
            this->addItem(rec);
            x_pos += cellLength;
        }
        y_pos += cellLength;
    }
}
