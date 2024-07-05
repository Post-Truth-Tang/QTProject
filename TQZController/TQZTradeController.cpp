#include "TQZTradeController.h"

#include <QDebug>


TQZTradeController::TQZTradeController(QWidget *parent):
    IController(parent),
    m_closeButton(nullptr),
    m_sendOrderButton(nullptr)
{
    double askBidLableX = 40;
    double askBidLableY = 40;
    double askBidLableWidth = 40;
    double labelHeight = 25;
    double edge = 10;

    // init ask bid labels.
    this->initAskBidLabels(askBidLableX, askBidLableY, askBidLableWidth, labelHeight);

    // init ask bid value labels.
    this->initAskBidValueLabels(askBidLableX + askBidLableWidth, askBidLableY, askBidLableWidth * 2, labelHeight);

    // init send order ui.
    this->initSendOrderUI(askBidLableX + askBidLableWidth + askBidLableWidth * 4 + edge * 2, askBidLableY + edge * 2, askBidLableWidth, labelHeight, edge);

    // init send order button.
    double emptyArea_X_Start = askBidLableX + askBidLableWidth + edge * 2 + askBidLableWidth * 4;
    double emptyArea_X_end = m_exchangeComboBox->x() + m_exchangeComboBox->width();
    double emptyArea_Y_Start = m_orderTypeComboBox->y() + m_orderTypeComboBox->height() + edge;
    double emptyArea_Y_end = askBidLableY + labelHeight * edge;

    this->initSendOrderButton(emptyArea_X_Start, emptyArea_X_end, emptyArea_Y_Start, emptyArea_Y_end);

    // init self
    this->initSelf(askBidLableX, askBidLableY, emptyArea_X_end, labelHeight);
}


void TQZTradeController::initSendOrderButton(double emptyArea_X_Start, double emptyArea_X_end, double emptyArea_Y_Start, double emptyArea_Y_end) {

    this->sendOrderButton()->setFixedSize((emptyArea_X_end - emptyArea_X_Start) * 0.8, (emptyArea_Y_end - emptyArea_Y_Start) * 0.4);
    this->sendOrderButton()->move((emptyArea_X_Start + emptyArea_X_end - this->sendOrderButton()->width()) * 0.5, (emptyArea_Y_Start + emptyArea_Y_end - this->sendOrderButton()->height()) * 0.5);

    // TODO: to be continue.
    // #. add connect method of send order.
    connect(this->sendOrderButton(), &TQZButton::clicked, this, [=](){
        // for test. (create a order obj in real time)
        QString orderInfo = QString("trade controller send order.");

        emit this->sendOrder(orderInfo);
    });

}

