#include "tracks_list_model.hpp"

// FIXME: This model is currently erroneously implemented, and is only a placeholder

int TracksListModel::rowCount(const QModelIndex &parent) const {
    return _data.length();
}

int TracksListModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

QVariant TracksListModel::data(const QModelIndex &index, int role) const {

    if (!index.isValid()) {
        return QVariant();
    }

    // Assuming column == 0
    return QVariant::fromValue(_data[index.row()]);
}