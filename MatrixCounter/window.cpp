#include "window.h"

window::window(QWidget *parent) : QWidget(parent) {

    pMatrix1 = new QTableWidget();
    pMatrix2 = new QTableWidget();
    pMatrix3 = new QTableWidget();

    plus = new QPushButton("+");
    bSetNewMatrixSize = new QPushButton("Set matrix size...");



    dioSetNewMatSize = new QDialog;
    enterMatSize = new QPushButton("Enter matrix size");
    bSetRowsSize1 = new QLineEdit;
    bSetColsSize1 = new QLineEdit;
    bSetRowsSize2 = new QLineEdit;
    bSetColsSize2 = new QLineEdit;

    bSetRowsSize1->setValidator(new QIntValidator());
    bSetColsSize1->setValidator(new QIntValidator());
    bSetRowsSize2->setValidator(new QIntValidator());
    bSetColsSize2->setValidator(new QIntValidator());

    QHBoxLayout *hbl1 = new QHBoxLayout;
    hbl1->addWidget(new QLabel("A Rows: "));
    hbl1->addWidget(bSetRowsSize1);
    QHBoxLayout *hbl2 = new QHBoxLayout;
    hbl2->addWidget(new QLabel("A Columns: "));
    hbl2->addWidget(bSetColsSize1);
    QHBoxLayout *hbl3 = new QHBoxLayout;
    hbl1->addWidget(new QLabel("B Rows: "));
    hbl1->addWidget(bSetRowsSize2);
    QHBoxLayout *hbl4 = new QHBoxLayout;
    hbl2->addWidget(new QLabel("B Columns: "));
    hbl2->addWidget(bSetColsSize2);
    QVBoxLayout *vbl = new QVBoxLayout;
    vbl->addLayout(hbl1);
    vbl->addLayout(hbl2);
    vbl->addLayout(hbl3);
    vbl->addLayout(hbl4);
    vbl->addWidget(enterMatSize);
    dioSetNewMatSize->setLayout(vbl);

    connect(bSetNewMatrixSize, &QPushButton::clicked, this, &window::slotDioSetNewMatSizeShow);
    connect(enterMatSize, &QPushButton::clicked, this, &window::slotSetNewMatrixSizeFromDialog);

    QVBoxLayout *vbl1 = new QVBoxLayout;
    vbl1->addWidget(new QLabel("A: "));
    vbl1->addWidget(new QLabel("B: "));
    //vbl1->setSpacing();

    QVBoxLayout *vbl2 = new QVBoxLayout;
    vbl2->addWidget(pMatrix1);
    vbl2->addWidget(pMatrix2);
    vbl2->addWidget(bSetNewMatrixSize);


    hbl = new QHBoxLayout;
    hbl->addLayout(vbl1);
    hbl->addLayout(vbl2);

    setLayout(hbl);

    //testGetFromMatrix(1, 2);
}

