#ifndef GRID_H
#define GRID_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <string>

class Grid : public QGraphicsScene {
    Q_OBJECT
private:
    QPointF start;
    QPointF goal;
    QList<QPointF> obstacles;
    QList<QPointF> shortestPath;
    QList<QPointF> visitedCells;
    int comboBoxIdx = 0;

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void draw(QList<QPointF>& points, QBrush brush);

public:
    Grid();
    Grid(qreal x, qreal y, qreal w, qreal h);

    QPointF getStart();
    QPointF getGoal();
    QList<QPointF> getObstacles();
    void coloringCell(QPointF p, QBrush brush);
    void coloringCell(QGraphicsRectItem* item, QBrush brush);
    void drawPath(QList<QPointF>& points, QBrush brush);
    void drawVisitedCells(QList<QPointF>& points, QBrush brush);
    void setComboBox(int id);
    void resetPath();
    void resetObstacles();
    void resetAnalyzedCells();
    void reset(QList<QPointF>& cont);
    void setupGrid(int cellLength);
};

#endif // GRID_H
