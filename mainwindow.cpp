#include "mainwindow.hpp"
#include "include/extractor.hpp"
#include "include/cleaner.hpp"

#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QWidget>

#include<vector>
#include<string>

MainWindow::~MainWindow() { }

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    QWidget *centralWidget = new QWidget(this);
	centralWidget->setMinimumSize(QSize(650, 450));
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(); 

    QPushButton *selectButton = new QPushButton("Select file for fetching", this);
    removeButton = new QPushButton("Remove metadata", this);
    lineEditFilePath = new QLineEdit(this);
    metadataDisplay = new QTextEdit(this);
    metadataDisplay->setReadOnly(true);

    layout->addWidget(selectButton);
    layout->addWidget(lineEditFilePath);
    layout->addWidget(removeButton);
    layout->addWidget(metadataDisplay);

    centralWidget->setLayout(layout);
	
    connect(selectButton, &QPushButton::clicked, this, &MainWindow::selectFile);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeMetadata);

    removeButton->setEnabled(false);
}


void MainWindow::selectFile() {
	filePath = QFileDialog::getOpenFileName(this, "Select file for fetching", "", "All Files (*)");
	if (filePath.isEmpty()) {
		return;
	}
	lineEditFilePath->setText(filePath);
	std::string metadata = Extractor::extractMetadata(filePath.toStdString());
	
	if (!metadata.empty()) {
		metadataDisplay->setText(QString::fromStdString(metadata));
		removeButton->setEnabled(true);
	} else {
		metadataDisplay->clear();
		removeButton->setEnabled(false);
		QMessageBox::warning(this, "Error", "Faild to fetch metadata");
	}
}

void MainWindow::removeMetadata() {

	QString filePath = lineEditFilePath->text();
	if (filePath.isEmpty()) {
		QMessageBox::warning(this, "Error", "Please, select a file");
		return;
	}

	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to remove metadata?", 
		QMessageBox::Yes | QMessageBox::No);

	if (reply == QMessageBox::Yes) {
		QStringList tags;
		bool ok;
		QString tagInput = QInputDialog::getText(this, "Enter tags", "Enter tags to remove (separated by commas or use 'all'):",
			QLineEdit::Normal, "", &ok);

		if (ok && !tagInput.isEmpty()) {
			std::vector<std::string> tagList; 
			for (const QString &tag : tagInput.split(",")) {
				tagList.push_back(tag.toStdString());
			}

			bool success = Cleaner::removeMetadata(filePath.toStdString(), tagList);
			if (success) {
				QMessageBox::information(this, "Success", "Metadata removed successfully.");
			} else {
				QMessageBox::critical(this, "Error", "Failed to remove metadata.");
			}
		}
	}
}