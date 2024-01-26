#ifndef GRID_H
#define GRID_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <string>

class Grid : public QGraphicsScene {
    Q_OBJECT

    QPointF start;
    QPointF goal;
    QList<QPointF> obstacles;
    QList<QPointF> shortestPath;

    int comboBoxIdx = 0;
    bool isRadioBtnClicked = false;

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void coloringCell(QPointF p, QBrush brush);
    void coloringCell(QGraphicsRectItem* item, QBrush brush);


public:
    Grid();
    Grid(qreal x, qreal y, qreal w, qreal h);

    void setComboBox(int id);
    void setRadioBtn(bool b);
    QPointF getStart();
    QPointF getGoal();
    QList<QPointF> getObstacles();
    void drawPath(QList<QPointF> path);
    void resetPath();
    void resetObstacles();
    void setupGrid(int cellLength);
};

#endif // GRID_H
