#include "matrixmodel1.h"

MatrixModel1::MatrixModel1(int rowsCount, int colsCount, QObject* obj)
    : QAbstractTableModel(obj), rows(rowsCount), cols(colsCount)  { }

QVariant MatrixModel1::data(const QModelIndex &index, int role) const {
    if(!index.isValid() || index.row() > rows || index.column() > cols) return QVariant();
    return (role == Qt::DisplayRole || role == Qt::EditRole) ? mat.value(index, 0) : QVariant();
}

int MatrixModel1::data(int i, int j) const {
    return mat.value(index(i, j));
}

Qt::ItemFlags MatrixModel1::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    return index.isValid() ? (flags | Qt::ItemIsEditable) : flags;
}

bool MatrixModel1::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || index.row() > rows || index.column() > cols) return false;
    mat[index] = value.toInt();
    emit dataChanged(index, index);
    return true;
}

int MatrixModel1::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED(parent)
    return rows;
}

int MatrixModel1::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED(parent)
    return cols;
}

QVariant MatrixModel1::headerData (int section, Qt::Orientation orientation, int role) const {
    if( role != Qt::DisplayRole ) return QVariant();
    if( orientation == Qt::Vertical || orientation == Qt::Horizontal) return section;
    return QVariant();
}

void MatrixModel1::setRowCount(int rowCount) {
    this->rows = rowCount;
    emit layoutChanged();
}
void MatrixModel1::setColumnCount(int colCount) {
    this->cols = colCount;
    emit layoutChanged();
}

bool MatrixModel1::insertRows(int row, int count, const QModelIndex &index) {
    if(index.isValid()) return false;

    beginInsertRows(QModelIndex(), row, count - 1);
    for(int i = 0; i < count ; ++i){
        mat.insert(index, 0);
    }
    endInsertRows();

    return true;
}
