#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>

class window : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* vbl;
    QTableWidget* pMatrix1; // A matrix
    QTableWidget* pMatrix2; // B matrix
    QTableWidget* pMatrix3; // C matrix

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
    void testGetFromMatrix();
private:
    void multMats(QVector<QVector<int>>, QVector<QVector<int>>);
private slots:
    void slotSetNewMatrixSizeFromDialog();
    void slotDioSetNewMatSizeShow();

    void slotPlusClicked();
    void slotMinusClicked();
    void slotMultiplyClicked();
};
#endif // WINDOW_H
