#include "BrowserTab.h"
#include "BrowserWindow.h"
#include "../Manitou.h"
#include <QtCore/QFile>
#include <QtCore/QPropertyAnimation>
#include <QtGui/QDesktopServices>
#include <QtGui/QDesktopWidget>
#include <QtGui/QLabel>
#include <QtGui/QToolTip>
#include <QtGui/QVBoxLayout>
#include <QtWebKit/QWebElement>
#include <QtWebKit/QWebFrame>
#include <QtWebKit/QWebSettings>

#include "../model/inspector/WebFrameInspector.h"

#include <QtDebug>

BrowserTab::BrowserTab(unsigned int id, QWidget *parent) :
    QWidget(parent), id(id), parentWindow(0)
{
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout->setSpacing(0);


    graphicsScene = new QGraphicsScene(this);
    graphicsScene->setBackgroundBrush(Qt::black);
    graphicsView = new GraphicsView(this);

    webView = new GraphicsWebView(0);
    graphicsScene->addItem(webView);
    graphicsView->setScene(graphicsScene);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    navigationToolBar = new NavigationToolBar(webView, this);


    verticalLayout->addWidget(navigationToolBar);
    verticalLayout->addWidget(graphicsView);

    this->setLayout(verticalLayout);

    connect(webView, SIGNAL(titleChanged(QString)), SLOT(onTitleChanged(QString)));
    connect(webView, SIGNAL(loadStarted()), SLOT(onLoadStarted()));
    connect(webView, SIGNAL(loadProgress(int)), SLOT(onLoadProgress(int)));
    connect(webView, SIGNAL(loadFinished(bool)), SLOT(onLoadFinished()));
}

BrowserTab::~BrowserTab()
{
    delete webView;
}

void BrowserTab::setParentWindow(BrowserWindow *parentWindow)
{
    this->parentWindow = parentWindow;
    connect(webView->page(), SIGNAL(linkHovered(QString,QString,QString)), this->parentWindow->getStatusBar(), SLOT(showMessage(QString)));
    connect(webView, SIGNAL(statusBarMessage(QString)), this->parentWindow->getStatusBar(), SLOT(showMessage(QString)));
}

void BrowserTab::openUrl(const QUrl &url)
{
    webView->load(url);
}

void BrowserTab::close()
{
    emit tabClosed(id);
}

void BrowserTab::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);

    QSize size = graphicsView->size();
    QMargins margins = graphicsView->contentsMargins();
    size.setWidth(size.width() - margins.left() - margins.right());
    size.setHeight(size.height() - margins.top() - margins.bottom());

    graphicsScene->setSceneRect(0.0, 0.0, size.width(), size.height());
    webView->resize(size);
}

void BrowserTab::onTitleChanged(QString title)
{
    if (parentWindow) {
        QTabWidget *tabWidget = parentWindow->getTabWidget();
        int index = tabWidget->indexOf(this);
        if (index != -1) {
            // TODO: udelat z maximalni delky konstantu
            if (title.length() > 24)
                title = title.remove(24, title.length() - 24) + "...";
            tabWidget->setTabText(index, title);
            tabWidget->setTabToolTip(index, title);
        }
    }
}

void BrowserTab::onLoadStarted()
{
    graphicsView->setFocus();
//    progressBar->setEnabled(true);
//    progressBar->setShown(true);
//    progressBar->setValue(0);
}

void BrowserTab::onLoadProgress(int progress)
{
    Q_UNUSED(progress);
//    progressBar->setValue(progress);
}

void BrowserTab::onLoadFinished()
{
    webView->setFocus();
    WebFrameInspector inspector;
    inspector.setWebFrame(webView->page()->currentFrame());
    //webView->setFocus();
//    progressBar->setValue(100);
//    progressBar->setEnabled(false);
//    progressBar->setShown(false);

    History *history = Manitou::instance()->getHistory();
    QAbstractItemModel *model = history->getItemModel();
    if (model) {
        model->insertRow(0);
        model->setData(model->index(0, 1), webView->url().toString());
        model->setData(model->index(0, 2), webView->title());
        model->setData(model->index(0, 3), QDateTime::currentDateTime().toUTC().toString(Qt::ISODate));
        model->submit();
    }
}

void BrowserTab::showInspector()
{
    webView->triggerPageAction(QWebPage::InspectElement);
}

void BrowserTab::toolbar()
{
//    if (navigationToolBar->isHidden()) {
//        ui->actionToolbar->setText(tr("Hide Toolbar"));
//        navigationToolBar->show();
//    }
//    else {
//        ui->actionToolbar->setText(tr("Show Toolbar"));
//        navigationToolBar->hide();
//    }
}

void BrowserTab::openLocation()
{
    navigationToolBar->location();
}

void BrowserTab::search()
{
    navigationToolBar->search();
}

void BrowserTab::reload()
{
    webView->reload();
}

void BrowserTab::stop()
{
    webView->stop();
}

void BrowserTab::highlightLinks()
{
    QWebFrame *frame = webView->page()->mainFrame();
    QWebElementCollection collection = frame->findAllElements("a");

    foreach (QWebElement element, collection) {
        QLabel *label = new QLabel(this);
        label->setText("<b>" + element.attribute("href") + "</b>");
        QPalette palette = QToolTip::palette();
        QColor color(Qt::yellow);
        color = color.lighter(150);
        color.setAlpha(175);
        palette.setColor(QPalette::Window, color);
        label->setAutoFillBackground(true);
        label->setFrameStyle(QLabel::StyledPanel | QLabel::Sunken);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //QPoint position = element.geometry().center() - frame->scrollPosition();

        label->setGeometry(element.geometry());

        label->setPalette(palette);
        //label->move(position);
        label->show();
        //element.encloseWith("<span style=\"background-color: yellow;\"></span>");
    }

    /*QString style("border:1px solid black; color: black; background-color: yellow; position:absolute;");
    char c = '0';

    foreach (QWebElement element, collection) {
        element.appendOutside(QString("<div style=\"" + style + " left:" + QString::number(element.geometry().right()) + "px; top:" + QString::number(element.geometry().top()) + "px;\">") + (c++) + QString("</div>"));
    }*/
}

void BrowserTab::highlightParagraphs()
{
    QWebFrame *frame = webView->page()->mainFrame();
    QWebElementCollection collection = frame->findAllElements("p");

    foreach (QWebElement element, collection) {
        QLabel *label = new QLabel(this);
        label->setText("<b>P</b>");
        QPalette palette = QToolTip::palette();
        QColor color(Qt::yellow);
        color = color.lighter(150);
        color.setAlpha(175);
        palette.setColor(QPalette::Window, color);
        label->setAutoFillBackground(true);
        label->setFrameStyle(QLabel::Box | QLabel::Plain);
        QPoint position = element.geometry().center() - frame->scrollPosition();

        label->setPalette(palette);
        label->move(position);
        label->show();
        //element.encloseWith("<span style=\"background-color: yellow;\"></span>");
    }
}

void BrowserTab::viewSource()
{
    QWebPage *page = webView->page();
    if (page) {
        QWebFrame *frame = page->mainFrame();
        if (frame) {
            QString html = frame->toHtml();
            QString directory = QDesktopServices::storageLocation(QDesktopServices::TempLocation);
            QUrl url = QUrl::fromLocalFile(directory + "/source.txt");
            QFile file(url.toLocalFile());
            if (file.open(QIODevice::WriteOnly)) {
                file.write(html.toUtf8());
                file.close();
                QDesktopServices::openUrl(url);
            }

        }
    }
}

