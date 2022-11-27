#ifndef MATRIXMODEL2_H
#define MATRIXMODEL2_H
#include <QAbstractListModel>

class MatrixModel2 : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit MatrixModel2 (int rows, int cols, QObject* obj = nullptr);

    QVariant data (const QModelIndex& index, int role) const override;
    bool setData (const QModelIndex& index, const QVariant& data, int role) override;

    void setData (int i, int j, const double& data);

    int rowCount (const QModelIndex& index = QModelIndex()) const override;
    int columnCount ( const QModelIndex& parent = QModelIndex()) const override;

    QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void setRowCount (int);
    void setColumnCount (int);

private:
    QHash<QModelIndex, double> mat;
    int rows;
    int cols;
};


#endif // MATRIXMODEL2_H
