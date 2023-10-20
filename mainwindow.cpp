#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QDebug>
#include <QProcess>
#include <QApplication>
#include <QFont>
#include <QFileDialog>

MainWindow::MainWindow()
{
	QFont font("Microsoft YaHei", 10);
	this->setFont(font);

	this->setWindowTitle(QString::fromLocal8Bit("DST模组提取工具"));

	QWidget* centerWidget = new QWidget;
	this->setCentralWidget(centerWidget);

	QVBoxLayout* mainLayout = new QVBoxLayout(centerWidget);


	m_textEdit = new QTextEdit;
	mainLayout->addWidget(m_textEdit);
	mainLayout->addSpacing(20);
	QHBoxLayout* layout = new QHBoxLayout;
	layout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding));
	QPushButton* bt = new QPushButton(QString::fromLocal8Bit("选择文件"));
	connect(bt, &QPushButton::clicked, this, &MainWindow::onOpenFile);
	layout->addWidget(bt);
	layout->addSpacing(125);
	bt = new QPushButton(QString::fromLocal8Bit("生成"));
	connect(bt, &QPushButton::clicked, this, &MainWindow::onGenerateSettingFiles);
	layout->addWidget(bt);
	layout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding));

	mainLayout->addLayout(layout);
	mainLayout->setContentsMargins(10, 10, 10, 20);

	this->setFixedSize(1280, 900);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onOpenFile()
{
	QString defaultPath = QString("%1/Documents/Klei/DoNotStarveTogether/").arg(QDir::homePath());
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), defaultPath, tr("Lua Files (modoverrides.lua)"));
	QFile f(fileName);
	if (f.open(QIODevice::ReadOnly))
	{
		m_textEdit->append(f.readAll());
		f.close();
	}
}

void MainWindow::onGenerateSettingFiles()
{
	QString text = m_textEdit->toPlainText();
	QRegExp reg("\\[\"workshop-\\d+\"\\]");
	reg.indexIn(text);

	QStringList sl;

	int pos = 0;
	while ((pos = reg.indexIn(text, pos)) != -1)
	{
		pos += reg.matchedLength();
		sl << reg.cap(0);
	}

	if (!sl.empty())
	{
		QString filePath = QString("%1/dedicated_server_mods_setup.lua").arg(QApplication::applicationDirPath());
		QFile f(filePath);
		f.open(QIODevice::Truncate | QIODevice::WriteOnly);
		QTextStream out(&f);

		for (auto it : sl)
		{
			QRegExp rx("\\d+");
			int pos = rx.indexIn(it);
			if (pos != -1)
				out << QString("ServerModSetup(\"%1\")\r\n").arg(rx.cap(0));
		}
		out << "\r\n\r\n";
		for (auto it : sl)
		{
			QRegExp rx("\\d+");
			int pos = rx.indexIn(it);
			if (pos != -1)
				out << QString("ServerModCollectionSetup(\"%1\")\r\n").arg(rx.cap(0));
		}
		f.close();

		const QString explorer = "explorer";
		QStringList param;
		param << QString("/e,/select,%1").arg(QDir::toNativeSeparators(filePath));
		QProcess::startDetached(explorer, param);

	}
}
