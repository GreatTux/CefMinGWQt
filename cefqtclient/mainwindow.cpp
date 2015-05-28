#include "mainwindow.h"

#include <QVBoxLayout>
#include <QShowEvent>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	m_clientHandler(new ClientHandler(this)),
	m_webviewWidget(nullptr)
{
	ui.setupUi(this);

	m_webviewWidget = new QWidget(this);
	m_webviewWidget->setAttribute(Qt::WA_NativeWindow);
	m_webviewWidget->setAttribute(Qt::WA_DontCreateNativeAncestors);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->setMargin(0);
	layout->addWidget(m_webviewWidget);

	ui.mainWidget->setLayout(layout);

	QObject::connect(ui.lineEdit, &QLineEdit::returnPressed, this, &MainWindow::handleReturnPress);

	m_webviewWidget->installEventFilter(this);
}

MainWindow::~MainWindow()
{
	if(!m_clientHandler->IsClosing())
	{
		CefRefPtr<CefBrowser> browser = m_clientHandler->GetBrowser();
		if(browser.get())
		{
			browser->GetHost()->CloseBrowser(false);
		}
	}
}

void MainWindow::updateLineEditUrl(const QString& text)
{
	ui.lineEdit->setText(text);
}

void MainWindow::initBrowser()
{
	RECT rect = {0, 0, m_webviewWidget->width(), m_webviewWidget->height()};

	CefWindowInfo info;
	info.SetAsChild((HWND)m_webviewWidget->winId(), rect);

	CefBrowserSettings settings;

	QString url = "http://www.google.com";
	CefBrowserHost::CreateBrowser(info,
											m_clientHandler,
											CefString(url.toStdWString()),
											settings,
											0);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
	assert(m_clientHandler.get());

	if(m_clientHandler->GetBrowser())
	{
		CefWindowHandle hwnd = m_clientHandler->GetBrowser()->GetHost()->GetWindowHandle();
		if(hwnd)
		{
			HDWP hdwp = BeginDeferWindowPos(1);
			hdwp = DeferWindowPos(hdwp, hwnd, NULL, 0, 0, m_webviewWidget->width(), m_webviewWidget->height(), SWP_NOZORDER);
			EndDeferWindowPos(hdwp);
		}
	}

	QMainWindow::resizeEvent(e);
}

void MainWindow::showEvent(QShowEvent *e)
{
	assert(m_clientHandler.get());

	initBrowser();

	QMainWindow::showEvent(e);
}

void MainWindow::handleReturnPress()
{
	assert(m_webviewWidget);

	const QString url = ui.lineEdit->text();
	m_clientHandler->GetBrowser()->GetMainFrame()->LoadURL(CefString(url.toStdString()));
}

void MainWindow::on_backwardButton_clicked()
{
	m_clientHandler->GetBrowser()->GoBack();
}

void MainWindow::on_forwardButton_clicked()
{
	m_clientHandler->GetBrowser()->GoForward();
}

void MainWindow::on_reloadButton_clicked()
{
	m_clientHandler->GetBrowser()->Reload();
}
