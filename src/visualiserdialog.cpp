#include "visualiserdialog.h"
#include "ui_gldialog.h"

#include <QtGui>
#include "widget.h"

VisualiserDialog::VisualiserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GlDialog)
{
    ui->setupUi(this);

    mWidget = new GlWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(mWidget);
    setLayout(layout);

    setAttribute(Qt::WA_QuitOnClose);
    setWindowTitle("Visualiser");
}

VisualiserDialog::~VisualiserDialog()
{
    delete ui;
}

void VisualiserDialog::add_square() {

}
