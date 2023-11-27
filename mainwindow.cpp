#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include "matrix.h"

// get QList of labels for matrix 1
QList<QLineEdit*> get_matrix1_Labels_QList(Ui::MainWindow* ui){
        QList<QLineEdit*> M1LineEdits = {
        ui->M1_00, ui->M1_01, ui->M1_02, ui->M1_03,
        ui->M1_10, ui->M1_11, ui->M1_12, ui->M1_13,
        ui->M1_20, ui->M1_21, ui->M1_22, ui->M1_23,
        ui->M1_30, ui->M1_31, ui->M1_32, ui->M1_33,
    };
    return M1LineEdits;
}

// get QList of labels for matrix 2
QList<QLineEdit*> get_matrix2_Labels_QList(Ui::MainWindow* ui){
    QList<QLineEdit*> M1LineEdits = {
        ui->M2_00, ui->M2_01, ui->M2_02, ui->M2_03,
        ui->M2_10, ui->M2_11, ui->M2_12, ui->M2_13,
        ui->M2_20, ui->M2_21, ui->M2_22, ui->M2_23,
        ui->M2_30, ui->M2_31, ui->M2_32, ui->M2_33,
    };
    return M1LineEdits;
}

// setup the combo box of operation choices
void setup_cBoperations(Ui::MainWindow* ui){
    // this sets the style across the application to "Fusion" which is a cross platform modern style
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    // add items to cBoperations
    ui->cBoperations->addItem("Matrix Addition");
    ui->cBoperations->addItem("Matrix Subtraction");
    ui->cBoperations->addItem("Matrix Multiplication");
    ui->cBoperations->addItem("Scalar Multiplication");
    ui->cBoperations->addItem("Scalar Division");
    ui->cBoperations->addItem("Determinant");
    ui->cBoperations->addItem("Inverse");
    ui->cBoperations->addItem("Transpose");
    ui->cBoperations->addItem("Co-factors");
}

// setup matrices labels to only accept integers
void setup_Matrices_to_only_accept_integers(QList<QLineEdit*> MLineEdits){

    // set validator for each index to only accept numbers
    for (QLineEdit* lineEdit : MLineEdits) {
        if (lineEdit) {
            QIntValidator* validator = new QIntValidator(lineEdit);
            lineEdit->setValidator(validator);
        }
    }
}

