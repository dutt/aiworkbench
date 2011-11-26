#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class VisualiserDialog;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addBtn_clicked();

private:
    void connectWiring();

    Ui::MainWindow *ui;
    VisualiserDialog* mVisualiser;
};

#endif // MAINWINDOW_H
