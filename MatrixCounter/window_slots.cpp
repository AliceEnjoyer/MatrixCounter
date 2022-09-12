#include "window.h"

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
    pMatrix3Model->setRowCount(pMatrix1Model->rowCount());
    pMatrix3Model->setColumnCount(pMatrix1Model->columnCount());
    for(int i = 0 ; i < pMatrix1Model->rowCount() ; ++i) {
        for(int j = 0; j < pMatrix1Model->columnCount() ; ++j) {
            pMatrix3Model->setData(i, j, pMatrix1Model->data(i, j) + pMatrix2Model->data(i, j));

        }
    }
}
void window::slotMinusClicked() {
    if(!isABEqual) {
        QMessageBox::information(0, "ERROR", "Matrices do not have same size");
        return;
    }
    pMatrix3Model->setRowCount(pMatrix1Model->rowCount());
    pMatrix3Model->setColumnCount(pMatrix1Model->columnCount());
    for(int i = 0 ; i < pMatrix1Model->rowCount() ; ++i) {
        for(int j = 0; j < pMatrix1Model->columnCount() ; ++j) {
            pMatrix3Model->setData(i, j, pMatrix1Model->data(i, j) - pMatrix2Model->data(i, j));

        }
    }
}

void window::slotSwapMatrices() {
    QHash<QModelIndex, int> bufMat1 = pMatrix1Model->GetMat();
    QHash<QModelIndex, int> bufMat2 = pMatrix2Model->GetMat();
    pMatrix1Model->clearData();
    pMatrix2Model->clearData();
    int rows = pMatrix1Model->rowCount();
    int cols = pMatrix1Model->columnCount();
    pMatrix1Model->setRowCount(pMatrix2Model->rowCount());
    pMatrix1Model->setColumnCount(pMatrix2Model->columnCount());
    pMatrix2Model->setRowCount(rows);
    pMatrix2Model->setColumnCount(cols);
    pMatrix1Model->SetMat(bufMat2);
    pMatrix2Model->SetMat(bufMat1);

//    int rows2 = ;
//    int cols2 = ;
//
//    pMatrix1Model->setRowCount(rows2);
//    pMatrix1Model->setColumnCount(cols2);
//    pMatrix2Model->setRowCount(rows1);
//    pMatrix2Model->setColumnCount(cols1);
//    for (int i = 0; i < rows1; ++i) {
//        for (int j = 0; j < cols1; ++j) {
//            pMatrix2Model->setData(i, j, bufMat1.value(pMatrix1Model->index(i, j)));
//            qDebug() << "2\n";
//        }
//    }
//    for (int i = 0; i < rows2; ++i) {
//        for (int j = 0; j < cols2; ++j) {
//            pMatrix1Model->setData(i, j, bufMat2.value(pMatrix2Model->index(i, j)));
//            qDebug() << "1\n";
//        }
//    }
}

void window::slotMultiplyClicked() {
    if(pMatrix1Model->columnCount() != pMatrix2Model->rowCount()) {
        QMessageBox::information(0, "ERROR", "Matrices are not negotiated");
        return;
    }
    pMatrix3Model->setRowCount(pMatrix1Model->rowCount());
    pMatrix3Model->setColumnCount(pMatrix2Model->columnCount());
    QHash<QModelIndex, int> mat1 = pMatrix1Model->GetMat();
    QHash<QModelIndex, int> mat2 = pMatrix2Model->GetMat();
    QHash<QModelIndex, int> mat;
    for (int i = 0; i < pMatrix2Model->columnCount(); ++i){
        for (int j = 0; j < pMatrix2Model->rowCount(); ++j){
            mat.insert(pMatrix2Model->index(i, j), mat2.value(pMatrix2Model->index(j, i)));
        }
    }

        for (int i2 = 0 ; i2 < pMatrix2Model->columnCount(); ++i2) {
            for (int i = 0; i < pMatrix1Model->rowCount(); ++i){
                int buf = 0;
                for (int j = 0; j < pMatrix1Model->columnCount(); ++j){
                    buf += mat1.value(pMatrix1Model->index(i, j)) * mat.value(pMatrix2Model->index(i2, j));
                }


        }
    }
    //pMatrix3Model->setData(i, b, buf);
}
