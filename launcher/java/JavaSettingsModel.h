#pragma once

#include "JavaRuntime.h"
#include "JavaSettings.h"

#include <QAbstractItemModel>
#include <variant>
#include <memory>

class JavaSettingsModel : public QAbstractItemModel
{
    Q_OBJECT

   public:
    explicit JavaSettingsModel(JavaSettings& javaSettings, QObject* parent = nullptr);
    //explicit JavaSettingsModel(const std::map<int, std::vector<std::shared_ptr<JavaRuntime>>> &runtimes, QObject* parent = nullptr);
    //explicit JavaSettingsModel(JavaSettings& javaSettings, QObject* parent = nullptr) : JavaSettingsModel(javaSettings.m_runtimes, parent){};

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex& parent = QModelIndex()) override;

   private:
    JavaSettings& m_javaSettings;
    //const std::map<int, std::vector<std::shared_ptr<JavaRuntime>>>& m_runtimes;
    enum Columns {
        Version,
        Name,
        Vendor,
        Architecture,
        Path,
        LastUsed
    };
    struct Node {
        struct CategoryInfo {
            int majorVersion;
        };
        struct RuntimeInfo {
            std::weak_ptr<JavaRuntime> runtime;
        };
        enum Type {
            Category,
            Runtime
        };

        std::variant<CategoryInfo, RuntimeInfo> data;
        int row;

        Node *parent;
        std::vector<std::unique_ptr<Node>> children;
    };
    std::unordered_map<int, std::unique_ptr<Node>> categories;
};
