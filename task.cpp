#include <QInputDialog>
#include "task.h"
#include "ui_task.h"

Task::Task(const QString &name, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Task)
{
	ui->setupUi(this);
	setName(name);
	connect(ui->editButton, &QPushButton::clicked, this, &Task::rename);
	connect(ui->delButton, &QPushButton::clicked, [this] {
		emit removed(this);
	});
	connect(ui->checkbox, &QCheckBox::toggled, this, &Task::checked);
}

Task::~Task()
{
	delete ui;
}

void Task::setName(const QString &name) {
	ui->checkbox->setText(name);
}

QString Task::name() const {
	return ui->checkbox->text();
}

bool Task::isComplete() const {
	return ui->checkbox->isChecked();
}

void Task::rename() {
	bool ok;
	QString val = QInputDialog::getText(this,
			tr("Rename task"),
			tr("Task describe"),
			QLineEdit::Normal,
			name(),
			&ok);
	if (ok && !val.isEmpty()) {
		setName(val);
	}
}

void Task::checked(bool checked) {
	QFont font(ui->checkbox->font());
	font.setStrikeOut(checked);
	ui->checkbox->setFont(font);
	emit statusChanged(this);
}