void TQZTradeController::initSendOrderUI(double x, double y, double askBidLableWidth, double labelHeight, double edge) {

    m_instrumentTextEdit = new QLineEdit(this);
    m_instrumentTextEdit->move(x, y);
    m_instrumentTextEdit->setFixedSize(askBidLableWidth * 3, labelHeight);
    m_instrumentTextEdit->setPlaceholderText("instrument");
    m_instrumentTextEdit->connect(m_instrumentTextEdit, &QLineEdit::returnPressed, this, [=](){
        qDebug() << "m_instrumentTextEdit content: " << m_instrumentTextEdit->text() + "." + m_exchangeComboBox->currentText();
    });


    m_exchangeComboBox = new QComboBox(this);
    m_exchangeComboBox->setStyleSheet("background-color: white; selection-background-color: red;");
    m_exchangeComboBox->move(m_instrumentTextEdit->x() + m_instrumentTextEdit->width() + edge, m_instrumentTextEdit->y());
    m_exchangeComboBox->setFixedSize(m_instrumentTextEdit->width() * 1.2, m_instrumentTextEdit->height());
    m_exchangeComboBox->addItem("- exchange -");
    m_exchangeComboBox->addItem("SHFE");
    m_exchangeComboBox->addItem("DCE");
    m_exchangeComboBox->addItem("CZCE");

    m_directComboBox = new QComboBox(this);
    m_directComboBox->setStyleSheet("background-color: white; selection-background-color: red;");
    m_directComboBox->move(m_instrumentTextEdit->x(), m_instrumentTextEdit->y() + m_instrumentTextEdit->height() + edge);
    m_directComboBox->setFixedSize(m_instrumentTextEdit->width(), m_instrumentTextEdit->height());
    m_directComboBox->addItem("- direct -");
    m_directComboBox->addItem("LONG");
    m_directComboBox->addItem("SHORT");

    m_openCloseComboBox = new QComboBox(this);
    m_openCloseComboBox->setStyleSheet("background-color: white; selection-background-color: red;");
    m_openCloseComboBox->move(m_directComboBox->x() + m_directComboBox->width() + edge, m_directComboBox->y());
    m_openCloseComboBox->setFixedSize(m_exchangeComboBox->width(), m_directComboBox->height());
    m_openCloseComboBox->addItem("- open | close -");
    m_openCloseComboBox->addItem("open");
    m_openCloseComboBox->addItem("close");
    m_openCloseComboBox->addItem("closeToday");

    m_orderTypeComboBox = new QComboBox(this);
    m_orderTypeComboBox->setStyleSheet("background-color: white; selection-background-color: red;");
    m_orderTypeComboBox->move(m_directComboBox->x(), m_directComboBox->y() + m_directComboBox->height() + edge);
    m_orderTypeComboBox->setFixedSize(m_directComboBox->width(), m_directComboBox->height());
    m_orderTypeComboBox->addItem("- order type -");
    m_orderTypeComboBox->addItem("market type");
    m_orderTypeComboBox->addItem("limit type");


    m_priceTextEdit = new QLineEdit(this);
    m_priceTextEdit->move(m_orderTypeComboBox->x() + m_orderTypeComboBox->width() + edge, m_orderTypeComboBox->y());
    m_priceTextEdit->setFixedSize(m_openCloseComboBox->width() * 0.5, labelHeight);
    m_priceTextEdit->setPlaceholderText("price");


    m_sizeTextEdit = new QLineEdit(this);
    m_sizeTextEdit->move(m_priceTextEdit->x() + m_priceTextEdit->width() + edge, m_orderTypeComboBox->y());
    m_sizeTextEdit->setFixedSize(m_priceTextEdit->width() - edge, m_priceTextEdit->height());
    m_sizeTextEdit->setPlaceholderText("size");
}


void TQZTradeController::initSelf(double askBidLableX, double askBidLableY, double emptyArea_X_end, double labelHeight) {
    QScreen *screen = qApp->primaryScreen();

    double width = emptyArea_X_end + askBidLableX; // <- width & height of trade controller is stable.
    double height = askBidLableY * 2 + labelHeight * 10;

    this->resize(width, height);
    this->move((screen->size().width() - this->width()) * 0.5, (screen->size().height() - this->height()) * 0.5);

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);

    this->closeButton();
}

