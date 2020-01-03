#include "tracks_list_model.hpp"
#include "note_track.hpp"

int TracksListModel::rowCount(const QModelIndex &parent) const {
    return _tracks.size();
}

int TracksListModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

QHash<int, QByteArray> TracksListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TRACK_DATA] = "dataNotes";
    roles[TRACK_NUMBER] = "dataTrackNumber";
    roles[TRACK_TYPE] = "dataTrackType";
    return roles;
}

QVariant TracksListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    Track* track = _tracks[index.row()];

    if (auto *note_track = dynamic_cast<NoteTrack*>(track)) {
        switch (role) {
            case TRACK_DATA:
                return QVariant::fromValue(note_track->notes());
            case TRACK_NUMBER:
                return QVariant::fromValue(note_track->id());
            case TRACK_TYPE:
                return QVariant::fromValue(1);
            default:
                return QVariant();
        }
    }

    // TODO add the SampleTrack type
}

QList<Track*> TracksListModel::tracks() const{
    return _tracks;
}

void TracksListModel::set_tracks(const QList<Track*>& tracks) {
    emit layoutAboutToBeChanged();
    _tracks = tracks;
    emit onTracksChanged();
    emit layoutChanged();
}
