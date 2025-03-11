#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLineEdit>


class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();
private slots:
	void selectFile();
	void removeMetadata();

private:
	QLineEdit* lineEditFilePath;
	QString filePath;
	QTextEdit* metadataDisplay;
	QPushButton* removeButton;
};


#endif // MAINWINDOW_HPP