void TQZTradeController::initAskBidLabels(double x, double y, double width, double labelHeight) {
    QFont font("宋体", 14, QFont::Thin);

    QLabel *ask5TitleLabel = new QLabel("ask5", this);
    ask5TitleLabel->move(x, y);
    ask5TitleLabel->setFixedSize(width, labelHeight);
    ask5TitleLabel->setStyleSheet("color: white; font-size: 15px;");
    ask5TitleLabel->setFont(font);
    ask5TitleLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    QLabel *ask4TitleLabel = new QLabel("ask4", this);
    ask4TitleLabel->move(ask5TitleLabel->x(), ask5TitleLabel->y() + ask5TitleLabel->height());
    ask4TitleLabel->setFixedSize(ask5TitleLabel->width(), ask5TitleLabel->height());
    ask4TitleLabel->setStyleSheet("color: white; font-size: 15px;");
    ask4TitleLabel->setFont(font);
    ask4TitleLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    QLabel *ask3TitleLabel = new QLabel("ask3", this);
    ask3TitleLabel->move(ask5TitleLabel->x(), ask4TitleLabel->y() + ask4TitleLabel->height());
    ask3TitleLabel->setFixedSize(ask5TitleLabel->width(), ask5TitleLabel->height());
    ask3TitleLabel->setStyleSheet("color: white; font-size: 15px;");
    ask3TitleLabel->setFont(font);
    ask3TitleLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    QLabel *ask2TitleLabel = new QLabel("ask2", this);
    ask2TitleLabel->move(ask5TitleLabel->x(), ask3TitleLabel->y() + ask3TitleLabel->height());
    ask2TitleLabel->setFixedSize(ask5TitleLabel->width(), ask5TitleLabel->height());
    ask2TitleLabel->setStyleSheet("color: white; font-size: 15px;");
    ask2TitleLabel->setFont(font);
    ask2TitleLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    // ask1Label need big font size.
    QLabel *ask1TitleLabel = new QLabel("ask1", this);
    ask1TitleLabel->move(ask5TitleLabel->x(), ask2TitleLabel->y() + ask2TitleLabel->height());
    ask1TitleLabel->setFixedSize(ask5TitleLabel->width(), ask5TitleLabel->height());
    ask1TitleLabel->setStyleSheet("color: white; font-size: 15px;"); // 28px
    ask1TitleLabel->setFont(font);
    ask1TitleLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);


    // -----------------------------------------


    // bid1Label need big font size.
    QLabel *bid1TitleLabel = new QLabel("bid1", this);
    bid1TitleLabel->move(ask5TitleLabel->x(), ask1TitleLabel->y() + ask1TitleLabel->height());
    bid1TitleLabel->setFixedSize(ask5TitleLabel->width(), ask5TitleLabel->height());
    bid1TitleLabel->setStyleSheet("color: white; font-size: 15px;");
    bid1TitleLabel->setFont(font);
    bid1TitleLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    QLabel *bid2TitleLabel = new QLabel("bid2", this);
    bid2TitleLabel->move(ask5TitleLabel->x(), bid1TitleLabel->y() + bid1TitleLabel->height());
    bid2TitleLabel->setFixedSize(ask5TitleLabel->width(), ask5TitleLabel->height());
    bid2TitleLabel->setStyleSheet("color: white; font-size: 15px;");
    bid2TitleLabel->setFont(font);
    bid2TitleLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    QLabel *bid3TitleLabel = new QLabel("bid3", this);
    bid3TitleLabel->move(ask5TitleLabel->x(), bid2TitleLabel->y() + bid2TitleLabel->height());
    bid3TitleLabel->setFixedSize(ask5TitleLabel->width(), ask5TitleLabel->height());
    bid3TitleLabel->setStyleSheet("color: white; font-size: 15px;");
    bid3TitleLabel->setFont(font);
    bid3TitleLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    QLabel *bid4TitleLabel = new QLabel("bid4", this);
    bid4TitleLabel->move(ask5TitleLabel->x(), bid3TitleLabel->y() + bid3TitleLabel->height());
    bid4TitleLabel->setFixedSize(ask5TitleLabel->width(), ask5TitleLabel->height());
    bid4TitleLabel->setStyleSheet("color: white; font-size: 15px;");
    bid4TitleLabel->setFont(font);
    bid4TitleLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    QLabel *bid5TitleLabel = new QLabel("bid5", this);
    bid5TitleLabel->move(ask5TitleLabel->x(), bid4TitleLabel->y() + bid4TitleLabel->height());
    bid5TitleLabel->setFixedSize(ask5TitleLabel->width(), ask5TitleLabel->height());
    bid5TitleLabel->setStyleSheet("color: white; font-size: 15px;");
    bid5TitleLabel->setFont(font);
    bid5TitleLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
}

