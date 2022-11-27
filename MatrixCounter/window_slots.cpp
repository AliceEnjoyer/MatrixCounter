#include "window.h"

void window::slotSetNewMatrixSizeFromDialog() {
    pMatrix1Model->setRowCount(bSetRowsSize1->text().toInt());
    pMatrix1Model->setColumnCount(bSetColsSize1->text().toInt());
    pMatrix2Model->setRowCount(bSetRowsSize2->text().toInt());
    pMatrix2Model->setColumnCount(bSetColsSize2->text().toInt());

    if(pMatrix1Model->rowCount() == 0 || pMatrix1Model->columnCount() == 0) { AMatInfo->setText("A is empty"); }
    else if(pMatrix1Model->rowCount() == pMatrix1Model->columnCount()){ AMatInfo->setText("A is a square matrix"); }
    else {
        AMatInfo->setText("A is a rectangular matrix");
        if(pMatrix1Model->rowCount() == 1 && pMatrix1Model->columnCount() > 1) { AMatInfo->setText(AMatInfo->text() + "; A is a row matrix"); }
        else if (pMatrix1Model->columnCount() == 1 && pMatrix1Model->rowCount() > 1) { AMatInfo->setText(AMatInfo->text() + "; A is a column matrix"); }
    }

    if(pMatrix2Model->rowCount() == 0 || pMatrix2Model->columnCount() == 0) { BMatInfo->setText("B is empty"); }
    else if(pMatrix2Model->rowCount() == pMatrix2Model->columnCount()) { BMatInfo->setText("B is a square matrix"); }
    else {
        BMatInfo->setText("B is a rectangular matrix");
        if(pMatrix2Model->rowCount() == 1 && pMatrix2Model->columnCount() > 1) { BMatInfo->setText(BMatInfo->text() + "; B is a row matrix"); }
        else if (pMatrix2Model->columnCount() == 1 && pMatrix2Model->rowCount() > 1) { BMatInfo->setText(BMatInfo->text() + "; B is a column matrix"); }
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
    QVector<QVector<double>> mat1 = pMatrix1Model->GetVectoredMat();
    QVector<QVector<double>> mat2 = pMatrix2Model->GetVectoredMat();
    pMatrix1Model->clearData();
    pMatrix2Model->clearData();
    int rows1 = pMatrix1Model->rowCount();
    int cols1 = pMatrix1Model->columnCount();
    int rows2 = pMatrix2Model->rowCount();
    int cols2 = pMatrix2Model->columnCount();
    pMatrix1Model->setRowCount(rows2);
    pMatrix1Model->setColumnCount(cols2);
    pMatrix2Model->setRowCount(rows1);
    pMatrix2Model->setColumnCount(cols1);

    for (int i = 0; i < rows1; ++i) { for (int j = 0; j < cols1; ++j) { pMatrix2Model->setData(i, j, mat1[i][j]); } }
    for (int i = 0; i < rows2; ++i) { for (int j = 0; j < cols2; ++j) { pMatrix1Model->setData(i, j, mat2[i][j]); } }
}

void window::slotMultiplyClicked() {
    if(pMatrix2Model->rowCount() == 1 && pMatrix2Model->columnCount() == 1){
        pMatrix3Model->setRowCount(pMatrix1Model->rowCount());
        pMatrix3Model->setColumnCount(pMatrix1Model->columnCount());
        QVector<QVector<double>> mat = pMatrix1Model->GetVectoredMat();
        int s = pMatrix2Model->data(0, 0);
        for(int i = 0; i < pMatrix1Model->rowCount(); ++i){
            for(int j = 0 ; j < pMatrix1Model->columnCount(); ++j){
                pMatrix3Model->setData(i, j, s * mat[i][j]);
            }
        }

        return;
    }
    if(pMatrix1Model->columnCount() != pMatrix2Model->rowCount()) {
        QMessageBox::information(0, "ERROR", "Matrices are not negotiated or matrix B has more than one item");
        return;
    }
    pMatrix3Model->setRowCount(pMatrix1Model->rowCount());
    pMatrix3Model->setColumnCount(pMatrix2Model->columnCount());
    QVector<QVector<double>> mat1 = pMatrix1Model->GetVectoredMat();
    QVector<QVector<double>> mat2 = pMatrix2Model->GetVectoredMat();

    for (int j2 = 0 ; j2 < pMatrix2Model->columnCount(); ++j2) {
        QVector<int> bufArr;
        for (int i1 = 0; i1 < pMatrix1Model->rowCount(); ++i1) {
            int buf = 0;
            for(int j = 0 ; j < pMatrix1Model->columnCount() ; ++ j) { buf += mat1[i1][j] * mat2[j][j2]; }
            pMatrix3Model->setData(i1, j2, buf);
        }
    }
}

void window::slotFindReversedA() {
    if(pMatrix1Model->rowCount() != pMatrix1Model->columnCount() || pMatrix1Model->rowCount() == 0 || pMatrix1Model->columnCount() == 0) {
        QMessageBox::information(0, "ERROR", "Matrix is not a square matrix");
        return;
    }
    QVector<QVector<double>> bufDet = pMatrix1Model->GetVectoredMat(); // buffer determ.
    QVector<QVector<double>> res;

    int detSize = bufDet.size(); // size of determ.

    for(int i = 0; i < detSize; ++i) {
        res.append(QVector<double>());
        for (int j = 0; j < detSize; ++j) {
            if(i == j) res[i].append(1);
            else res[i].append(0);
        }
    }

    for(int m = 0; m < detSize; ++m){
        for (int row = m + 1; row < detSize; ++row) {
            for (int count = row; bufDet[m][m] == 0 && count < detSize; ++count) {
                bufDet[m].swap(bufDet[count]);
                res[m].swap(res[count]);
            }
            if(bufDet[m][m] == 0) {
                break;
            }
            double k = bufDet[row][m]/bufDet[m][m];
            for (int col = m; col < detSize; ++col) {
                bufDet[row][col] = bufDet[row][col] - bufDet[m][col] * k;
                res[row][col] = res[row][col] - res[m][col] * k;
            }
            double temp = bufDet[m][m];
            for (int col = 0; col < detSize; ++col) {
                bufDet[m][col] = bufDet[m][col] / temp;
                res[m][col] = res[m][col]/temp;
            }
        }
    }
    int tempM = detSize - 1;
    double temp = bufDet[tempM][tempM];
    for (int col = 0; col < detSize; ++col) {
        bufDet[tempM][col] = bufDet[tempM][col] / temp;
        res[tempM][col] = res[tempM][col]/temp;
    }

    for (int m = 0; m < detSize; ++ m) {
        for (int row = m ; row > 0; --row){
            double k = bufDet[row - 1][m];
            for (int col = 0 ; col < detSize; ++col) {
                bufDet[row - 1][col] = bufDet[row - 1][col] - bufDet[m][col] * k;
                res[row - 1][col] = res[row - 1][col] - res[m][col] * k;
            }
        }
    }
    pMatrix3Model->setRowCount(detSize);
    pMatrix3Model->setColumnCount(detSize);
    for (int i = 0 ; i < detSize; ++i){
        for (int j = 0; j < detSize; ++j) {
            pMatrix3Model->setData(i, j, res[i][j]);
        }
    }
}

void window::slotFindReversedB() {
    if(pMatrix2Model->rowCount() != pMatrix2Model->columnCount() || pMatrix2Model->rowCount() == 0 || pMatrix2Model->columnCount() == 0) {
        QMessageBox::information(0, "ERROR", "Matrix is not a square matrix");
        return;
    }
    QVector<QVector<double>> bufDet = pMatrix2Model->GetVectoredMat(); // buffer determ.
    QVector<QVector<double>> res;

    int detSize = bufDet.size(); // size of determ.

    for(int i = 0; i < detSize; ++i) {
        res.append(QVector<double>());
        for (int j = 0; j < detSize; ++j) {
            if(i == j) res[i].append(1);
            else res[i].append(0);
        }
    }

    for(int m = 0; m < detSize; ++m){
        for (int row = m + 1; row < detSize; ++row) {
            for (int count = row; bufDet[m][m] == 0 && count < detSize; ++count) {
                bufDet[m].swap(bufDet[count]);
                res[m].swap(res[count]);
            }
            if(bufDet[m][m] == 0) {
                break;
            }
            double k = bufDet[row][m]/bufDet[m][m];
            for (int col = m; col < detSize; ++col) {
                bufDet[row][col] = bufDet[row][col] - bufDet[m][col] * k;
                res[row][col] = res[row][col] - res[m][col] * k;
            }
            double temp = bufDet[m][m];
            for (int col = 0; col < detSize; ++col) {
                bufDet[m][col] = bufDet[m][col] / temp;
                res[m][col] = res[m][col]/temp;
            }
        }
    }
    int tempM = detSize - 1;
    double temp = bufDet[tempM][tempM];
    for (int col = 0; col < detSize; ++col) {
        bufDet[tempM][col] = bufDet[tempM][col] / temp;
        res[tempM][col] = res[tempM][col]/temp;
    }

    for (int m = 0; m < detSize; ++ m) {
        for (int row = m ; row > 0; --row){
            double k = bufDet[row - 1][m];
            for (int col = 0 ; col < detSize; ++col) {
                bufDet[row - 1][col] = bufDet[row - 1][col] - bufDet[m][col] * k;
                res[row - 1][col] = res[row - 1][col] - res[m][col] * k;
            }
        }
    }
    pMatrix3Model->setRowCount(detSize);
    pMatrix3Model->setColumnCount(detSize);
    for (int i = 0 ; i < detSize; ++i){
        for (int j = 0; j < detSize; ++j) {
            pMatrix3Model->setData(i, j, res[i][j]);
        }
    }
}
