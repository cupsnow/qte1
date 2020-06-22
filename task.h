#ifndef TASK_H
#define TASK_H

#include <QWidget>

namespace Ui {
class Task;
}

class Task : public QWidget
{
	Q_OBJECT

public:
	explicit Task(const QString &name, QWidget *parent = nullptr);
	~Task();

	void setName(const QString&);
	QString name() const;
	bool isComplete() const;

public slots:
	void rename();
	void checked(bool);

signals:
	void removed(Task*);
	void statusChanged(Task*);

private:
	Ui::Task *ui;
};

#endif // TASK_H
