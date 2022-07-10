#include "NewJavaPage.h"
#include "ui_NewJavaPage.h"

#include "java/JavaSettingsModel.h"


#include "java/javaruntimemodel.h"

NewJavaPage::NewJavaPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewJavaPage)
{
    ui->setupUi(this);

    std::map<int, std::vector<std::shared_ptr<JavaRuntime>>> testData;

    // Add a JavaRuntime with major version 8 to the QHash
    testData[8].emplace_back(std::make_shared<JavaRuntime>(
        JavaRuntime{ QUuid(), "Java 8 Runtime 1", true, "java8.exe", QString("8.0.1"), "64-bit", "Oracle", QDateTime::currentDateTime(),
                     QDateTime::currentDateTime(), QDateTime::currentDateTime(), QDateTime::currentDateTime() }));
    testData[8].emplace_back(std::make_shared<JavaRuntime>(
        JavaRuntime{ QUuid(), "Java 8 Runtime 2", true, "java8.exe", QString("8.0.1"), "64-bit", "Oracle", QDateTime::currentDateTime(),
                     QDateTime::currentDateTime(), QDateTime::currentDateTime(), QDateTime::currentDateTime() }));

    // Add a JavaRuntime with major version 11 to the QHash
    testData[11].emplace_back(std::make_shared<JavaRuntime>(
        JavaRuntime{ QUuid(), "Java 11 Runtime 1", true, "java11.exe", QString("11.0.1"), "64-bit", "Oracle", QDateTime::currentDateTime(),
                     QDateTime::currentDateTime(), QDateTime::currentDateTime(), QDateTime::currentDateTime() }));
    testData[11].emplace_back(std::make_shared<JavaRuntime>(JavaRuntime{
        QUuid(), "Java 11 Runtime 2", true, "java11.exe", QStringLiteral("11.0.1"), "64-bit", "Oracle", QDateTime::currentDateTime(),
        QDateTime::currentDateTime(), QDateTime::currentDateTime(), QDateTime::currentDateTime() }));

    auto* model = new JavaSettingsModel(testData, this);
    ui->treeView->setModel(model);
}

NewJavaPage::~NewJavaPage()
{
    delete ui;
}
