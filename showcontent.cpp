/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "showcontent.h"

#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QPainter>
#include <QDebug>

const int g_w = 40;


ShowPart::ShowPart(QGraphicsItem *parent)
    : QGraphicsObject(parent), color_(Qt::lightGray)
{
    setAcceptDrops(true);
}

QString ShowPart::getType() const
{
    return type_;
}

void ShowPart::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasColor()) {
        event->setAccepted(true);
        dragOver = true;
        update();
    } else {
        event->setAccepted(false);
    }
}

void ShowPart::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    dragOver = false;
    update();
}

void ShowPart::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    dragOver = false;
    if (event->mimeData()->hasColor())
        color_ = qvariant_cast<QColor>(event->mimeData()->colorData());
    update();
}


void ShowPart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (!type_.isEmpty()) {
            isClicked = true;
            qDebug() << "Clicked : " << type_;
        }
    } else if (event->button() == Qt::RightButton) {
        color_ = Qt::lightGray;
        type_.clear();
        pixmap_ = QPixmap();
        update();
    }
    QGraphicsObject::mousePressEvent(event);
}

void ShowPart::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (!type_.isEmpty()) {
            isClicked = false;
            color_ = Qt::lightGray;
            type_.clear();
            pixmap_ = QPixmap();
            update();
        }
    }
    QGraphicsObject::mouseReleaseEvent(event);
}


ShowButton::ShowButton(QGraphicsItem *parent)
    : ShowPart(parent)
{
}

QRectF ShowButton::boundingRect() const
{
    return QRectF(-g_w, -g_w, g_w, g_w);
}

void ShowButton::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (pixmap_.isNull()) {
        painter->setBrush(dragOver ? color_.lighter(130) : color_);
        painter->drawRoundedRect(-g_w, -g_w, g_w, g_w, 10, 10, Qt::RelativeSize);
    } else {
        painter->setBrush(dragOver ? color_.lighter(130) : color_);
        painter->drawRoundedRect(-g_w, -g_w, g_w, g_w, 10, 10, Qt::RelativeSize);
        painter->drawPixmap(-g_w, -g_w, g_w, g_w, pixmap_);
    }
}

void ShowButton::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasImage()) {
        event->setAccepted(true);
        dragOver = true;
        update();
    } else {
        ShowPart::dragEnterEvent(event);
    }
}

void ShowButton::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasImage()) {
        dragOver = false;
        pixmap_ = qvariant_cast<QPixmap>(event->mimeData()->imageData());
        update();
    }
    if (event->mimeData()->hasFormat("text/plain")) {
        QString text = QString::fromUtf8(event->mimeData()->data("text/plain"));
        type_ = text;
    }

    ShowPart::dropEvent(event);
}

ShowContent::ShowContent(QGraphicsItem *parent)
    : ShowPart(parent)
{
    setFlag(ItemHasNoContents);

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            QGraphicsObject *showBtn = new ShowButton(this);
            showBtn->setPos(-20 + j * (g_w + 10), -60 + i * (g_w + 10));
        }
    }
}


QRectF ShowContent::boundingRect() const
{
    return QRectF();
}

void ShowContent::paint(QPainter *painter,
                  const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

