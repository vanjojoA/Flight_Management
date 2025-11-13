#include "maininterface.h"
#include "ui_maininterface.h"

MainInterface::MainInterface(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainInterface)
{
    ui->setupUi(this);
}

MainInterface::~MainInterface()
{
    delete ui;
}
