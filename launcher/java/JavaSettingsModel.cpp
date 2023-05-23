#include "JavaSettingsModel.h"

JavaSettingsModel::JavaSettingsModel(JavaSettings& javaSettings, QObject* parent)
    : QAbstractItemModel(parent), m_javaSettings{ javaSettings }
{
    for (const auto& [majorVersion, runtimeVector] : javaSettings.m_runtimes) {
        categories.emplace(majorVersion, std::make_unique<Node>(
            Node{ Node::CategoryInfo{ majorVersion }, static_cast<int>(categories.size()), nullptr }));
        for (auto& runtime : runtimeVector) {
            categories[majorVersion]->children.emplace_back(std::make_unique<Node>(Node{
                Node::RuntimeInfo{ runtime },
                static_cast<int>(categories[majorVersion]->children.size()),
                categories[majorVersion].get(),
            }));
        }
    }

    connect(&m_javaSettings, &JavaSettings::runtimeInserted, this, [this](int major, int index, std::shared_ptr<JavaRuntime> runtime) {

    });
}

QVariant JavaSettingsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Orientation::Horizontal)
    {
        switch (section)
        {
        case Version:
            return tr("Version");
        case Name:
            return tr("Name");
        case Vendor:
            return tr("Vendor");
        case Architecture:
            return tr("Architecture");
        case Path:
            return tr("Path");
        }
    }
    return QVariant();
}

QModelIndex JavaSettingsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid() && static_cast<int>(categories.size()) > row)
    {
        return createIndex(row, column, static_cast<void *>(std::next(categories.begin(), row)->second.get()));
    }
    else
    {
        auto &parentNode = *static_cast<Node *>(parent.internalPointer());
        if (std::holds_alternative<Node::CategoryInfo>(parentNode.data) && static_cast<int>(parentNode.children.size()) > row)
        {
            return createIndex(row, column, static_cast<void *>(parentNode.children.at(row).get()));
        }
    }
    return QModelIndex();
}

QModelIndex JavaSettingsModel::parent(const QModelIndex &index) const
{
    if (index.isValid())
    {
        auto parentNode = static_cast<Node *>(index.internalPointer())->parent;
        if (parentNode != nullptr && std::holds_alternative<Node::CategoryInfo>(parentNode->data))
        {
            return createIndex(parentNode->row, 0, static_cast<void *>(parentNode));
        }
    }
    return QModelIndex();
}

int JavaSettingsModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return categories.size();
    return static_cast<Node *>(parent.internalPointer())->children.size();
}

int JavaSettingsModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 5;
    else
        return 5;
}

QVariant JavaSettingsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    auto x = static_cast<Node*>(index.internalPointer());
    if (std::holds_alternative<Node::RuntimeInfo>(x->data)) {
        auto rt = std::get<Node::RuntimeInfo>(x->data).runtime.lock();
        if (!rt)
            return QVariant();
        switch (index.column()) {
            case Version:
                return rt->version.toString();
            case Name:
                return rt->name;
            case Vendor:
                return rt->vendor;
            case Architecture:
                return rt->architecture;
            case Path:
                return rt->path;
        }
    }
    else if (std::holds_alternative<Node::CategoryInfo>(x->data))
    {
        switch (index.column()) {
            case 0:
                return tr("%1.*").arg(std::get<Node::CategoryInfo>(x->data).majorVersion);
        }
    }
    return QVariant();
}

bool JavaSettingsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    endInsertRows();
    return true;
}

bool JavaSettingsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    return true;
}