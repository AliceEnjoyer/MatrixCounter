#include "window.h"
#include "thread"
#include "chrono"

void window::slotSetNewMatrixSizeFromDialog() {
    pMatrix1->setRowCount(bSetRowsSize1->text().toInt());
    pMatrix1->setColumnCount(bSetColsSize1->text().toInt());
    pMatrix2->setRowCount(bSetRowsSize2->text().toInt());
    pMatrix2->setColumnCount(bSetColsSize2->text().toInt());

    if(pMatrix1->rowCount() == 0 || pMatrix1->columnCount() == 0) {
        AMatInfo->setText("A is empty");
        return;
    } else if(pMatrix1->rowCount() == pMatrix1->columnCount()){
        AMatInfo->setText("A is a square matrix");

    } else {
        AMatInfo->setText("A is a rectangular matrix");
        if(pMatrix1->rowCount() == 1 && pMatrix1->columnCount() > 1) {
            AMatInfo->setText(AMatInfo->text() + "; A is a row matrix");
        } else if (pMatrix1->columnCount() == 1 && pMatrix1->rowCount() > 1) {
            AMatInfo->setText(AMatInfo->text() + "; A is a column matrix");
        }
    }

    if(pMatrix2->rowCount() == 0 || pMatrix2->columnCount() == 0) {
        BMatInfo->setText("B is empty");
        return;
    } else if(pMatrix2->rowCount() == pMatrix2->columnCount()) {
        BMatInfo->setText("B is a square matrix");

    } else {
        BMatInfo->setText("B is a rectangular matrix");
        if(pMatrix2->rowCount() == 1 && pMatrix2->columnCount() > 1) {
            BMatInfo->setText(BMatInfo->text() + "; B is a row matrix");
        } else if (pMatrix2->columnCount() == 1 && pMatrix2->rowCount() > 1) {
            BMatInfo->setText(BMatInfo->text() + "; B is a column matrix");
        }
    }
    if(pMatrix1->rowCount() == pMatrix2->rowCount() &&
       pMatrix1->columnCount() == pMatrix2->columnCount()) isABEqual = true;
    else isABEqual = false;
}


void window::slotDioSetNewMatSizeShow() {
    bSetRowsSize1->setText(QString::number(pMatrix1->rowCount()));
    bSetColsSize1->setText(QString::number(pMatrix1->columnCount()));
    bSetRowsSize2->setText(QString::number(pMatrix2->rowCount()));
    bSetColsSize2->setText(QString::number(pMatrix2->columnCount()));
    dioSetNewMatSize->show();
}

void window::slotPlusClicked() {
    if(!isABEqual) {
        QMessageBox::information(0, "ERROR", "Matrices do not have same size");
        return;
    }
    pMatrix3->setRowCount(pMatrix1->rowCount());
    pMatrix3->setColumnCount(pMatrix1->columnCount());
    bool bufB1; // buffer boolean
    bool bufB2;
    if(pMatrix1->rowCount() == pMatrix2->rowCount() && pMatrix1->columnCount() == pMatrix2->columnCount()) {
        for(int i = 0 ; i < pMatrix1->rowCount() ; ++i) {
            for(int j = 0; j < pMatrix1->columnCount() ; ++j) {
                auto model1 = pMatrix1->model();
                auto model2 = pMatrix2->model();
                int bufI1 = model1->data(model1->index(i, j)).toInt(&bufB1);
                int bufI2 = model2->data(model2->index(i, j)).toInt(&bufB2);
                if(bufB1 && bufB2) {
                    auto model = pMatrix3->model();
                    model->setData(model->index(i, j), QString::number(bufI1 + bufI2));
                } else {
                    pMatrix3->setRowCount(0);
                    pMatrix3->setColumnCount(0);
                    QMessageBox::information(0, "ERROR", "You have entered a wrong characters");
                    return;
                }
            }
        }
    }
}
void window::slotMinusClicked() {
    if(!isABEqual) {
        QMessageBox::information(0, "ERROR", "Matrices do not have same size");
        return;
    }
    pMatrix3->setRowCount(pMatrix1->rowCount());
    pMatrix3->setColumnCount(pMatrix1->columnCount());
    bool bufB1; // buffer boolean
    bool bufB2;
    if(pMatrix1->rowCount() == pMatrix2->rowCount() && pMatrix1->columnCount() == pMatrix2->columnCount()) {
        for(int i = 0 ; i < pMatrix1->rowCount() ; ++i) {
            for(int j = 0; j < pMatrix1->columnCount() ; ++j) {
                auto model1 = pMatrix1->model();
                auto model2 = pMatrix2->model();
                int bufI1 = model1->data(model1->index(i, j)).toInt(&bufB1);
                int bufI2 = model2->data(model2->index(i, j)).toInt(&bufB2);
                if(bufB1 && bufB2) {
                    auto model = pMatrix3->model();
                    model->setData(model->index(i, j), QString::number(bufI1 - bufI2));
                } else {
                    pMatrix3->setRowCount(0);
                    pMatrix3->setColumnCount(0);
                    QMessageBox::information(0, "ERROR", "You have entered a wrong characters");
                    return;
                }
            }
        }
    }
}

void window::slotMultiplyClicked() {

}
