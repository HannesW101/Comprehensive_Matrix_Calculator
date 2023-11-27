#ifndef MATRIX_H
#define MATRIX_H

#include <QLineEdit>
#include "mainwindow.h"

class Matrix
{
private:
    int totRows;
    int totColumns;
    bool isValid = true;
public:
    double** Index;  // Pointer to a dynamically allocated 2D array (public attribute to allow easy access to a specific index without long lines of code)

    Matrix(int rows, int columns);
    ~Matrix();

    // get attributes
    int get_totRows();
    int get_totColumns();
    bool get_isValid();

    // set attributes
    void set_isValid(bool validity);
    void set_Indices_from_lineEdits(QList<QLineEdit*> matrixLineEdits);

    // display
    void display_matrix(Ui::MainWindow* ui);

    // methods
    Matrix calculate_Addition(Ui::MainWindow* ui, Matrix* matrix2);
    Matrix calculate_Subtraction(Ui::MainWindow* ui, Matrix* matrix2);
    Matrix calculate_Multiplication(Ui::MainWindow* ui, Matrix* matrix2);
    Matrix calculate_Scaler_Multiplication(Ui::MainWindow* ui);
    Matrix calculate_Scaler_Division(Ui::MainWindow* ui);
    double calculate_Determinant();
    Matrix calculate_Inverse();
    Matrix calculate_Transpose();
    Matrix calculate_cofactors();
    double calculate_SubmatrixDeterminant(int excludeRow, int excludeCol) const;
};

#endif // MATRIX_H
