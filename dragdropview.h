#ifndef DRAGDROPVIEW_H
#define DRAGDROPVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>

class OriginalItem;

class DragDropView : public QGraphicsView
{
public:
    explicit DragDropView(QWidget *parent = Q_NULLPTR);
    void setOriginlItemsVisible(bool visible);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QGraphicsScene *scene_;
    QVector<OriginalItem*> item_list_;
};

#endif // DRAGDROPVIEW_H
