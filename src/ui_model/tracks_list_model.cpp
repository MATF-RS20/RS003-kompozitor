#include "tracks_list_model.hpp"
#include "note_track.hpp"
#include "sample_track.hpp"

int TracksListModel::rowCount(const QModelIndex &parent) const {
    return _tracks.size();
}

int TracksListModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

QHash<int, QByteArray> TracksListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TRACK_NOTES] = "dataNotes";
    roles[TRACK_SAMPLES] = "dataSamples";
    roles[TRACK_NUMBER] = "dataTrackNumber";
    roles[TRACK_TYPE] = "dataTrackType";
    return roles;
}

QVariant TracksListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    Track *track = _tracks[index.row()];

    if (auto *note_track = dynamic_cast<NoteTrack *>(track)) {
        switch (role) {
            case TRACK_NOTES:
                return QVariant::fromValue(note_track->notes());
            case TRACK_NUMBER:
                return QVariant::fromValue(note_track->id());
            case TRACK_TYPE:
                return QVariant::fromValue(1);
            default:
                return QVariant();
        }
    } else if (auto *sample_track = dynamic_cast<SampleTrack *>(track)) {
        switch (role) {
            case TRACK_SAMPLES:
                return QVariant::fromValue(sample_track->samples());
            case TRACK_NUMBER:
                return QVariant::fromValue(sample_track->id());
            case TRACK_TYPE:
                return QVariant::fromValue(0);
            default:
                return QVariant();
        }
    }
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