void TQZTradeController::initAskBidValueLabels(double x, double y, double width, double labelHeight) {
    QFont font("宋体", 14, QFont::Thin);

    // ask 5.
    m_ask5PriceLabel = new QLabel("900000", this);
    m_ask5PriceLabel->move(x, y);
    m_ask5PriceLabel->setFixedSize(width, labelHeight);
    m_ask5PriceLabel->setStyleSheet("color: green; font-size: 15px;");
    m_ask5PriceLabel->setFont(font);
    m_ask5PriceLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    m_ask5SizeLabel = new QLabel("10", this);
    m_ask5SizeLabel->move(x + width + 10, y);
    m_ask5SizeLabel->setFixedSize(width, labelHeight);
    m_ask5SizeLabel->setStyleSheet("color: yellow; font-size: 15px;");
    m_ask5SizeLabel->setFont(font);
    m_ask5SizeLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    // ask 4.
    m_ask4PriceLabel = new QLabel("800000", this);
    m_ask4PriceLabel->move(m_ask5PriceLabel->x(), m_ask5PriceLabel->y() + m_ask5PriceLabel->height());
    m_ask4PriceLabel->setFixedSize(m_ask5PriceLabel->width(), m_ask5PriceLabel->height());
    m_ask4PriceLabel->setStyleSheet("color: green; font-size: 15px;");
    m_ask4PriceLabel->setFont(font);
    m_ask4PriceLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    m_ask4SizeLabel = new QLabel("11", this);
    m_ask4SizeLabel->move(m_ask5SizeLabel->x(), m_ask5SizeLabel->y() + m_ask5SizeLabel->height());
    m_ask4SizeLabel->setFixedSize(m_ask5SizeLabel->width(), m_ask5SizeLabel->height());
    m_ask4SizeLabel->setStyleSheet("color: yellow; font-size: 15px;");
    m_ask4SizeLabel->setFont(font);
    m_ask4SizeLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);


    // ask 3.
    m_ask3PriceLabel = new QLabel("700000", this);
    m_ask3PriceLabel->move(m_ask5PriceLabel->x(), m_ask4PriceLabel->y() + m_ask4PriceLabel->height());
    m_ask3PriceLabel->setFixedSize(m_ask5PriceLabel->width(), m_ask5PriceLabel->height());
    m_ask3PriceLabel->setStyleSheet("color: green; font-size: 15px;");
    m_ask3PriceLabel->setFont(font);
    m_ask3PriceLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    m_ask3SizeLabel = new QLabel("12", this);
    m_ask3SizeLabel->move(m_ask5SizeLabel->x(), m_ask4SizeLabel->y() + m_ask4SizeLabel->height());
    m_ask3SizeLabel->setFixedSize(m_ask5SizeLabel->width(), m_ask5SizeLabel->height());
    m_ask3SizeLabel->setStyleSheet("color: yellow; font-size: 15px;");
    m_ask3SizeLabel->setFont(font);
    m_ask3SizeLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);


    // ask 2
    m_ask2PriceLabel = new QLabel("600000", this);
    m_ask2PriceLabel->move(m_ask5PriceLabel->x(), m_ask3PriceLabel->y() + m_ask3PriceLabel->height());
    m_ask2PriceLabel->setFixedSize(m_ask5PriceLabel->width(), m_ask5PriceLabel->height());
    m_ask2PriceLabel->setStyleSheet("color: green; font-size: 15px;");
    m_ask2PriceLabel->setFont(font);
    m_ask2PriceLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    m_ask2SizeLabel = new QLabel("13", this);
    m_ask2SizeLabel->move(m_ask5SizeLabel->x(), m_ask3SizeLabel->y() + m_ask3SizeLabel->height());
    m_ask2SizeLabel->setFixedSize(m_ask5SizeLabel->width(), m_ask5SizeLabel->height());
    m_ask2SizeLabel->setStyleSheet("color: yellow; font-size: 15px;");
    m_ask2SizeLabel->setFont(font);
    m_ask2SizeLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);


    // ask 1
    m_ask1PriceLabel = new QLabel("500000", this);
    m_ask1PriceLabel->move(m_ask5PriceLabel->x(), m_ask2PriceLabel->y() + m_ask2PriceLabel->height());
    m_ask1PriceLabel->setFixedSize(m_ask5PriceLabel->width(), m_ask5PriceLabel->height());
    m_ask1PriceLabel->setStyleSheet("color: green; font-size: 20px;");
    m_ask1PriceLabel->setFont(QFont("宋体", 14, QFont::Bold));
    m_ask1PriceLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    m_ask1SizeLabel = new QLabel("14", this);
    m_ask1SizeLabel->move(m_ask5SizeLabel->x(), m_ask2SizeLabel->y() + m_ask2SizeLabel->height());
    m_ask1SizeLabel->setFixedSize(m_ask5SizeLabel->width(), m_ask5SizeLabel->height());
    m_ask1SizeLabel->setStyleSheet("color: yellow; font-size: 20px;");
    m_ask1SizeLabel->setFont(QFont("宋体", 14, QFont::Bold));
    m_ask1SizeLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);


    // ---------------------------

    // bid 1.
    m_bid1PriceLabel = new QLabel("400000", this);
    m_bid1PriceLabel->move(m_ask5PriceLabel->x(), m_ask1PriceLabel->y() + m_ask1PriceLabel->height());
    m_bid1PriceLabel->setFixedSize(m_ask5PriceLabel->width(), m_ask5PriceLabel->height());
    m_bid1PriceLabel->setStyleSheet("color: red; font-size: 20px;");
    m_bid1PriceLabel->setFont(QFont("宋体", 14, QFont::Bold));
    m_bid1PriceLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    m_bid1SizeLabel = new QLabel("15", this);
    m_bid1SizeLabel->move(m_ask5SizeLabel->x(), m_ask1SizeLabel->y() + m_ask1SizeLabel->height());
    m_bid1SizeLabel->setFixedSize(m_ask5SizeLabel->width(), m_ask5SizeLabel->height());
    m_bid1SizeLabel->setStyleSheet("color: yellow; font-size: 20px;");
    m_bid1SizeLabel->setFont(QFont("宋体", 14, QFont::Bold));
    m_bid1SizeLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);


    // bid 2.
    m_bid2PriceLabel = new QLabel("300000", this);
    m_bid2PriceLabel->move(m_ask5PriceLabel->x(), m_bid1PriceLabel->y() + m_bid1PriceLabel->height());
    m_bid2PriceLabel->setFixedSize(m_ask5PriceLabel->width(), m_ask5PriceLabel->height());
    m_bid2PriceLabel->setStyleSheet("color: red; font-size: 15px;");
    m_bid2PriceLabel->setFont(font);
    m_bid2PriceLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    m_bid2SizeLabel = new QLabel("16", this);
    m_bid2SizeLabel->move(m_ask5SizeLabel->x(), m_bid1SizeLabel->y() + m_bid1SizeLabel->height());
    m_bid2SizeLabel->setFixedSize(m_ask5SizeLabel->width(), m_ask5SizeLabel->height());
    m_bid2SizeLabel->setStyleSheet("color: yellow; font-size: 15px;");
    m_bid2SizeLabel->setFont(font);
    m_bid2SizeLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);


    // bid 3.
    m_bid3PriceLabel = new QLabel("200000", this);
    m_bid3PriceLabel->move(m_ask5PriceLabel->x(), m_bid2PriceLabel->y() + m_bid2PriceLabel->height());
    m_bid3PriceLabel->setFixedSize(m_ask5PriceLabel->width(), m_ask5PriceLabel->height());
    m_bid3PriceLabel->setStyleSheet("color: red; font-size: 15px;");
    m_bid3PriceLabel->setFont(font);
    m_bid3PriceLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    m_bid3SizeLabel = new QLabel("17", this);
    m_bid3SizeLabel->move(m_ask5SizeLabel->x(), m_bid2SizeLabel->y() + m_bid2SizeLabel->height());
    m_bid3SizeLabel->setFixedSize(m_ask5SizeLabel->width(), m_ask5SizeLabel->height());
    m_bid3SizeLabel->setStyleSheet("color: yellow; font-size: 15px;");
    m_bid3SizeLabel->setFont(font);
    m_bid3SizeLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);


    // bid 4.
    m_bid4PriceLabel = new QLabel("150000", this);
    m_bid4PriceLabel->move(m_ask5PriceLabel->x(), m_bid3PriceLabel->y() + m_bid3PriceLabel->height());
    m_bid4PriceLabel->setFixedSize(m_ask5PriceLabel->width(), m_ask5PriceLabel->height());
    m_bid4PriceLabel->setStyleSheet("color: red; font-size: 15px;");
    m_bid4PriceLabel->setFont(font);
    m_bid4PriceLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    m_bid4SizeLabel = new QLabel("18", this);
    m_bid4SizeLabel->move(m_ask5SizeLabel->x(), m_bid3SizeLabel->y() + m_bid3SizeLabel->height());
    m_bid4SizeLabel->setFixedSize(m_ask5SizeLabel->width(), m_ask5SizeLabel->height());
    m_bid4SizeLabel->setStyleSheet("color: yellow; font-size: 15px;");
    m_bid4SizeLabel->setFont(font);
    m_bid4SizeLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);


    // bid 5.
    m_bid5PriceLabel = new QLabel("100000", this);
    m_bid5PriceLabel->move(m_ask5PriceLabel->x(), m_bid4PriceLabel->y() + m_bid4PriceLabel->height());
    m_bid5PriceLabel->setFixedSize(m_ask5PriceLabel->width(), m_ask5PriceLabel->height());
    m_bid5PriceLabel->setStyleSheet("color: red; font-size: 15px;");
    m_bid5PriceLabel->setFont(font);
    m_bid5PriceLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    m_bid5SizeLabel = new QLabel("19", this);
    m_bid5SizeLabel->move(m_ask5SizeLabel->x(), m_bid4SizeLabel->y() + m_bid4SizeLabel->height());
    m_bid5SizeLabel->setFixedSize(m_ask5SizeLabel->width(), m_ask5SizeLabel->height());
    m_bid5SizeLabel->setStyleSheet("color: yellow; font-size: 15px;");
    m_bid5SizeLabel->setFont(font);
    m_bid5SizeLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
}

