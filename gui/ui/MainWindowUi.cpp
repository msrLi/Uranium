#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QFileDialog>

#include "version.h"
#include "common.h"
#include "ui/MainWindowUi.h"
#include "CoreHandler.h"
#include "Dialogs.h"

namespace uranium {

MainWindowUi::MainWindowUi() :
    mStarted(false),
    mCore(nullptr)
{
}

MainWindowUi::~MainWindowUi()
{
}

int32_t MainWindowUi::setupUi(QMainWindow *MainWindow)
{
    int32_t rc = NO_ERROR;
    QFont checkBoxFont;
    QFont lineEditFont;
    QFont settingBlankingFont;
    QSizePolicy virtualExpandingPolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    if (SUCCEED(rc)) {
        if (MainWindow->objectName().isEmpty()) {
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        }
        MainWindow->resize(1209, 848);
    }

    if (SUCCEED(rc)) {
        mActionAbout = new QAction(MainWindow);
        mActionAbout->setObjectName(QStringLiteral("mActionAbout"));
        connect(mActionAbout, SIGNAL(triggered(bool)), this, SIGNAL(about()));
        mActionExit = new QAction(MainWindow);
        mActionExit->setObjectName(QStringLiteral("mActionExit"));
        connect(mActionExit, SIGNAL(triggered(bool)), this, SIGNAL(quit()));
    }

    if (SUCCEED(rc)) {
        mCentralWidget = new QWidget(MainWindow);
        mCentralWidget->setObjectName(QStringLiteral("mCentralWidget"));
        mHorizontalLayoutWidget = new QWidget(mCentralWidget);
        mHorizontalLayoutWidget->setObjectName(QStringLiteral("mHorizontalLayoutWidget"));
        mHorizontalLayoutWidget->setGeometry(QRect(10, 10, 1191, 791));
    }

    if (SUCCEED(rc)) {
        mSettingHorizontalLayout = new QHBoxLayout(mHorizontalLayoutWidget);
        mSettingHorizontalLayout->setSpacing(6);
        mSettingHorizontalLayout->setContentsMargins(11, 11, 11, 11);
        mSettingHorizontalLayout->setObjectName(QStringLiteral("mSettingHorizontalLayout"));
        mSettingHorizontalLayout->setContentsMargins(0, 0, 0, 0);
    }

    if (SUCCEED(rc)) {
        mSettingGroupBox = new QGroupBox(mHorizontalLayoutWidget);
        mSettingGroupBox->setObjectName(QStringLiteral("mSettingGroupBox"));
        mVerticalLayoutWidget = new QWidget(mSettingGroupBox);
        mVerticalLayoutWidget->setObjectName(QStringLiteral("mVerticalLayoutWidget"));
        mVerticalLayoutWidget->setGeometry(QRect(10, 10, 571, 770));
        mSettingverticalLayout = new QVBoxLayout(mVerticalLayoutWidget);
        mSettingverticalLayout->setSpacing(6);
        mSettingverticalLayout->setContentsMargins(11, 11, 11, 11);
        mSettingverticalLayout->setObjectName(QStringLiteral("mSettingverticalLayout"));
        mSettingverticalLayout->setContentsMargins(0, 0, 0, 0);
    }

    if (SUCCEED(rc)) {
        mCheckBoxGridLayout = new QGridLayout();
        mCheckBoxGridLayout->setSpacing(6);
        mCheckBoxGridLayout->setObjectName(QStringLiteral("mCheckBoxGridLayout"));
    }

    if (SUCCEED(rc)) {
        mMasterCheckBox = new QCheckBox(mVerticalLayoutWidget);
        mMasterCheckBox->setObjectName(QStringLiteral("mMasterCheckBox"));
        checkBoxFont.setPointSize(14);
        checkBoxFont.setBold(true);
        checkBoxFont.setWeight(75);
        mMasterCheckBox->setFont(checkBoxFont);
        mCheckBoxGridLayout->addWidget(mMasterCheckBox, 1, 0, 1, 1);
    }

    if (SUCCEED(rc)) {
        mStartPushButton = new QPushButton(mVerticalLayoutWidget);
        mStartPushButton->setObjectName(QStringLiteral("mStartPushButton"));
        virtualExpandingPolicy.setHorizontalStretch(0);
        virtualExpandingPolicy.setVerticalStretch(0);
        virtualExpandingPolicy.setHeightForWidth(mStartPushButton->sizePolicy().hasHeightForWidth());
        mStartPushButton->setSizePolicy(virtualExpandingPolicy);
        mStartPushButton->setEnabled(false);
        QFont font1;
        font1.setFamily(QStringLiteral("Consolas"));
        font1.setPointSize(22);
        font1.setBold(true);
        font1.setWeight(75);
        mStartPushButton->setFont(font1);
        mCheckBoxGridLayout->addWidget(mStartPushButton, 0, 4, 5, 1);
        connect(mStartPushButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
    }

    if (SUCCEED(rc)) {
        mCheckBoxHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        mCheckBoxGridLayout->addItem(mCheckBoxHorizontalSpacer, 1, 1, 4, 1);

        mDebugCheckBox = new QCheckBox(mVerticalLayoutWidget);
        mDebugCheckBox->setObjectName(QStringLiteral("mDebugCheckBox"));
        mDebugCheckBox->setEnabled(false);
        mDebugCheckBox->setFont(checkBoxFont);
        mDebugCheckBox->setChecked(true);
        mCheckBoxGridLayout->addWidget(mDebugCheckBox, 3, 0, 1, 1);
    }

    if (SUCCEED(rc)) {
        mRemoteControlCheckBox = new QCheckBox(mVerticalLayoutWidget);
        mRemoteControlCheckBox->setObjectName(QStringLiteral("mRemoteControlCheckBox"));
        mRemoteControlCheckBox->setFont(checkBoxFont);
        mCheckBoxGridLayout->addWidget(mRemoteControlCheckBox, 4, 0, 1, 1);
    }

    if (SUCCEED(rc)) {
        mEncryptionCheckBox = new QCheckBox(mVerticalLayoutWidget);
        mEncryptionCheckBox->setObjectName(QStringLiteral("mEncryptionCheckBox"));
        mEncryptionCheckBox->setEnabled(false);
        mEncryptionCheckBox->setFont(checkBoxFont);
        mEncryptionCheckBox->setCheckable(true);
        mEncryptionCheckBox->setChecked(true);
        mCheckBoxGridLayout->addWidget(mEncryptionCheckBox, 2, 0, 1, 1);
    }


    if (SUCCEED(rc)) {
        mStatusLabel = new QLabel(mVerticalLayoutWidget);
        mStatusLabel->setObjectName(QStringLiteral("mStatusLabel"));
        mStatusLabel->setSizePolicy(virtualExpandingPolicy);
        mStatusLabel->resize(mStatusLabel->width(), mStatusLabel->width());
        QImage Image;
        Image.load(":/status/question");
        QPixmap pixmap = QPixmap::fromImage(Image);
        QPixmap fitPixmap = pixmap.scaled(mStatusLabel->width(),
            mStatusLabel->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        mStatusLabel->setPixmap(fitPixmap);
        mCheckBoxGridLayout->addWidget(mStatusLabel, 1, 2, 4, 1);
    }

    if (SUCCEED(rc)) {
        mStartedLabel = new QLabel(mVerticalLayoutWidget);
        mStartedLabel->setObjectName(QStringLiteral("mStartedLabel"));
        mStartedLabel->setSizePolicy(virtualExpandingPolicy);
        mStartedLabel->resize(mStartedLabel->width(), mStartedLabel->width());
        QImage Image;
        Image.load(":/status/question");
        QPixmap pixmap = QPixmap::fromImage(Image);
        QPixmap fitPixmap = pixmap.scaled(mStatusLabel->width(),
            mStatusLabel->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        mStartedLabel->setPixmap(fitPixmap);
        mCheckBoxGridLayout->addWidget(mStartedLabel, 1, 3, 4, 1);
        mSettingverticalLayout->addLayout(mCheckBoxGridLayout);
    }

    if (SUCCEED(rc)) {
        mSettingBlanking1 = new QLabel(mVerticalLayoutWidget);
        mSettingBlanking1->setObjectName(QStringLiteral("mSettingBlanking1"));
        settingBlankingFont.setPointSize(10);
        settingBlankingFont.setBold(true);
        settingBlankingFont.setWeight(75);
        mSettingBlanking1->setFont(settingBlankingFont);
        mSettingverticalLayout->addWidget(mSettingBlanking1);
    }

    if (SUCCEED(rc)) {
        mInputBoxGridLayout = new QGridLayout();
        mInputBoxGridLayout->setSpacing(6);
        mInputBoxGridLayout->setObjectName(QStringLiteral("mInputBoxGridLayout"));
    }

    if (SUCCEED(rc)) {
        mLocalDirLabel = new QLabel(mVerticalLayoutWidget);
        mLocalDirLabel->setObjectName(QStringLiteral("mLocalDirLabel"));
        lineEditFont.setPointSize(12);
        lineEditFont.setBold(false);
        lineEditFont.setWeight(50);
        mLocalDirLabel->setFont(lineEditFont);
        mInputBoxGridLayout->addWidget(mLocalDirLabel, 3, 0, 1, 1);

        mLocalDirLineEdit = new QLineEdit(mVerticalLayoutWidget);
        mLocalDirLineEdit->setObjectName(QStringLiteral("mLocalDirLineEdit"));
        mLocalDirLineEdit->setFont(lineEditFont);
        mInputBoxGridLayout->addWidget(mLocalDirLineEdit, 3, 1, 1, 1);

        mSelectPushButton = new QPushButton(mVerticalLayoutWidget);
        mSelectPushButton->setObjectName(QStringLiteral("mSelectPushButton"));
        mSelectPushButton->setFont(lineEditFont);
        mInputBoxGridLayout->addWidget(mSelectPushButton, 3, 2, 1, 1);
        connect(mSelectPushButton, SIGNAL(clicked()), this, SLOT(onSelectButonClicked()));
    }

    if (SUCCEED(rc)) {
        mPasswordLabel = new QLabel(mVerticalLayoutWidget);
        mPasswordLabel->setObjectName(QStringLiteral("mPasswordLabel"));
        mPasswordLabel->setFont(lineEditFont);
        mInputBoxGridLayout->addWidget(mPasswordLabel, 1, 0, 1, 1);

        mPasswordLineEdit = new QLineEdit(mVerticalLayoutWidget);
        mPasswordLineEdit->setObjectName(QStringLiteral("mPasswordLineEdit"));
        mPasswordLineEdit->setFont(lineEditFont);
        mPasswordLineEdit->setEchoMode(QLineEdit::Password);
        mInputBoxGridLayout->addWidget(mPasswordLineEdit, 1, 1, 1, 2);
    }

    if (SUCCEED(rc)) {
        mUserNameLabel = new QLabel(mVerticalLayoutWidget);
        mUserNameLabel->setObjectName(QStringLiteral("mUserNameLabel"));
        mUserNameLabel->setFont(lineEditFont);
        mInputBoxGridLayout->addWidget(mUserNameLabel, 0, 0, 1, 1);

        mUserNameLineEdit = new QLineEdit(mVerticalLayoutWidget);
        mUserNameLineEdit->setObjectName(QStringLiteral("mUserNameLineEdit"));
        mUserNameLineEdit->setFont(lineEditFont);
        mInputBoxGridLayout->addWidget(mUserNameLineEdit, 0, 1, 1, 2);
    }

    if (SUCCEED(rc)) {
        mRemoteDirLabel = new QLabel(mVerticalLayoutWidget);
        mRemoteDirLabel->setObjectName(QStringLiteral("mRemoteDirLabel"));
        mRemoteDirLabel->setFont(lineEditFont);
        mInputBoxGridLayout->addWidget(mRemoteDirLabel, 2, 0, 1, 1);

        mRemoteDirLineEdit = new QLineEdit(mVerticalLayoutWidget);
        mRemoteDirLineEdit->setObjectName(QStringLiteral("mRemoteDirLineEdit"));
        mRemoteDirLineEdit->setFont(lineEditFont);
        mInputBoxGridLayout->addWidget(mRemoteDirLineEdit, 2, 1, 1, 2);
    }

    if (SUCCEED(rc)) {
        mSettingverticalLayout->addLayout(mInputBoxGridLayout);

        mSettingBlanking2 = new QLabel(mVerticalLayoutWidget);
        mSettingBlanking2->setObjectName(QStringLiteral("mSettingBlanking2"));
        mSettingBlanking2->setFont(settingBlankingFont);
        mSettingverticalLayout->addWidget(mSettingBlanking2);
    }

    if (SUCCEED(rc)) {
        mDebugTextEdit = new QTextEdit(mVerticalLayoutWidget);
        mDebugTextEdit->setObjectName(QStringLiteral("mDebugTextEdit"));
        QFont font6;
        font6.setFamily(QStringLiteral("Consolas"));
        font6.setPointSize(10);
        mDebugTextEdit->setFont(font6);
        mSettingverticalLayout->addWidget(mDebugTextEdit);

        mSettingHorizontalLayout->addWidget(mSettingGroupBox);
    }

    if (SUCCEED(rc)) {
        mShellGroupBox = new QGroupBox(mHorizontalLayoutWidget);
        mShellGroupBox->setObjectName(QStringLiteral("mShellGroupBox"));
        mShellTextEditor = new QTextEdit(mShellGroupBox);
        mShellTextEditor->setObjectName(QStringLiteral("mShellTextEditor"));
        mShellTextEditor->setGeometry(QRect(10, 20, 571, 761));
        QFont font7;
        font7.setFamily(QStringLiteral("Consolas"));
        font7.setPointSize(10);
        font7.setBold(true);
        font7.setWeight(75);
        mShellTextEditor->setFont(font7);
        mSettingHorizontalLayout->addWidget(mShellGroupBox);
    }

    if (SUCCEED(rc)) {
        MainWindow->setCentralWidget(mCentralWidget);
        mMenuBar = new QMenuBar(MainWindow);
        mMenuBar->setObjectName(QStringLiteral("mMenuBar"));
        mMenuBar->setGeometry(QRect(0, 0, 1209, 17));
        mMenuFile = new QMenu(mMenuBar);
        mMenuFile->setObjectName(QStringLiteral("mMenuFile"));
        mMenuHelp = new QMenu(mMenuBar);
        mMenuHelp->setObjectName(QStringLiteral("mMenuHelp"));
        MainWindow->setMenuBar(mMenuBar);
        mStatusBar = new QStatusBar(MainWindow);
        mStatusBar->setObjectName(QStringLiteral("mStatusBar"));
        MainWindow->setStatusBar(mStatusBar);
    }

    if (SUCCEED(rc)) {
        QWidget::setTabOrder(mMasterCheckBox, mStartPushButton);
        QWidget::setTabOrder(mStartPushButton, mEncryptionCheckBox);
        QWidget::setTabOrder(mEncryptionCheckBox, mDebugCheckBox);
        QWidget::setTabOrder(mDebugCheckBox, mRemoteControlCheckBox);
        QWidget::setTabOrder(mRemoteControlCheckBox, mUserNameLineEdit);
        QWidget::setTabOrder(mUserNameLineEdit, mPasswordLineEdit);
        QWidget::setTabOrder(mPasswordLineEdit, mRemoteDirLineEdit);
        QWidget::setTabOrder(mRemoteDirLineEdit, mLocalDirLineEdit);
        QWidget::setTabOrder(mLocalDirLineEdit, mLocalDirLineEdit);
        QWidget::setTabOrder(mLocalDirLineEdit, mRemoteDirLineEdit);
        QWidget::setTabOrder(mRemoteDirLineEdit, mPasswordLineEdit);
        QWidget::setTabOrder(mPasswordLineEdit, mUserNameLineEdit);
        QWidget::setTabOrder(mUserNameLineEdit, mSelectPushButton);
        QWidget::setTabOrder(mSelectPushButton, mSelectPushButton);
        QWidget::setTabOrder(mSelectPushButton, mDebugTextEdit);
        QWidget::setTabOrder(mDebugTextEdit, mShellTextEditor);
    }

    if (SUCCEED(rc)) {
        mMenuBar->addAction(mMenuFile->menuAction());
        mMenuBar->addAction(mMenuHelp->menuAction());
        mMenuFile->addAction(mActionExit);
        mMenuHelp->addAction(mActionAbout);
    }

    if (SUCCEED(rc)) {
        connect(mMasterCheckBox,        SIGNAL(toggled(bool)), this, SLOT(setConfig(bool)));
        connect(mDebugCheckBox,         SIGNAL(toggled(bool)), this, SLOT(setConfig(bool)));
        connect(mEncryptionCheckBox,    SIGNAL(toggled(bool)), this, SLOT(setConfig(bool)));
        connect(mRemoteControlCheckBox, SIGNAL(toggled(bool)), this, SLOT(setConfig(bool)));
        connect(mPasswordLineEdit,      SIGNAL(textChanged(const QString &)), this, SLOT(setConfig(const QString &)));
        connect(mUserNameLineEdit,      SIGNAL(textChanged(const QString &)), this, SLOT(setConfig(const QString &)));
        connect(mRemoteDirLineEdit,     SIGNAL(textChanged(const QString &)), this, SLOT(setConfig(const QString &)));
        connect(mLocalDirLineEdit,      SIGNAL(textChanged(const QString &)), this, SLOT(setConfig(const QString &)));
    }

    if (SUCCEED(rc) || !SUCCEED(rc)) {
        retranslateUi(MainWindow);
        QMetaObject::connectSlotsByName(MainWindow);
    }

    return NO_ERROR;
}

void MainWindowUi::retranslateUi(QMainWindow *MainWindow)
{
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", PROJNAME " " VERSION, nullptr));
    mActionAbout->setText(QApplication::translate("MainWindow", "About", nullptr));
    mActionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
    mSettingGroupBox->setTitle(QApplication::translate("MainWindow", "Settings", nullptr));
    mMasterCheckBox->setText(QApplication::translate("MainWindow", "Master to Override Remote", nullptr));
    mStartPushButton->setText(QApplication::translate("MainWindow", " Start ", nullptr));
    mDebugCheckBox->setText(QApplication::translate("MainWindow", "Debug Mode", nullptr));
    mRemoteControlCheckBox->setText(QApplication::translate("MainWindow", "Enable Remote Control", nullptr));
    mEncryptionCheckBox->setText(QApplication::translate("MainWindow", "Encryption", nullptr));
    mStatusLabel->setText(QString());
    mStartedLabel->setText(QString());
    mSettingBlanking1->setText(QString());
    mLocalDirLabel->setText(QApplication::translate("MainWindow", "Local Directory", nullptr));
    mPasswordLabel->setText(QApplication::translate("MainWindow", "Password", nullptr));
    mSelectPushButton->setText(QApplication::translate("MainWindow", "Select ...", nullptr));
    mUserNameLabel->setText(QApplication::translate("MainWindow", "User Name", nullptr));
    mRemoteDirLabel->setText(QApplication::translate("MainWindow", "Remote Directory", nullptr));
    mSettingBlanking2->setText(QString());
    mDebugTextEdit->setHtml(QApplication::translate("MainWindow",
        "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
        "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:'Consolas'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
            "<span style=\" font-family:'Courier New'; font-size:12pt;\">Debug Window &gt; </span></p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
            "<span style=\" font-family:'Courier New'; font-size:12pt;\">Wish you have a pleasant day. :)</span></p></body></html>",
                nullptr));
    mShellGroupBox->setTitle(QApplication::translate("MainWindow", "Remote Shell", nullptr));
    mShellTextEditor->setHtml(QApplication::translate("MainWindow",
        "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
        "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:'Consolas'; font-size:10pt; font-weight:600; font-style:normal;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
            "Unknown@Remote:/home/Unknown$</p></body></html>", nullptr));
    mMenuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    mMenuHelp->setTitle(QApplication::translate("MainWindow", "Help", nullptr));
}

int32_t MainWindowUi::setupCore()
{
    int32_t rc = NO_ERROR;

    if (SUCCEED(rc)) {
        mCore = new CoreHandler(this);
        if (NOTNULL(mCore)) {
            rc = mCore->construct();
            if (FAILED(rc)) {
                showError("Failed to construct core, " + rc);
            }
        }
    }

    if (SUCCEED(rc)) {
        rc = loadConfig();
        if (FAILED(rc)) {
            showError("Failed to load config, " + rc);
        }
    }

    return rc;
}

int32_t MainWindowUi::destructCore()
{
    int32_t rc = NO_ERROR;

    if (SUCCEED(rc)) {
        if (NOTNULL(mCore)) {
            rc = mCore->destruct();
            if (FAILED(rc)) {
                showError("Failed to destruct core, " + rc);
            }
        }
        SECURE_DELETE(mCore);
    }

    return rc;
}

int32_t MainWindowUi::updateUi()
{
    return NO_ERROR;
}

int32_t MainWindowUi::onStarted(int32_t rc)
{
    mStarted = SUCCEED(rc);

    QImage Image;
    Image.load(mStarted ? ":/status/succeed" : ":/status/failed");
    QPixmap pixmap = QPixmap::fromImage(Image);
    QPixmap fitPixmap = pixmap.scaled(mStartedLabel->width(),
        mStartedLabel->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    mStartedLabel->setPixmap(fitPixmap);
    mStartPushButton->setText(QApplication::translate("MainWindow",
        mStarted ? " Stop " : " Start ", nullptr));

    return NO_ERROR;
}

int32_t MainWindowUi::onStopped(int32_t rc)
{
    mStarted = FAILED(rc);

    QImage Image;
    Image.load(!mStarted ? ":/status/question" : ":/status/failed");
    QPixmap pixmap = QPixmap::fromImage(Image);
    QPixmap fitPixmap = pixmap.scaled(mStartedLabel->width(),
        mStartedLabel->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    mStartedLabel->setPixmap(fitPixmap);
    mStartPushButton->setText(QApplication::translate("MainWindow",
        !mStarted ? " Start " : " Stop ", nullptr));

    return NO_ERROR;
}

int32_t MainWindowUi::onInitialized(int32_t rc)
{
    mStartPushButton->setEnabled(SUCCEED(rc));

    QImage Image;
    Image.load(SUCCEED(rc) ? ":/status/succeed" : ":/status/failed");
    QPixmap pixmap = QPixmap::fromImage(Image);
    QPixmap fitPixmap = pixmap.scaled(mStatusLabel->width(),
        mStatusLabel->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    mStatusLabel->setPixmap(fitPixmap);

    return NO_ERROR;
}

int32_t MainWindowUi::appendDebugger(std::string str)
{
    mDebugTextEdit->append(str.c_str());
    QTextCursor cursor = mDebugTextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    mDebugTextEdit->setTextCursor(cursor);

    return NO_ERROR;
}

int32_t MainWindowUi::appendShell(std::string str)
{
    mShellTextEditor->append(str.c_str());
    QTextCursor cursor = mShellTextEditor->textCursor();
    cursor.movePosition(QTextCursor::End);
    mShellTextEditor->setTextCursor(cursor);

    return NO_ERROR;
}

int32_t MainWindowUi::onStartButtonClicked()
{
    int32_t rc = NO_ERROR;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);

    if (SUCCEED(rc)) {
        if (mStarted) {
            rc = mCore->stop();
            if (!SUCCEED(rc)) {
                showError("Failed to stop core");
            }
        } else {
            rc = mCore->start();
            if (!SUCCEED(rc)) {
                showError("Failed to start core");
            }
        }
    }
    pthread_mutex_unlock(&mutex);

    return rc;
}

int32_t MainWindowUi::onSelectButonClicked()
{
    int32_t rc = NO_ERROR;
    QString path;

    if (SUCCEED(rc)) {
        QString old = mLocalDirLineEdit->text();
        path = QFileDialog::getExistingDirectory(mCentralWidget,
            "Choose Path Directory", old.toLocal8Bit().data(),
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        mLocalDirLineEdit->setText(QApplication::translate("MainWindow",
            path.toLocal8Bit().data(), nullptr));
    }

    if (SUCCEED(rc)) {
        rc = mCore->setConfig(CONFIG_LOCAL_PATH, path.toLocal8Bit().data());
        if (!SUCCEED(rc)) {
            QString err = "Failed to set local path to";
            showError(err + path.toLocal8Bit().data());
        }
    }

    return rc;
}

int32_t MainWindowUi::loadConfig()
{
    int32_t rc = NO_ERROR;

    bool master = true;
    bool encryption = true;
    bool debug = true;
    bool shell = false;
    std::string username;
    std::string password;
    std::string localpath;
    std::string remotePath;

    if (SUCCEED(rc)) {
        rc  = mCore->getConfig(CONFIG_MASTER_MODE, master);
        rc |= mCore->getConfig(CONFIG_ENCRYPTION, encryption);
        rc |= mCore->getConfig(CONFIG_DEBUG_MODE, debug);
        rc |= mCore->getConfig(CONFIG_REMOTE_SHELL, shell);
        rc |= mCore->getConfig(CONFIG_USERNAME, username);
        rc |= mCore->getConfig(CONFIG_PASSWORD, password);
        rc |= mCore->getConfig(CONFIG_LOCAL_PATH, localpath);
        rc |= mCore->getConfig(CONFIG_REMOTE_PATH, remotePath);
        if (FAILED(rc)) {
            showError("gui load config failed.");
        }
    }

    if (SUCCEED(rc)) {
        mMasterCheckBox->setChecked(master);
        mDebugCheckBox->setChecked(debug);
        mEncryptionCheckBox->setChecked(encryption);
        mRemoteControlCheckBox->setChecked(shell);
        mPasswordLineEdit->setText(password.c_str());
        mUserNameLineEdit->setText(username.c_str());
        mRemoteDirLineEdit->setText(remotePath.c_str());
        mLocalDirLineEdit->setText(localpath.c_str());
    }

    return rc;
}

int32_t MainWindowUi::setConfig(bool checked)
{
    int32_t rc = NO_ERROR;

    QString name = sender()->objectName();
    if (name == "mMasterCheckBox") {
        rc = mCore->setConfig(CONFIG_MASTER_MODE, checked);
    } else if (name == "mDebugCheckBox") {
        rc = mCore->setConfig(CONFIG_DEBUG_MODE, checked);
    } else if (name == "mEncryptionCheckBox") {
        rc = mCore->setConfig(CONFIG_ENCRYPTION, checked);
    } else if (name == "mRemoteControlCheckBox") {
        rc = mCore->setConfig(CONFIG_REMOTE_SHELL, checked);
    }

    if (FAILED(rc)) {
        QString err = "failed to set config.";
        showError(err + name);
    }

    return rc;
}

int32_t MainWindowUi::setConfig(const QString &set)
{
    int32_t rc = NO_ERROR;

    QString name = sender()->objectName();
    if (name == "mPasswordLineEdit") {
        rc = mCore->setConfig(CONFIG_PASSWORD, set.toLatin1().data());
    } else if (name == "mUserNameLineEdit") {
        rc = mCore->setConfig(CONFIG_USERNAME, set.toLatin1().data());
    } else if (name == "mRemoteDirLineEdit") {
        rc = mCore->setConfig(CONFIG_REMOTE_PATH, set.toLatin1().data());
    } else if (name == "mLocalDirLineEdit") {
        rc = mCore->setConfig(CONFIG_LOCAL_PATH, set.toLatin1().data());
    }

    if (FAILED(rc)) {
        QString err = "failed to set config.";
        showError(err + name);
    }

    return rc;
}

}
