#ifndef GLDIALOG_H
#define GLDIALOG_H

#include <QDialog>

#include "glhelper.h"

class GlWidget;

namespace Ui {
    class GlDialog;
}

class VisualiserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VisualiserDialog(QWidget *parent = 0);
    ~VisualiserDialog();

    void add_square();
private:
    GlWidget* mWidget;
    Ui::GlDialog *ui;
    GlHelper mHelper;
};

#endif // GLDIALOG_H
