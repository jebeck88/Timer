#include <QApplication>
#include <QDate>

#include "Application.h"
#include "Dialog.h"

// const QString startDate = "2005-04-14";
const QString startDate = "1988-04-30";

// const QString endDate = "2023-03-14";
const QString endDate = "2031-04-30";

// Set start and end datetimes
const QDateTime Application::sBeginDateTime(QDateTime::fromString(startDate, "yyyy-MM-dd"));
const QDateTime Application::sEndDateTime(QDateTime::fromString(endDate, "yyyy-MM-dd"));

Application::Application(int argc, char *argv[]) : QApplication(argc, argv),
												   mDialog(nullptr)
{
	mDialog = new Dialog();
}

Application::~Application()
{
	if (mDialog)
	{
		delete mDialog;
	}
}

int Application::secsToEnd(void) const
{
	// Add a 1 to the elapsed seconds, in place of having to get mS and round
	return QDateTime::currentDateTime().secsTo(sEndDateTime) + 1;
}

int Application::secsFromBegin(void) const
{
	return sBeginDateTime.secsTo(QDateTime::currentDateTime());
}

int Application::secsFromBeginToEnd(void) const
{
	return sBeginDateTime.secsTo(sEndDateTime);
}

bool Application::isAfterBegin(void) const
{
	return sBeginDateTime < QDateTime::currentDateTime();
}

bool Application::isBeforeEnd(void) const
{
	return QDateTime::currentDateTime() < sEndDateTime;
}

Application *Application::instance()
{
	return dynamic_cast<Application *>(QApplication::instance());
}

Dialog *Application::getWindow(void) const
{
	return mDialog;
}
