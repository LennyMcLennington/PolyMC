#ifndef NEWJAVAPAGE_H
#define NEWJAVAPAGE_H

#include <QWidget>
#include <ui/pages/BasePage.h>
#include <Application.h>

namespace Ui {
class NewJavaPage;
}

class NewJavaPage : public QWidget, public BasePage
{
    Q_OBJECT

   public:
    explicit NewJavaPage(QWidget *parent = nullptr);
    ~NewJavaPage();

   private:
    Ui::NewJavaPage *ui;





   public:
    QString displayName() const override
    {
        return tr("Java");
    }
    QIcon icon() const override
    {
        return APPLICATION->getThemedIcon("java");
    }
    QString id() const override
    {
        return "new-java-settings";
    }
    QString helpPage() const override
    {
        return "Java-settings";
    }
};

#endif // NEWJAVAPAGE_H
