#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H

#include <QTreeView>

class MyTreeView : public QTreeView
{
    Q_OBJECT
public:
    MyTreeView(QWidget *parent = nullptr);
signals:
    void keyReleased(QKeyEvent * event);
protected:
     virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // MYTREEVIEW_H
