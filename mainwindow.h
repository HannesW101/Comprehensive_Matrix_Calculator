#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_NumRowsM1_valueChanged(int value);

    void on_NumColumnsM1_valueChanged(int value);

    void on_NumRowsM2_valueChanged(int value);

    void on_NumColumnsM2_valueChanged(int value);

    void on_pBcalculate_clicked();

    void on_cBoperations_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
