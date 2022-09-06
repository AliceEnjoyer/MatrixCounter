#include "window.h"

void window::slotSetNewMatrixSizeFromDialog() {
    pMatrix1->setRowCount(bSetRowsSize1->text().toInt());
    pMatrix1->setColumnCount(bSetColsSize1->text().toInt());
    pMatrix2->setRowCount(bSetRowsSize2->text().toInt());
    pMatrix2->setColumnCount(bSetColsSize2->text().toInt());
}

void window::slotDioSetNewMatSizeShow() {
    bSetRowsSize1->setText(QString::number(pMatrix1->rowCount()));
    bSetColsSize1->setText(QString::number(pMatrix1->columnCount()));
    bSetRowsSize2->setText(QString::number(pMatrix2->rowCount()));
    bSetColsSize2->setText(QString::number(pMatrix2->columnCount()));
    dioSetNewMatSize->show();
}
