#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include "models/matrixmodel1.h"
#include "models/matrixmodel2.h"

class window : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* vbl;
    MatrixModel1* pMatrix1Model; // A matrix
    MatrixModel1* pMatrix2Model; // B matrix
    MatrixModel2* pMatrix3Model; // С matrix

    QPushButton* bSetNewMatrixSize;
    QPushButton* bPlus;
    QPushButton* bMinus;
    QPushButton* bMultiply;
    QPushButton* bSwapMatrices;

    QDialog* dioSetNewMatSize;
    QLineEdit* bSetRowsSize1;
    QLineEdit* bSetColsSize1;
    QLineEdit* bSetRowsSize2;
    QLineEdit* bSetColsSize2;
    QPushButton *enterMatSize;

    QLabel* AMatInfo;
    QLabel* BMatInfo;

    bool isABEqual;

public:
    window(QWidget *parent = nullptr);
private slots:
    void slotSetNewMatrixSizeFromDialog();
    void slotDioSetNewMatSizeShow();

    void slotPlusClicked();
    void slotMinusClicked();
    void slotMultiplyClicked();
    void slotSwapMatrices();
};
#endif // WINDOW_H
