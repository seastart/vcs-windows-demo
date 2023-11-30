#include "viewitem.h"
#include "ui_viewitem.h"

ViewItem::ViewItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewItem)
  , key(0)
{
    ui->setupUi(this);
    view = new QWidget(this);
    ui->horizontalLayout->addWidget(view);
}

ViewItem::~ViewItem()
{
    delete ui;
}
QWidget* ViewItem::GetView()
{
    return view;
}

void ViewItem::SetName(QString name){
    ui->label->setText(name);
}
