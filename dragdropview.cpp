#include "dragdropview.h"

#include <QApplication>
#include <QStyle>

#include "originalitem.h"
#include "showcontent.h"


DragDropView::DragDropView(QWidget *parent)
{
    Q_UNUSED(parent);

    // view 配置
    setRenderHint(QPainter::Antialiasing);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setBackgroundBrush(QColor(255, 255, 255));


    // 初始化scene
    scene_ = new QGraphicsScene(this);
    scene_->setSceneRect(-200, -200, 400, 400);

    // 添加原始项目
    for (int i = 0; i < 10; ++i) {
        OriginalItem *item = new OriginalItem;
        item->setPos(-150, -180 + 40 * i);
        QStyle::StandardPixmap type = (QStyle::StandardPixmap)(QStyle::SP_DirHomeIcon + i);
        auto pixmap = QApplication::style()->standardIcon(type).pixmap(32, 32);
        item->setPixmip(pixmap);
        item->setType("Type " + QString::number(i));

        item_list_.append(item);
        scene_->addItem(item);
    }

    // 添加待添加项目
    ShowContent *robot = new ShowContent;
    robot->setTransform(QTransform::fromScale(1.2, 1.2), true);
    robot->setPos(0, -20);

    // 加入scene
    scene_->addItem(robot);


    // 为view指定scene
    setScene(scene_);
}

void DragDropView::setOriginlItemsVisible(bool visible)
{
    foreach(auto item, item_list_) {
        item->setVisible(visible);
    }
}

void DragDropView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}
