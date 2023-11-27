#include "matrix.h"
#include "ui_mainwindow.h"
#include <vector>

// constructor
Matrix::Matrix(int rows, int columns) : totRows(rows), totColumns(columns)
{
    // Allocate memory for the 2D array
    Index = new double*[totRows];
    for (int i = 0; i < totRows; ++i)
    {
        Index[i] = new double[totColumns];
    }
}

// destructor
Matrix::~Matrix()
{
    // Deallocate memory for the 2D array
    for (int i = 0; i < totRows; ++i)
    {
        delete[] Index[i];
    }
    delete[] Index;
}

// get methods
int Matrix::get_totRows(){
    return totRows;
}
int Matrix::get_totColumns(){
    return totColumns;
}
bool Matrix::get_isValid(){
    return isValid;
}

// set methods
void Matrix::set_isValid(bool validity){
    isValid = validity;
}
void Matrix::set_Indices_from_lineEdits(QList<QLineEdit*> matrixLineEdits){
    // populate index depending on the number of rows and looking at the textline edits
    if(totRows >= 1){
        for (int i = 0; i<totColumns; i++){
            Index[0][i] =  matrixLineEdits[i]->text().toInt();
        }
    }
    if(totRows >= 2){
        for (int i = 4; i<totColumns+4; i++){
            Index[1][i-4] =  matrixLineEdits[i]->text().toInt();
        }
    }
    if(totRows >= 3){
        for (int i = 8; i<totColumns+8; i++){
            Index[2][i-8] =  matrixLineEdits[i]->text().toInt();
        }
    }
    if(totRows == 4){
        for (int i = 12; i<totColumns+12; i++){
            Index[3][i-12] =  matrixLineEdits[i]->text().toInt();
        }
    }
}

// display matrix method
void Matrix::display_matrix(Ui::MainWindow* ui){

    // unhide the solution widgets
    ui->tWsolution->show();
    ui->lblequals->show();

    // set size of table widget
    ui->tWsolution->setColumnCount(totColumns);
    ui->tWsolution->setRowCount(totRows);

    // loop through rows
    for (int i = 0; i < totRows; i++){
        // loop through columns
        for (int j = 0; j < totColumns; j++){
            // create tablewidget item to place in cell (i,j)
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setText(QString::number(Index[i][j]));
            ui->tWsolution->setItem(i,j,item);
        }
    }

    // resize tWsolution
    ui->tWsolution->resizeColumnsToContents();
}

// calculate addition **NB!!! you need to use this function for matrix 1 and pass in matrix 2 as a parameter
Matrix Matrix::calculate_Addition(Ui::MainWindow* ui, Matrix* matrix2){

    // create object
    Matrix solMatrix(totRows,totColumns);
    solMatrix.set_isValid(true);

    // first check if its possible to do addition
    if (totRows != matrix2->get_totRows() || totColumns != matrix2->get_totColumns()){
        // set tablewidget rows and columns to 1 to show error message
        ui->tWsolution->setColumnCount(1);
        ui->tWsolution->setRowCount(1);

        // create new table widget item and add the error message text then insert it into the correct index
        QTableWidgetItem* item = new QTableWidgetItem;
        item->setText("Incorrect dimensions to perform operation! (nxm + nxm)");
        ui->tWsolution->setItem(0,0,item);

        // resize tWsolution
        ui->tWsolution->resizeColumnsToContents();
        // make invalid
        solMatrix.set_isValid(false);
    }

    // do addition below if it is possible

    if (solMatrix.get_isValid()){
        // loop through rows
        for (int i = 0; i < totRows; i++){
            // loop through columns
            for (int j = 0; j < totColumns; j++){
                solMatrix.Index[i][j] = Index[i][j] + matrix2->Index[i][j];
            }
        }
    }

    // return solution matrix
    return solMatrix;
}

