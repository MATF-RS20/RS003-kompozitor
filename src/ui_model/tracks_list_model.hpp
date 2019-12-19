#ifndef KOMPOZITOR_TRACKS_LIST_MODEL_HPP
#define KOMPOZITOR_TRACKS_LIST_MODEL_HPP

// FIXME: This model is currently erroneously implemented, and is only a placeholder

#include <QtCore/QAbstractListModel>
#include "track_note.hpp"

class TracksListModel: public QAbstractListModel {

Q_OBJECT
public:

    explicit TracksListModel(QObject* parent = nullptr) {};

    [[nodiscard]]
    int rowCount(const QModelIndex &parent) const override;

    [[nodiscard]]
    int columnCount(const QModelIndex &parent) const override;

    [[nodiscard]]
    QVariant data(const QModelIndex &index, int role) const override;

private:
    // Temporary data for testing
    QList<QObject*> _data {
            new TrackNote(2, 0, 2),
            new TrackNote(5, 3, 4)
    };
};

#endif //KOMPOZITOR_TRACKS_LIST_MODEL_HPP
