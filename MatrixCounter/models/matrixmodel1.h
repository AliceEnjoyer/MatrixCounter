#ifndef MATRIXMODEL1_H
#define MATRIXMODEL1_H

#include <QAbstractListModel>

class MatrixModel1 : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit MatrixModel1 (int rows, int cols, QObject* obj = nullptr);

    QVariant data (const QModelIndex& index, int role) const override;
    int data (int i, int j) const;
    bool setData (const QModelIndex& index, const QVariant& data, int role) override;
    void setData (int i, int j, const int& data);
    void clearData();

    int rowCount (const QModelIndex& index = QModelIndex()) const override;
    int columnCount ( const QModelIndex& parent = QModelIndex()) const override;

    QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags (const QModelIndex&) const override;

    void setRowCount (int);
    void setColumnCount (int);

    QVector<QVector<int>> GetVectoredMat();
private:
    QHash<QModelIndex, int> mat;
    int rows;
    int cols;
};

#endif // MATRIXMODEL1_H
