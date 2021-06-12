#pragma once

class PlaylistSongsController
{
public:
	static void handleAddSong(int);

	static void handleDeleteSong(int);

	PlaylistSongsController() : songId(-1), playlistId(-1) {};
	PlaylistSongsController(int songId, int playlistId) : songId(songId), playlistId(playlistId) {};

	void attachSongToPlaylist() const;
	static void addSongToPlaylist(int);

protected:
	int songId;
	int playlistId;

	void promptSongId();
	void detachSongFromPlaylist() const;
};