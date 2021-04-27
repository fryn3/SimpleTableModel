#pragma once

#include <QAbstractTableModel>

class SimpleTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    static const QString ITEM_NAME;     // SimpleTableModel
    static const bool IS_QML_REG;
    SimpleTableModel(int rows = 5, int columns = 5, QObject *parent = nullptr);
    virtual ~SimpleTableModel() = default;
private:

    int _columnCount, _rowCount;
public:
    Q_INVOKABLE int rowCount(const QModelIndex &parent) const override;
    Q_INVOKABLE int columnCount(const QModelIndex &parent) const override;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const override;
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