void TQZTradeController::updateTick(QObject tick) {
    // for test.
    this->m_ask1PriceLabel->setText("1");
    this->m_ask2PriceLabel->setText("2");
    this->m_ask3PriceLabel->setText("3");
    this->m_ask4PriceLabel->setText("4");
    this->m_ask5PriceLabel->setText("5");
    this->m_bid1PriceLabel->setText("6");
    this->m_bid2PriceLabel->setText("7");
    this->m_bid3PriceLabel->setText("8");
    this->m_bid4PriceLabel->setText("9");
    this->m_bid5PriceLabel->setText("10");

    this->m_ask1SizeLabel->setText("1");
    this->m_ask2SizeLabel->setText("2");
    this->m_ask3SizeLabel->setText("3");
    this->m_ask4SizeLabel->setText("4");
    this->m_ask5SizeLabel->setText("5");
    this->m_bid1SizeLabel->setText("6");
    this->m_bid2SizeLabel->setText("7");
    this->m_bid3SizeLabel->setText("8");
    this->m_bid4SizeLabel->setText("9");
    this->m_bid5SizeLabel->setText("10");
}

TQZButton *TQZTradeController::closeButton() {
    if (this->m_closeButton == nullptr) {
        double height = 30;

        this->m_closeButton = new TQZButton("X", TQZButtonType::CLOSE, this);
        this->m_closeButton->move(this->width() - height, 0);
        this->m_closeButton->setFixedSize(height, height);
        this->m_closeButton->connect(this->m_closeButton, &TQZButton::clicked, this, &TQZTradeController::close);
    }

    return this->m_closeButton;
}

TQZButton *TQZTradeController::sendOrderButton() {
    if (this->m_sendOrderButton == nullptr) {
        this->m_sendOrderButton = new TQZButton("send order", TQZButtonType::LOCK, this);
    }

    return this->m_sendOrderButton;
}
