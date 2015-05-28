#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "clienthandler.h"

class CEFWebView;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void updateLineEditUrl(const QString& text);

private:
	void initBrowser();

protected:
	void resizeEvent(QResizeEvent *) override;
	void showEvent(QShowEvent *) override;

private slots:
	void handleReturnPress();

	void on_backwardButton_clicked();
	void on_forwardButton_clicked();
	void on_reloadButton_clicked();

private:
	Ui::MainWindow ui;

	CefRefPtr<ClientHandler>	m_clientHandler;
	QWidget*							m_webviewWidget;
};

#endif // MAINWINDOW_H
