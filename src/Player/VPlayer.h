#pragma once

#include "APlayer.h"
#include <QActionGroup>

extern "C"
{
#include <vlc/vlc.h>
}

class VPlayer :public APlayer
{
public:
	enum Event
	{
		Init,
		Wait,
		Free,
		Fail
	};

	explicit VPlayer(QObject *parent = 0);
	~VPlayer();
	static QMutex time;
	QList<QAction *> getTracks(int type);

private:
	int		state;
	QActionGroup *tracks[3];
	libvlc_instance_t *vlc;
	libvlc_media_player_t *mp;

	void	init();
	void	wait();
	void	free();

public slots:
	void	play();
	void	stop(bool manually = true);
	int 	getState(){ return state; }

	void	setTime(qint64 _time);
	qint64	getTime();

	void	setMedia(QString _file, bool manually = true);
	QString getMedia();

	qint64	getDuration();
	void	addSubtitle(QString _file);

	void	setVolume(int _volume);
	int 	getVolume();

	void    setRate(double _rate);
	double  getRate();

	void	event(int type);
};
