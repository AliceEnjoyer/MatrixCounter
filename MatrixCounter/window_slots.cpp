#include "window.h"
#include "thread"
#include "chrono"

void window::slotSetNewMatrixSizeFromDialog() {
    pMatrix1Model->setRowCount(bSetRowsSize1->text().toInt());
    pMatrix1Model->setColumnCount(bSetColsSize1->text().toInt());
    pMatrix2Model->setRowCount(bSetRowsSize2->text().toInt());
    pMatrix2Model->setColumnCount(bSetColsSize2->text().toInt());

    if(pMatrix1Model->rowCount() == 0 || pMatrix1Model->columnCount() == 0) {
        AMatInfo->setText("A is empty");
        return;
    } else if(pMatrix1Model->rowCount() == pMatrix1Model->columnCount()){
        AMatInfo->setText("A is a square matrix");

    } else {
        AMatInfo->setText("A is a rectangular matrix");
        if(pMatrix1Model->rowCount() == 1 && pMatrix1Model->columnCount() > 1) {
            AMatInfo->setText(AMatInfo->text() + "; A is a row matrix");
        } else if (pMatrix1Model->columnCount() == 1 && pMatrix1Model->rowCount() > 1) {
            AMatInfo->setText(AMatInfo->text() + "; A is a column matrix");
        }
    }

    if(pMatrix2Model->rowCount() == 0 || pMatrix2Model->columnCount() == 0) {
        BMatInfo->setText("B is empty");
        return;
    } else if(pMatrix2Model->rowCount() == pMatrix2Model->columnCount()) {
        BMatInfo->setText("B is a square matrix");

    } else {
        BMatInfo->setText("B is a rectangular matrix");
        if(pMatrix2Model->rowCount() == 1 && pMatrix2Model->columnCount() > 1) {
            BMatInfo->setText(BMatInfo->text() + "; B is a row matrix");
        } else if (pMatrix2Model->columnCount() == 1 && pMatrix2Model->rowCount() > 1) {
            BMatInfo->setText(BMatInfo->text() + "; B is a column matrix");
        }
    }
    if(pMatrix1Model->rowCount() == pMatrix2Model->rowCount() &&
       pMatrix1Model->columnCount() == pMatrix2Model->columnCount()) isABEqual = true;
    else isABEqual = false;
}


void window::slotDioSetNewMatSizeShow() {
    bSetRowsSize1->setText(QString::number(pMatrix1Model->rowCount()));
    bSetColsSize1->setText(QString::number(pMatrix1Model->columnCount()));
    bSetRowsSize2->setText(QString::number(pMatrix2Model->rowCount()));
    bSetColsSize2->setText(QString::number(pMatrix2Model->columnCount()));
    dioSetNewMatSize->show();
}

void window::slotPlusClicked() {
    if(!isABEqual) {
        QMessageBox::information(0, "ERROR", "Matrices do not have same size");
        return;
    }
    pMatrix3->setRowCount(pMatrix1Model->rowCount());
    pMatrix3->setColumnCount(pMatrix1Model->columnCount());
    if(pMatrix1Model->rowCount() == pMatrix2Model->rowCount() && pMatrix1Model->columnCount() == pMatrix2Model->columnCount()) {
        for(int i = 0 ; i < pMatrix1Model->rowCount() ; ++i) {
            for(int j = 0; j < pMatrix1Model->columnCount() ; ++j) {
                int bufI1 = pMatrix1Model->data(i, j);
                int bufI2 = pMatrix2Model->data(i, j);
                auto model = pMatrix3->model();
                model->setData(model->index(i, j), QString::number(bufI1 + bufI2));

            }
        }
    }
}
void window::slotMinusClicked() {
    if(!isABEqual) {
        QMessageBox::information(0, "ERROR", "Matrices do not have same size");
        return;
    }
    pMatrix3->setRowCount(pMatrix1Model->rowCount());
    pMatrix3->setColumnCount(pMatrix1Model->columnCount());
    if(pMatrix1Model->rowCount() == pMatrix2Model->rowCount() && pMatrix1Model->columnCount() == pMatrix2Model->columnCount()) {
        for(int i = 0 ; i < pMatrix1Model->rowCount() ; ++i) {
            for(int j = 0; j < pMatrix1Model->columnCount() ; ++j) {
                int bufI1 = pMatrix1Model->data(i, j);
                int bufI2 = pMatrix2Model->data(i, j);
                auto model = pMatrix3->model();
                model->setData(model->index(i, j), QString::number(bufI1 - bufI2));

            }
        }
    }
}

void window::slotSwapMatrices() {

}

void window::slotMultiplyClicked() {

}
