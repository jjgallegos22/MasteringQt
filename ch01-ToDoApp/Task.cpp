#include "Task.h"
#include "ui_Task.h"

#include <QInputDialog>

Task::Task(const QString& name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    setName(name);
    connect(ui->editButton, &QPushButton::clicked, this, &Task::rename);
    connect(ui->removeButton, &QPushButton::clicked,
            // C++11: lambda
            [this] { emit removed(this); }
            );
    connect(ui->checkbox, &QCheckBox::toggled, this, &Task::checked);
}

void Task::checked(bool checked)
{
    QFont font(ui->checkbox->font());
    font.setStrikeOut(checked);
    ui->checkbox->setFont(font);
    emit statusChanged(this);
}

bool Task::isCompleted() const
{
    return ui->checkbox->isChecked();
}

QString Task::name() const
{
    return ui->checkbox->text();
}

void Task::rename()
{
    bool ok;
    QString value = QInputDialog::getText(this, tr("Edit task"),
                                          tr("Task name"), QLineEdit::Normal,
                                          this->name(), &ok);
    if (ok && !value.isEmpty())
    {
        setName(value);
    }
}

void Task::setName(const QString &name)
{
    ui->checkbox->setText(name);
}

Task::~Task()
{
    delete ui;
}
