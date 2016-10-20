#include "gui/mainwindow.h"
#include "ui_mainwindow.h"
#include <head.h>
#include <core/TorrentParser.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DictType dictType;

    QString content("d12:inuyasha1027li32167e22:this_is_a_test_of_dicteee");
    dictType.parser(content);

    dictType.showValue();
}

MainWindow::~MainWindow()
{
    delete ui;
}