// display labels for matrix depending on sliders
void display_matrix_labels(QList<QLineEdit*> MatrixLineEdits, int numRows, int numColumns){

    // hide labels initially
    for (QLineEdit* lineEdit : MatrixLineEdits) {
        lineEdit->hide();
    }

    // check how many rows the matrix has and then loop through the columns and show labels
    if(numRows >= 1){
        for (int i = 0; i<numColumns; i++){
                MatrixLineEdits[i]->show();
        }
    }
    if(numRows >= 2){
        for (int i = 4; i<numColumns+4; i++){
                MatrixLineEdits[i]->show();
        }
    }
    if(numRows >= 3){
        for (int i = 8; i<numColumns+8; i++){
                MatrixLineEdits[i]->show();
        }
    }
    if(numRows == 4){
        for (int i = 12; i<numColumns+12; i++){
                MatrixLineEdits[i]->show();
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // call function to setup cBoperations
    setup_cBoperations(ui);

    // call function to setup matrix indices to only accept numbers
    setup_Matrices_to_only_accept_integers(get_matrix1_Labels_QList(ui));
    setup_Matrices_to_only_accept_integers(get_matrix2_Labels_QList(ui));
    // scaler only accept numbers
    QIntValidator* validator = new QIntValidator;
    ui->lEscaler->setValidator(validator);

    // hide labels initially
    QList<QLineEdit*> matrix1_labels = get_matrix1_Labels_QList(ui);
    for (QLineEdit* lineEdit : matrix1_labels) {
        lineEdit->hide();
    }
    QList<QLineEdit*> matrix2_labels = get_matrix2_Labels_QList(ui);
    for (QLineEdit* lineEdit : matrix2_labels) {
        lineEdit->hide();
    }
    ui->tWsolution->hide();
    ui->lblequals->hide();
    ui->lblScaler->hide();
    ui->lEscaler->hide();

    // call function to show labels initially
    display_matrix_labels(get_matrix1_Labels_QList(ui),1,1);
    display_matrix_labels(get_matrix2_Labels_QList(ui),1,1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// change the number of rows as slider moves (M1)
void MainWindow::on_NumRowsM1_valueChanged(int value)
{
    ui->lblM1rowCount->setText("Rows: "+QString::number(value));

    display_matrix_labels(get_matrix1_Labels_QList(ui),ui->NumRowsM1->value(),ui->NumColumnsM1->value());
}

// change the number of columns as slider moves (M1)
void MainWindow::on_NumColumnsM1_valueChanged(int value)
{
    ui->lblM1ColumnCount->setText("Columns: "+QString::number(value));

    display_matrix_labels(get_matrix1_Labels_QList(ui),ui->NumRowsM1->value(),ui->NumColumnsM1->value());
}

// change the number of rows as slider moves (M2)
void MainWindow::on_NumRowsM2_valueChanged(int value)
{
    ui->lblM2rowCount->setText("Rows: "+QString::number(value));

    display_matrix_labels(get_matrix2_Labels_QList(ui),ui->NumRowsM2->value(),ui->NumColumnsM2->value());
}

// change the number of columns as slider moves (M2)
void MainWindow::on_NumColumnsM2_valueChanged(int value)
{
    ui->lblM2ColumnCount->setText("Columns: "+QString::number(value));

    display_matrix_labels(get_matrix2_Labels_QList(ui),ui->NumRowsM2->value(),ui->NumColumnsM2->value());
}

// button clicked calculate
void MainWindow::on_pBcalculate_clicked()
{
    // clear table widget
    ui->tWsolution->clear();
    ui->tWsolution->setRowCount(0);
    ui->tWsolution->setColumnCount(0);

    // create matrix objects
    Matrix* matrix1 = new Matrix(ui->NumRowsM1->value(),ui->NumColumnsM1->value());
    Matrix* matrix2 = new Matrix(ui->NumRowsM2->value(),ui->NumColumnsM2->value());
    // initialising the entries in the objects to the values in the line edits
    matrix1->set_Indices_from_lineEdits(get_matrix1_Labels_QList(ui));
    matrix2->set_Indices_from_lineEdits(get_matrix2_Labels_QList(ui));

    // check what the combobox chosen operation is and perform appropriate operation and display solution
    if (ui->cBoperations->currentText() == "Matrix Addition"){
        Matrix solMatrix = matrix1->calculate_Addition(ui,matrix2);
        if(solMatrix.get_isValid()){
            solMatrix.display_matrix(ui);
        }
    }
    if (ui->cBoperations->currentText() == "Matrix Subtraction"){
        Matrix solMatrix = matrix1->calculate_Subtraction(ui,matrix2);
        if(solMatrix.get_isValid()){
            solMatrix.display_matrix(ui);
        }
    }
    if (ui->cBoperations->currentText() == "Matrix Multiplication"){
        Matrix solMatrix = matrix1->calculate_Multiplication(ui,matrix2);
        if(solMatrix.get_isValid()){
            solMatrix.display_matrix(ui);
            qDebug() << "true";
        }
    }
    if (ui->cBoperations->currentText() == "Scalar Multiplication"){
        Matrix solMatrix = matrix1->calculate_Scaler_Multiplication(ui);
        if(solMatrix.get_isValid()){
            solMatrix.display_matrix(ui);
        }
    }
    if (ui->cBoperations->currentText() == "Scalar Division"){
        Matrix solMatrix = matrix1->calculate_Scaler_Division(ui);
        if(solMatrix.get_isValid()){
            solMatrix.display_matrix(ui);
        }
    }
    if (ui->cBoperations->currentText() == "Transpose"){
        Matrix solMatrix = matrix1->calculate_Transpose();
        if(solMatrix.get_isValid()){
            solMatrix.display_matrix(ui);
        }
    }
    if (ui->cBoperations->currentText() == "Determinant"){
        double det = matrix1->calculate_Determinant();
        if(matrix1->get_isValid()){
            // set tablewidget rows and columns to 1
            ui->tWsolution->setColumnCount(1);
            ui->tWsolution->setRowCount(1);

            // create new table widget item and show the determinant
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setText(QString::number(det));
            ui->tWsolution->setItem(0,0,item);

            ui->tWsolution->show();
            // resize tWsolution
            ui->tWsolution->resizeColumnsToContents();
        } else{
            // set tablewidget rows and columns to 1
            ui->tWsolution->setColumnCount(1);
            ui->tWsolution->setRowCount(1);

            // create new table widget item and add the error message text then insert it into the correct index
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setText("Cannot find determinant! (matrix is not square)");
            ui->tWsolution->setItem(0,0,item);

            ui->tWsolution->show();
            // resize tWsolution
            ui->tWsolution->resizeColumnsToContents();

            matrix1->set_isValid(true);
        }
    }
    if (ui->cBoperations->currentText() == "Co-factors"){
        Matrix solMatrix = matrix1->calculate_cofactors();
        if(solMatrix.get_isValid()){
            solMatrix.display_matrix(ui);
        }
    }
    if (ui->cBoperations->currentText() == "Inverse"){
        matrix1->set_isValid(true);
        Matrix solMatrix = matrix1->calculate_Inverse();
        if(matrix1->get_isValid()){
            solMatrix.display_matrix(ui);
        } else{
            // set tablewidget rows and columns to 1
            ui->tWsolution->setColumnCount(1);
            ui->tWsolution->setRowCount(1);

            // create new table widget item and add the error message text then insert it into the correct index
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setText("Cannot find inverse! (matrix is not square or determinant = 0)");
            ui->tWsolution->setItem(0,0,item);

            ui->tWsolution->show();
            // resize tWsolution
            ui->tWsolution->resizeColumnsToContents();

            matrix1->set_isValid(true);
        }
    }

    // delete the objects to free up memory
    delete matrix1;
    delete matrix2;
}

// event on cBoperations change, used to clear widgets and also set labels correctly depending on the operation being done
void MainWindow::on_cBoperations_currentIndexChanged(int index)
{
    // setup widgets to default
    QList<QLineEdit*> matrix1_labels = get_matrix1_Labels_QList(ui);
    for (QLineEdit* lineEdit : matrix1_labels) {
        lineEdit->setText("0");
    }
    QList<QLineEdit*> matrix2_labels = get_matrix2_Labels_QList(ui);
    for (QLineEdit* lineEdit : matrix2_labels) {
        lineEdit->setText("0");
    }
    ui->tWsolution->clear();
    ui->tWsolution->setRowCount(0);
    ui->tWsolution->setColumnCount(0);
    ui->M1_00->show();
    ui->M2_00->show();
    ui->NumRowsM2->show();
    ui->NumColumnsM2->show();
    ui->lblM2rowCount->show();
    ui->lblM2ColumnCount->show();
    ui->lblScaler->hide();
    ui->lEscaler->hide();
    ui->lblTranspose->hide();
    ui->NumRowsM1->setValue(1);
    ui->NumRowsM2->setValue(1);
    ui->NumColumnsM1->setValue(1);
    ui->NumColumnsM2->setValue(1);

    // hide solution widgets
    ui->tWsolution->hide();
    ui->lblequals->hide();

    // switch to change widgets that appear / widgets text depending on the operation
    switch (index) {
    case 0: {
        // addition
        ui->lbloperation->setText("+");
        break;
    }
    case 1: {
        // subtraction
        ui->lbloperation->setText("-");
        break;
    }
    case 2: {
        // multiplication
        ui->lbloperation->setText("x");
        break;
    }
    case 3: {
        // scaler multiplication
        ui->lbloperation->setText("");
        // hide the matrix 2 widgets
        QList<QLineEdit*> matrix1_labels = get_matrix2_Labels_QList(ui);
        for (QLineEdit* lineEdit : matrix1_labels) {
                lineEdit->setText("0");
                lineEdit->hide();
        }
        ui->NumRowsM2->hide();
        ui->NumColumnsM2->hide();
        ui->lblM2rowCount->hide();
        ui->lblM2ColumnCount->hide();
        ui->lblScaler->show();
        ui->lblScaler->setText("x");
        ui->lEscaler->show();
        break;
    }
    case 4: {
        // scaler division
        ui->lbloperation->setText("");
        // hide the matrix 2 widgets
        QList<QLineEdit*> matrix1_labels = get_matrix2_Labels_QList(ui);
        for (QLineEdit* lineEdit : matrix1_labels) {
                lineEdit->setText("0");
                lineEdit->hide();
        }
        ui->NumRowsM2->hide();
        ui->NumColumnsM2->hide();
        ui->lblM2rowCount->hide();
        ui->lblM2ColumnCount->hide();
        ui->lblScaler->show();
        // show scaler info
        ui->lblScaler->setText(QString::fromUtf8("\u00F7"));
        ui->lEscaler->show();
        break;
    }
    case 5: {
        // determinant
        // hide the matrix 2 widgets
        QList<QLineEdit*> matrix1_labels = get_matrix2_Labels_QList(ui);
        for (QLineEdit* lineEdit : matrix1_labels) {
                lineEdit->setText("0");
                lineEdit->hide();
        }
        ui->lbloperation->setText("");
        ui->NumRowsM2->hide();
        ui->NumColumnsM2->hide();
        ui->lblM2rowCount->hide();
        ui->lblM2ColumnCount->hide();
        break;
    }
    case 6: {
        // Inverse
        // hide the matrix 2 widgets
        QList<QLineEdit*> matrix1_labels = get_matrix2_Labels_QList(ui);
        for (QLineEdit* lineEdit : matrix1_labels) {
                lineEdit->setText("0");
                lineEdit->hide();
        }
        ui->lbloperation->setText("");
        ui->NumRowsM2->hide();
        ui->NumColumnsM2->hide();
        ui->lblM2rowCount->hide();
        ui->lblM2ColumnCount->hide();
        break;
    }
    case 7:{
        // transpose
        // hide the matrix 2 widgets
        QList<QLineEdit*> matrix1_labels = get_matrix2_Labels_QList(ui);
        for (QLineEdit* lineEdit : matrix1_labels) {
                lineEdit->setText("0");
                lineEdit->hide();
        }
        ui->lbloperation->setText("");
        ui->NumRowsM2->hide();
        ui->NumColumnsM2->hide();
        ui->lblM2rowCount->hide();
        ui->lblM2ColumnCount->hide();
        // show T
        ui->lblTranspose->show();
        break;
    }
    case 8:{
        // co-factors
        // hide the matrix 2 widgets
        QList<QLineEdit*> matrix1_labels = get_matrix2_Labels_QList(ui);
        for (QLineEdit* lineEdit : matrix1_labels) {
                lineEdit->setText("0");
                lineEdit->hide();
        }
        ui->lbloperation->setText("");
        ui->NumRowsM2->hide();
        ui->NumColumnsM2->hide();
        ui->lblM2rowCount->hide();
        ui->lblM2ColumnCount->hide();
        break;
    }
    }
}

