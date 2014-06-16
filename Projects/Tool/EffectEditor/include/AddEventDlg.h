#ifndef __ADDOBJECT_TABDIALOG_h__
#define __ADDOBJECT_TABDIALOG_h__
#include <QDialog>

class QTreeWidget;
class QTreeWidgetItem;

class AddEventDlg :public QDialog
{
	Q_OBJECT
public:
	AddEventDlg(QWidget *parent = 0, Qt::WFlags flag = 0);
	~AddEventDlg(void);

public:
	void createWidget();
	void init();

	void setEventTime(float timing);
private slots:
	void	itemClicked(QTreeWidgetItem *, int);
	void	okClicked();
	void	cancelClicked();

private:
	QTreeWidget* mEventTreeWidget;

	QPushButton *mOKBtn;
	QPushButton *mCancleBtn;

	std::string	 mCurrentEventName;

	float		 mEventTiming;
};

#endif