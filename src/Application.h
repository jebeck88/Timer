#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QDateTime>

class Dialog;

/// The Application class
class Application : public QApplication
{
	Q_OBJECT

public:
	/// The begin date-time
	static const QDateTime sBeginDateTime;

	/// The end date-time
	static const QDateTime sEndDateTime;

public:
	/// Constructor
	/// @param argc the number of command line arguments
	/// @param argv the command line arguments
	Application(int argc, char *argv[]);

	/// Destructor
	virtual ~Application();

	/// Return the singleton instance
	/// @return the instance
	static Application *instance(void);

	/// Return a handle to the window
	/// @return the window
	Dialog *getWindow(void) const;

	/// Return the number of seconds remaining from now until end
	/// @return secs to end
	int secsToEnd(void) const;

	/// Return the number of seconds elapsed from begin until now
	/// @return secs from begin
	int secsFromBegin(void) const;

	/// Return the number of seconds from begin to end
	/// @return secs from begin to end
	int secsFromBeginToEnd(void) const;

	/// Return true if it's after the begin date
	// @return true if it's after the begin date
	bool isAfterBegin(void) const;

	/// Return true if it's before the end date
	/// @return true if it's before the end date
	bool isBeforeEnd(void) const;

private:
	/// No copies
	Application(const Application &);
	Application &operator=(const Application &);

private:
	/// The main dialog (non-parented)
	Dialog *mDialog;
};

#endif // APPLICATION_H