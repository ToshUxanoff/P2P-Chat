#ifndef ISSUECREATOR_H
#define ISSUECREATOR_H

#include <QDialog>
#include <QProcess>
#include <QNetworkConfigurationManager>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
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
    void WriteTokenToFile(const std::string& Token);
    QString ReadTokenFromFile();
    QString ParseToken(QString Data);
    QString GetGithubToken(const QString& Login, const QString& Pass);
      ~issuecreator();

private slots:

    void on_Send_clicked();
private:

    bool isTokenWrited = false;
    QString Token;
    QString IssueDescription;
    Ui::issuecreator *ui;
};

#endif // ISSUECREATOR_H