// calculate subtraction **NB!!! you need to use this function for matrix 1 as pass in matrix 2 as a parameter
Matrix Matrix::calculate_Subtraction(Ui::MainWindow* ui, Matrix* matrix2){

    // create object
    Matrix solMatrix(totRows,totColumns);

    // first check if its possible to do subtraction
    if (totRows != matrix2->get_totRows() || totColumns != matrix2->get_totColumns()){
        // set tablewidget rows and columns to 1 to show error message
        ui->tWsolution->setColumnCount(1);
        ui->tWsolution->setRowCount(1);

        // create new table widget item and add the error message text then insert it into the correct index
        QTableWidgetItem* item = new QTableWidgetItem;
        item->setText("Incorrect dimensions to perform operation! (nxm - nxm)");
        ui->tWsolution->setItem(0,0,item);

        // resize tWsolution
        ui->tWsolution->resizeColumnsToContents();
        // make invalid
        solMatrix.set_isValid(false);
    }

    // do subtraction below if it is possible

    if (solMatrix.get_isValid()){
        // loop through rows
        for (int i = 0; i < totRows; i++){
            // loop through columns
            for (int j = 0; j < totColumns; j++){
                solMatrix.Index[i][j] = Index[i][j] - matrix2->Index[i][j];
            }
        }
    }

    // return solution matrix
    return solMatrix;
}

// calculate multiplication **NB!!! you need to use this function for matrix 1 as pass in matrix 2 as a parameter
Matrix Matrix::calculate_Multiplication(Ui::MainWindow* ui, Matrix* matrix2) {

    // Create the result matrix
    Matrix solMatrix(totRows, matrix2->totColumns);
    solMatrix.set_isValid(true);

    // Check if it's possible to do multiplication
    if (totColumns != matrix2->totRows) {
        // Handle dimension mismatch error
        ui->tWsolution->setColumnCount(1);
        ui->tWsolution->setRowCount(1);

        QTableWidgetItem* item = new QTableWidgetItem;
        item->setText("Incorrect dimensions to perform operation! (nxm x mxk)");
        ui->tWsolution->setItem(0, 0, item);
        ui->tWsolution->resizeColumnsToContents();
        // unhide the solution widgets
        ui->tWsolution->show();
        ui->lblequals->show();

        solMatrix.set_isValid(false);
        // Return an invalid matrix
        return solMatrix;
    }

    // Perform multiplication
    std::vector<long long int> solution(solMatrix.totRows * solMatrix.totColumns, 0);

    for (int row = 0; row < totRows; row++) {
        for (int col = 0; col < matrix2->totColumns; col++) {
            long long int temp = 0;
            for (int k = 0; k < totColumns; k++) {
                temp += Index[row][k] * matrix2->Index[k][col];
            }
            solution[row * solMatrix.totColumns + col] = temp;
        }
    }

    // Fill the solution matrix
    int count = 0;
    for (int row = 0; row < solMatrix.totRows; row++) {
        for (int col = 0; col < solMatrix.totColumns; col++) {
            solMatrix.Index[row][col] = solution[count];
            count++;
        }
    }

    return solMatrix;
}

// calculate scaler multiplication
Matrix Matrix::calculate_Scaler_Multiplication(Ui::MainWindow* ui){

    // create object
    Matrix solMatrix(totRows,totColumns);

    // loop through matrix and multiple scaler by each index, out result to table widget
    for (int row = 0; row < totRows; row++){
        for (int column = 0; column < totColumns; column++){
            solMatrix.Index[row][column] = Index[row][column] * ui->lEscaler->text().toInt();
        }
    }

    return solMatrix;
}

// calculate scaler division
Matrix Matrix::calculate_Scaler_Division(Ui::MainWindow* ui){

    // create object
    Matrix solMatrix(totRows,totColumns);

    // loop through matrix and multiple scaler by each index, out result to table widget
    for (int row = 0; row < totRows; row++){
        for (int column = 0; column < totColumns; column++){
            solMatrix.Index[row][column] = Index[row][column] / ui->lEscaler->text().toInt();
        }
    }

    return solMatrix;
}

// calculate determinant (recursively)
// will return -1 by default if you cannot find the determinant (useful for when you want to find the inverse i.e. determinant cannot = 0
double Matrix::calculate_Determinant(){

    // check if you can find the determinant
    if (totRows != totColumns) {
        this->set_isValid(false);
        return -1;
    } else{
        this->set_isValid(true);
    }

    // find the determinant in the case that you can
    if (this->get_isValid()){
        // Base case: If the matrix is 1x1, return the single element as the determinant
        if (totRows == 1) {
            return Index[0][0];
        }

        long long int determinant = 0;

        // Iterate over the first row to calculate the determinant
        for (int i = 0; i < totColumns; ++i) {
            // Calculate the minor matrix (matrix obtained by removing the first row and i-th column)
            Matrix minorMatrix(totRows - 1, totColumns - 1);

            for (int row = 1; row < totRows; ++row) {
                for (int col = 0, colIdx = 0; col < totColumns; ++col) {
                    if (col != i) {
                        minorMatrix.Index[row - 1][colIdx++] = Index[row][col];
                    }
                }
            }

            // Calculate the determinant recursively for the minor matrix
            long long int minorDeterminant = minorMatrix.calculate_Determinant();

            // Add the contribution of this element to the determinant
            determinant += std::pow(-1, i) * Index[0][i] * minorDeterminant;
        }

        return determinant;
    }
    return -1;
}

