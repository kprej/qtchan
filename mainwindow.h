#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "settings.h"
#include "treeitem.h"
#include "treemodel.h"
#include "threadform.h"
#include "netcontroller.h"
#include <QUrl>
#include <QMap>
#include <QItemSelectionModel>
#include <QMainWindow>

struct Tab{
	enum TabType {Board,Thread} type;
	void *TabPointer;
	TreeItem *tn;
	QString query;
	QString display;
};

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
	Q_OBJECT
protected:
	bool eventFilter(QObject *obj, QEvent *ev);

public:
	explicit MainWindow(QWidget *parent = 0);
	TreeModel *model = new TreeModel(this);
	QItemSelectionModel *selectionModel;
	QMap<QWidget*,Tab> tabs;
	~MainWindow();

	void addTab(TreeItem *child, TreeItem *parent = Q_NULLPTR, bool select = false);
	void deleteSelected();
	QObject *currentWidget();
	Settings settingsView;

private slots:
	void on_pushButton_clicked();
	void on_treeView_clicked(QModelIndex index);
	void onSelectionChanged();
	void on_navBar_returnPressed();

public slots:
	void focusTree();
	void focusBar();
	TreeItem *loadFromSearch(QString query, QString display, TreeItem *childOf, bool select = false);
	TreeItem *onNewThread(QWidget *parent, QString board, QString thread, QString display, TreeItem *childOf);
	void saveSession();
	void loadSession();
	void prevTab();
	void nextTab();
	void prevParent();
	void nextParent();
	void toggleAutoUpdate();
	void toggleAutoExpand();
	void openExplorer();
	void updateSettings(QString setting, QVariant value);
	void updateSeen(int formsUnseen);

private:
	Ui::MainWindow *ui;
	void setShortcuts();
	void removeTabs(TreeItem *tn);
	void saveSessionToFile(QString fileName);
	void loadSessionFromFile(QString sessionFile);
	QMetaObject::Connection selectionConnection;

signals:
	void requestCatalog(QString);
	void setAutoUpdate(bool autoUpdate);
	void setAutoExpand(bool autoExpand);
	void setUse4chanPass(bool use4chanPass);
	void setFontSize(int fontSize);
	void setImageSize(int imageSize);
	void reloadFilters();
};

extern MainWindow *mw;

enum FilterType{id,comment,trip};
enum BoardName{b,g,diy,h,pol,d};


#endif // MAINWINDOW_H
