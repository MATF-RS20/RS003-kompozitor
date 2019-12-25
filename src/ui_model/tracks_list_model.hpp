#ifndef KOMPOZITOR_TRACKS_LIST_MODEL_HPP
#define KOMPOZITOR_TRACKS_LIST_MODEL_HPP

#include <QtCore/QAbstractListModel>
#include "track_note.hpp"
#include "note_track.hpp"

class TracksListModel: public QAbstractListModel {

Q_OBJECT
Q_PROPERTY(QList<NoteTrack*> tracks READ tracks WRITE set_tracks NOTIFY onTracksChanged)

public:
    enum RoleType {
        TRACK_DATA = Qt::UserRole + 1,
        TRACK_NUMBER,
        TRACK_TYPE
    };

    explicit TracksListModel(QObject* parent = nullptr) {};

    [[nodiscard]]
    int rowCount(const QModelIndex &parent) const override;

    [[nodiscard]]
    int columnCount(const QModelIndex &parent) const override;

    [[nodiscard]]
    QVariant data(const QModelIndex &index, int role) const override;

    [[nodiscard]]
    QHash<int, QByteArray> roleNames() const override;

    [[nodiscard]]
    QList<NoteTrack*> tracks() const;

    void set_tracks(const QList<NoteTrack*>& tracks);

signals:
    void onTracksChanged();

private:
    QList<NoteTrack*> _tracks;
};

#endif //KOMPOZITOR_TRACKS_LIST_MODEL_HPP
