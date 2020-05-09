#include "tablemodel.h"

TableModel::TableModel()
{
    //TableModel::file_display fileDisplay = TableModel::file_display();
    //fileDisplay.name = QString("name");
    //fileDisplay.size = QString("size");
    //fileDisplay.created = QString("created");
    //fileDisplay.updated = QString("updated");
    //TableModel::file_table.push_back(&fileDisplay);
    TableModel::num_rows = 0;
    TableModel::num_cols = 4;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    } else {
        return num_rows;
    }
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    } else {
        return num_cols;
    }
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= num_rows)
    {
        return QVariant();
    }
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (index.column())
        {
        case 0:
            return TableModel::file_table.at(index.row())->name;
            break;
        case 1:
            return TableModel::file_table.at(index.row())->size;
            break;
        case 2:
            return TableModel::file_table.at(index.row())->created;
            break;
        case 3:
            return TableModel::file_table.at(index.row())->updated;
            break;
        default:
            return QVariant();
            break;
        }
    }
    else
    {
        return QVariant();
    }
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0:
            return QString("Name");
        case 1:
            return QString("Size");
        case 2:
            return QString("Created");
        case 3:
            return QString("Updated");
        default:
            return QVariant();
        }
    }
    else
    {
        return QVariant();
    }
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
    {
        return false;
    }
    switch (index.column())
    {
    case 0:
        TableModel::file_table.at(index.row())->name = value;
        break;
    case 1:
        TableModel::file_table.at(index.row())->size = value;
        break;
    case 2:
        TableModel::file_table.at(index.row())->created = value;
        break;
    case 3:
        TableModel::file_table.at(index.row())->updated = value;
        break;
    }
    emit dataChanged(index, index, {role});
    return true;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::ItemIsEnabled;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    std::vector<file_display*>::iterator it;
    std::advance(it, row);
    beginInsertRows(parent, row, row + count - 1);
    TableModel::file_table.insert(it, count, nullptr);
    for (int i = row; i < count; i++)
    {
        TableModel::file_table.at(i) = new TableModel::file_display();
    }
    TableModel::num_rows += count;
    endInsertRows();
    return true;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    std::vector<file_display*>::iterator it_start;
    std::advance(it_start, row);
    std::vector<file_display*>::iterator it_end;
    std::advance(it_end, row + count - 1);
    beginRemoveRows(parent, row, row + count - 1);
    TableModel::file_table.erase(it_start, it_end);
    TableModel::num_rows -= count;
    endRemoveRows();
    return true;
}
