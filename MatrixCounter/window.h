#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>

class window : public QWidget {
    Q_OBJECT
private:
    QHBoxLayout* hbl;
    QTableWidget* pMatrix1;
    QTableWidget* pMatrix2;
    QTableWidget* pMatrix3;

    QPushButton* bSetNewMatrixSize;
    QPushButton* plus;

    QDialog* dioSetNewMatSize;
    QLineEdit* bSetRowsSize1;
    QLineEdit* bSetColsSize1;
    QLineEdit* bSetRowsSize2;
    QLineEdit* bSetColsSize2;
    QPushButton *enterMatSize;


public:
    window(QWidget *parent = nullptr);
    void testGetFromMatrix();
private slots:
    void slotSetNewMatrixSizeFromDialog();
    void slotDioSetNewMatSizeShow();
};
#endif // WINDOW_H
