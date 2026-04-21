#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QTimer>


/// Dialog for the timer app
class Dialog : public QDialog
{
    Q_OBJECT

public:
	/// The number of seconds in a day
	static int sSecsPerDay;

	/// The number of seconds in an hour
	static int sSecsPerHour;

	/// The number of seconds in a minute
	static int sSecsPerMinute;

public:
	/// The constructor
    Dialog( QWidget *parent = 0 );

	/// The destructor
	virtual ~Dialog();

	/// Return the stylesheet
	QString styleSheet() const;

public slots:
	/// Update the UI
	void update( void );

protected:
	virtual void hideEvent( QHideEvent* evt );
	virtual void showEvent( QShowEvent* evt );
	virtual void mouseDoubleClickEvent( QMouseEvent* evt );

private:
	/// Make a time stamp
    static QString makeTimestamp( int nSecs, int nTotalSecs );


private:
	/// Timer
	QTimer* mTimer;

	/// The to-go label
	QLabel* mTogoLabel;

	/// The elapsed label
	QLabel* mElapsedLabel;

};

#endif  // DIALOG_H
