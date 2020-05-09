#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>

class TableModel : public QAbstractTableModel
{
public:
    TableModel();
    // Required function overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    // Editable required function overrides
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    // Resizable required function overrides
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

private:
    struct file_display {
        file_display() : name(QString("")), size(QString("")), created(QString("")), updated(QString("")) {}
        QVariant name;
        QVariant size;
        QVariant created;
        QVariant updated;
    };
    uint num_rows;
    uint num_cols;
    std::vector<file_display*> file_table;
};

#endif // TABLEMODEL_H
