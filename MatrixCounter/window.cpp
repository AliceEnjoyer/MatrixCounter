#include "window.h"

window::window(QWidget *parent) : QWidget(parent) {

    //init vars
    pMatrix1 = new QTableWidget();
    pMatrix2 = new QTableWidget();
    pMatrix3 = new QTableWidget();

    bPlus = new QPushButton("A + B");
    bMinus = new QPushButton("A - B");
    bMultiply = new QPushButton("A * B");
    bSetNewMatrixSize = new QPushButton("Set matrix size...");

    bPlus->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    bMinus->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    bMultiply->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    AMatInfo = new QLabel("A is empty");
    BMatInfo = new QLabel("B is empty");

///// dialog
    dioSetNewMatSize = new QDialog(this);
    enterMatSize = new QPushButton("Enter matrix size");
    bSetRowsSize1 = new QLineEdit;
    bSetColsSize1 = new QLineEdit;
    bSetRowsSize2 = new QLineEdit;
    bSetColsSize2 = new QLineEdit;

    bSetRowsSize1->setValidator(new QIntValidator());
    bSetColsSize1->setValidator(new QIntValidator());
    bSetRowsSize2->setValidator(new QIntValidator());
    bSetColsSize2->setValidator(new QIntValidator());

    QHBoxLayout *hbl1d = new QHBoxLayout;
    hbl1d->addWidget(new QLabel("A Rows: "));
    hbl1d->addWidget(bSetRowsSize1);
    QHBoxLayout *hbl2d = new QHBoxLayout;
    hbl2d->addWidget(new QLabel("A Columns: "));
    hbl2d->addWidget(bSetColsSize1);
    QHBoxLayout *hbl3d = new QHBoxLayout;
    hbl1d->addWidget(new QLabel("B Rows: "));
    hbl1d->addWidget(bSetRowsSize2);
    QHBoxLayout *hbl4d = new QHBoxLayout;
    hbl2d->addWidget(new QLabel("B Columns: "));
    hbl2d->addWidget(bSetColsSize2);
    QVBoxLayout *vbld = new QVBoxLayout;
    vbld->addLayout(hbl1d);
    vbld->addLayout(hbl2d);
    vbld->addLayout(hbl3d);
    vbld->addLayout(hbl4d);
    vbld->addWidget(enterMatSize);
    dioSetNewMatSize->setLayout(vbld);
///// dialog/

    //connection
    connect(bSetNewMatrixSize, &QPushButton::clicked, this, &window::slotDioSetNewMatSizeShow);
    connect(enterMatSize, &QPushButton::clicked, this, &window::slotSetNewMatrixSizeFromDialog);
    connect(bPlus, &QPushButton::clicked, this, &window::slotPlusClicked);
    connect(bMinus, &QPushButton::clicked, this, &window::slotMinusClicked);
    connect(bMultiply, &QPushButton::clicked, this, &window::slotMultiplyClicked);

/////// Layout setup
    QVBoxLayout *vbl1 = new QVBoxLayout;
    vbl1->addWidget(new QLabel("A: "));
    vbl1->addWidget(new QLabel("B: "));
    //vbl1->setSpacing();

    QVBoxLayout *vbl2 = new QVBoxLayout;
    vbl2->addWidget(pMatrix1);
    vbl2->addWidget(pMatrix2);
    vbl2->addWidget(bSetNewMatrixSize);

    QVBoxLayout *vbl3 = new QVBoxLayout;
    vbl3->addWidget(bPlus);
    vbl3->addWidget(bMinus);
    vbl3->addWidget(bMultiply);

    QVBoxLayout *vbl4 = new QVBoxLayout;
    QHBoxLayout *hblBuf1 = new QHBoxLayout;
    hblBuf1->addWidget(new QLabel("               C: "));
    hblBuf1->addWidget(pMatrix3);
    vbl4->addLayout(hblBuf1);

    QHBoxLayout *hbl = new QHBoxLayout;
    hbl->addLayout(vbl1);
    hbl->addLayout(vbl2);
    hbl->addLayout(vbl3);
    hbl->addLayout(vbl4);

    vbl = new QVBoxLayout;
    vbl->addLayout(hbl);
    vbl->addSpacing(10);
    vbl->addWidget(AMatInfo);
    vbl->addWidget(BMatInfo);
    vbl->addSpacing(10);
    vbl->setAlignment(AMatInfo, Qt::AlignHCenter);
    vbl->setAlignment(BMatInfo, Qt::AlignHCenter);

    setLayout(vbl);

    //testGetFromMatrix(1, 2);
}

