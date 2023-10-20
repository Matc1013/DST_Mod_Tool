#include <QMainWindow>
#include <QDir>
#include <QRegExp>
#include <QFile>
#include <QComboBox>
#include <QPushButton>

class MainWindow : public QMainWindow
{
public:
	MainWindow();

	~MainWindow();

	void onOpenFile();
	void onGenerateSettingFiles();

private:

	class QTextEdit* m_textEdit = nullptr;

};