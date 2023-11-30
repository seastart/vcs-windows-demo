#ifndef VIEWITEM_H
#define VIEWITEM_H

#include <QWidget>

namespace Ui {
class ViewItem;
}

class ViewItem : public QWidget
{
    Q_OBJECT

public:
    explicit ViewItem(QWidget *parent = nullptr);
    ~ViewItem();

    void SetData(int k){key = k;}
    int GetData(){return key;}
    void SetName(QString name);
    QWidget* GetView();
private:
    Ui::ViewItem *ui;
    int key;
    QWidget* view;
};

#endif // VIEWITEM_H
