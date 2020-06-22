#include <qdebug.h>
#include <QInputDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
	updateStatus();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::addTask() {
	qDebug() << "Add new task";
	bool ok;
	QString name = QInputDialog::getText(this,
			tr("Add task"),
			tr("Task describe"),
			QLineEdit::Normal,
			tr("Unknown task"),
			&ok);
	if (ok && !name.isEmpty()) {
		Task *task = new Task(name);
		connect(task, &Task::removed, this, &MainWindow::delTask);
		connect(task, &Task::statusChanged, this, &MainWindow::taskStatusChanged);
		mTasks.append(task);
		ui->taskLayout->addWidget(task);
		updateStatus();
	}
}

void MainWindow::delTask(Task *task) {
	mTasks.removeOne(task);
	ui->taskLayout->removeWidget(task);
	delete task;
	updateStatus();
}

void MainWindow::taskStatusChanged(Task*) {
	updateStatus();
}

void MainWindow::updateStatus() {
	int completedCount = 0;
	for (auto i: mTasks) {
		if (i->isComplete()) completedCount++;
	}
	int todoCount = mTasks.size() - completedCount;
	ui->statusLabel->setText(QString("Status: %1 todo, %2 done")
			.arg(todoCount)
			.arg(completedCount));
}
