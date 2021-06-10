#pragma once

class PlaylistSongsController
{
public:
	static void handleAddSong(int);

	static void handleDeleteSong(int);

	PlaylistSongsController() : songId(-1), playlistId(-1) {};

protected:
	int songId;
	int playlistId;

	void promptSongId();
	void attachSongToPlaylist() const;
	void detachSongFromPlaylist() const;
};