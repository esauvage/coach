#include "mytreeview.h"

#include <QKeyEvent>

MyTreeView::MyTreeView(QWidget *parent)
    :QTreeView(parent)
{

}

void MyTreeView::keyReleaseEvent(QKeyEvent *event)
{
    QTreeView::keyReleaseEvent(event);
    emit keyReleased(static_cast<QKeyEvent *>(event));
}
