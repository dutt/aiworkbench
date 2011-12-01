#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include "visualiserdialog.h"
#include "scriptengine.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("AI Toolbox");
    setAttribute(Qt::WA_QuitOnClose);

    mVisualiser = new VisualiserDialog(this);
    mVisualiser->setModal(false);
    mVisualiser->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectWiring() {
    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(on_addBtn_clicked()));
}

void MainWindow::on_addBtn_clicked() {
    mVisualiser->add_square();
}