// calculate inverse
Matrix Matrix::calculate_Inverse() {
    // Check if the matrix is square
    if (totRows != totColumns) {
        this->set_isValid(false);
        return Matrix(0, 0);
    } else {
        this->set_isValid(true);
    }

    // Calculate the determinant
    long double determinant = this->calculate_Determinant();

    // Check if the determinant is zero (no inverse exists)
    if (determinant == 0) {
        this->set_isValid(false);
        return Matrix(0, 0);
    } else {
        this->set_isValid(true);
    }

    // Calculate the Inverse matrix
    Matrix inverseMatrix(totRows, totColumns);

    for (int i = 0; i < totRows; ++i) {
        for (int j = 0; j < totColumns; ++j) {
            // Calculate the determinant of the submatrix excluding the current row and column
            long double minorDeterminant = calculate_SubmatrixDeterminant(i, j);

            // Apply the checkerboard of minuses to get the cofactor
            long double cofactor = ((i + j) % 2 == 0 ? 1 : -1) * minorDeterminant;

            // Transpose the cofactor to get the adjugate
            inverseMatrix.Index[j][i] = cofactor;
        }
    }

    // Multiply each element by 1/determinant to get the inverse
    for (int i = 0; i < totRows; ++i) {
        for (int j = 0; j < totColumns; ++j) {
            inverseMatrix.Index[i][j] /= determinant;
        }
    }

    return inverseMatrix;
}

// calculate transpose
Matrix Matrix::calculate_Transpose(){
    // create object with swapped rows and columns
    Matrix solMatrix(totColumns,totRows);

    // loop through matrix and fill in the swapped entries for solMatrix
    for (int i = 0; i<totRows; i++){
        for (int j = 0; j<totColumns; j++){
            solMatrix.Index[j][i] = Index[i][j];
        }
    }

    return solMatrix;
}

// calculate co-factors
Matrix Matrix::calculate_cofactors() {
    Matrix cofactorMatrix(totRows, totColumns);

    for (int i = 0; i < totRows; ++i) {
        for (int j = 0; j < totColumns; ++j) {
            // Calculate the minor matrix (matrix obtained by removing the i-th row and j-th column)
            Matrix minorMatrix(totRows - 1, totColumns - 1);

            for (int row = 0, minorRow = 0; row < totRows; ++row) {
                if (row == i) {
                    // Skip the i-th row
                    continue;
                }

                for (int col = 0, minorCol = 0; col < totColumns; ++col) {
                    if (col == j) {
                        // Skip the j-th column
                        continue;
                    }

                    minorMatrix.Index[minorRow][minorCol] = Index[row][col];
                    ++minorCol;
                }

                ++minorRow;
            }

            // Calculate the determinant of the minor matrix
            long long int minorDeterminant = minorMatrix.calculate_Determinant();

            // Calculate the cofactor and assign it to the cofactorMatrix
            cofactorMatrix.Index[i][j] = std::pow(-1, i + j) * minorDeterminant;
        }
    }

    return cofactorMatrix;
}

// Calculate the determinant of a submatrix (helper function)
double Matrix::calculate_SubmatrixDeterminant(int excludeRow, int excludeCol) const {
    Matrix submatrix(totRows - 1, totColumns - 1);

    for (int i = 0, subRow = 0; i < totRows; ++i) {
        if (i == excludeRow) {
            continue;
        }

        for (int j = 0, subCol = 0; j < totColumns; ++j) {
            if (j == excludeCol) {
                continue;
            }

            submatrix.Index[subRow][subCol] = Index[i][j];
            ++subCol;
        }

        ++subRow;
    }

    return submatrix.calculate_Determinant();
}
