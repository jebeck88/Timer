#include <QDialog>
#include <QGuiApplication>
#include <QHideEvent>
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>

#include "Application.h"
#include "Dialog.h"

int Dialog::sSecsPerMinute(60);
int Dialog::sSecsPerHour(60 * sSecsPerMinute);
int Dialog::sSecsPerDay(24 * sSecsPerHour);

Dialog::Dialog(QWidget *parent) : QDialog(parent, Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnBottomHint),
								  mTimer(nullptr),
								  mTogoLabel(nullptr),
								  mElapsedLabel(nullptr)
{
	// make the labels
	mTogoLabel = new QLabel(this);
	mTogoLabel->setText(
		makeTimestamp(
			Application::instance()->secsToEnd(),
			Application::instance()->secsFromBeginToEnd()));

	mElapsedLabel = new QLabel(this);
	mElapsedLabel->setText(
		makeTimestamp(
			Application::instance()->secsFromBegin(),
			Application::instance()->secsFromBeginToEnd()));

	// layout
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(mElapsedLabel);
	layout->addWidget(mTogoLabel);
	setLayout(layout);

	// Set the style sheet
	setStyleSheet(styleSheet());

	// Force an initial update
	update();

	// timer
	mTimer = new QTimer(this);
	mTimer->setInterval(500);
	connect(mTimer, SIGNAL(timeout(void)), this, SLOT(update(void)));
}

Dialog::~Dialog()
{
}

void Dialog::update(void)
{
	const bool bIsAfterBegin(Application::instance()->isAfterBegin());
	const bool bIsBeforeEnd(Application::instance()->isBeforeEnd());
	const int secsTotal(Application::instance()->secsFromBeginToEnd());

	int secsElapsed(0);
	int secsTogo(secsTotal);

	if (!bIsAfterBegin)
	{
		secsElapsed = 0;
		secsTogo = secsTotal;
	}
	else if (bIsAfterBegin && bIsBeforeEnd)
	{
		secsElapsed = Application::instance()->secsFromBegin();
		secsTogo = Application::instance()->secsToEnd();
	}
	else
	{
		secsElapsed = secsTotal;
		secsTogo = 0;
	}

	mElapsedLabel->setText(
		makeTimestamp(secsElapsed, secsTotal));

	mTogoLabel->setText(
		makeTimestamp(secsTogo, secsTotal));
}

QString Dialog::makeTimestamp(int nSecs, int nTotalSecs)
{
	// Calc percent
	double percent = 100 * (static_cast<double>(nSecs) / static_cast<double>(nTotalSecs));

	// Calc days, hours, mins & secs
	int nDays(0);
	if (nSecs > 0)
	{
		nDays = nSecs / sSecsPerDay;
		nSecs -= nDays * sSecsPerDay;
	}

	int nHours(0);
	if (nSecs > 0)
	{
		nHours = nSecs / sSecsPerHour;
		nSecs -= nHours * sSecsPerHour;
	}

	int nMins(0);
	if (nSecs > 0)
	{
		nMins = nSecs / sSecsPerMinute;
		nSecs -= nMins * sSecsPerMinute;
	}

	// Update the UI
	return QString("%1 : %2 : %3 : %4 (%5%)")
		.arg(nDays, 4, 10, QChar('0'))
		.arg(nHours, 2, 10, QChar('0'))
		.arg(nMins, 2, 10, QChar('0'))
		.arg(nSecs, 2, 10, QChar('0'))
		.arg(percent, 4, 'F', 2, QChar('0'));
}

void Dialog::showEvent(QShowEvent *evt)
{
	// Start the timer
	mTimer->start();

	// Center on the screen
	QRect frect = frameGeometry();
	frect.moveCenter(QGuiApplication::primaryScreen()->availableGeometry().center());
	move(frect.topLeft());

	// Handle base class show
	QWidget::showEvent(evt);
}

void Dialog::hideEvent(QHideEvent * /*evt*/)
{
	mTimer->stop();
}

void Dialog::mouseDoubleClickEvent(QMouseEvent * /*evt*/)
{
	QApplication::instance()->exit(0);
}

QString Dialog::styleSheet() const
{
	// Pitt Blue
	const QColor textColor = QColor("#192857");
	// Pitt Gold
	const QColor backgroundColor = QColor("#cdb87d");

	static QString result = QString(
								"Dialog \
		{ \
			background-color: %1; \
			border: 3px solid white; \
		} \
		Dialog>QLabel \
		{ \
			background-color: transparent; \
			font-family: helvetica; \
			font-size: 14px; \
			font-weight: bold; \
			color: %2; \
		}")
								.arg(backgroundColor.name())
								.arg(textColor.name());

	return result;
}