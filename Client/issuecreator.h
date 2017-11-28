#ifndef ISSUECREATOR_H
#define ISSUECREATOR_H

#include <QDialog>

namespace Ui {
class issuecreator;
}

class issuecreator : public QDialog
{
    Q_OBJECT

public:
    explicit issuecreator(QWidget *parent = 0);
    issuecreator(const QString& selectedText, QWidget* parent = 0);
    bool IsInternetConnected();

    ~issuecreator();

private slots:

    void on_Send_clicked();
private:
    QString IssueDescription;
    Ui::issuecreator *ui;
};

#endif // ISSUECREATOR_H
