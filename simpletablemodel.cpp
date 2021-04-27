#include "simpletablemodel.h"

#include <QColor>
#include <QDebug>

#include <QQmlEngine>

static bool registerMe() {
    // in QML file use 'import cpp.SimpleTableModel 12.34'
    qmlRegisterUncreatableType<SimpleTableModel>(
                QString("cpp.%1").arg(SimpleTableModel::ITEM_NAME).toUtf8(),
                12, 34, SimpleTableModel::ITEM_NAME.toUtf8(),
                "Not creatable as it is an enum type");
    return true;
}

const QString SimpleTableModel::ITEM_NAME = "SimpleTableModel";
const bool SimpleTableModel::IS_QML_REG = registerMe();

SimpleTableModel::SimpleTableModel(int rows, int columns, QObject *parent)
    : QAbstractTableModel(parent), _columnCount(columns), _rowCount(rows) { }

int SimpleTableModel::rowCount(const QModelIndex &/*parent*/) const {
    return _rowCount;
}

int SimpleTableModel::columnCount(const QModelIndex &/*parent*/) const {
    return _columnCount;
}

QVariant SimpleTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()
            || index.row() >= _rowCount
            || index.column() >= _columnCount) {
        return QVariant();
    }
    const QString DEFAULT_VALUE
            = "test data[%1, %2]";

    auto r = index.row();
    auto c = index.column();
    switch (role) {
    case Qt::DisplayRole:
        return DEFAULT_VALUE.arg(index.row()).arg(index.column());
    case Qt::TextAlignmentRole:
        return (1 << (index.row() % 4)) | (0x20 << index.column() % 3);
    case Qt::BackgroundRole:
        if (c == 1) {
            return QColor(0x4D, 0x5A, 0xB2, 255 * 0.4);
        } else if (c == 3) {
            return QColor(0xDC, 0xAA, 0x29);
        } else if (c == 5) {
            return QColor(0x50, 0x34, 0x34, 255 * .1);
        }
        return QColor(0x53, 0x53, 0x53, r % 2 ? 255 : 128);
    case Qt::ToolTipRole:
        return QString("Qt::ToolTipRole (%1, %2)").arg(index.row()).arg(index.column());
    default:
        qDebug() << __PRETTY_FUNCTION__ << "bad role:" << index << role;
        return QVariant();
    }
}

QVariant SimpleTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    switch (orientation) {
    case Qt::Horizontal:
        if (section < 0 || section >= _columnCount) { return QVariant(); }
        break;
    case Qt::Vertical:
        if (section < 0 || section >= _rowCount) { return QVariant(); }
        break;
    default:
        return QVariant();
    }
    const QString DEFAULT_H_VALUE = "Title%1";
    const QString DEFAULT_V_VALUE = "%1_%2";
    switch (orientation) {
    case Qt::Horizontal:
        switch (role) {
        case Qt::DisplayRole:
            return DEFAULT_H_VALUE.arg(section);
        case Qt::TextAlignmentRole:
            return (1 << (section % 4)) | (0x20 << section % 3);
        case Qt::BackgroundRole:
            return QColor(0xDA, 0x70, 0xD6, section % 2 ? 255 : 128);
        case Qt::ToolTipRole:
            return "Qt::ToolTipRole Head H";
        default:
            qDebug() << __PRETTY_FUNCTION__ << "bad role:" << role;
            return QVariant();
        }
    case Qt::Vertical:
        switch (role) {
        case Qt::DisplayRole:
            return DEFAULT_V_VALUE.arg(section).arg(QChar('a' + section % 3));
        case Qt::TextAlignmentRole:
            return (1 << (section % 4)) | (0x20 << section % 3);
        case Qt::BackgroundRole:
            return QColor(0xB8, 0x4D, 0xFF, section % 2 ? 255 : 128);
        case Qt::ToolTipRole:
            return "Qt::ToolTipRole Head V";
        default:
            qDebug() << __PRETTY_FUNCTION__ << "bad role:" << role;
            return QVariant();
        }
    default:
        return QVariant();
    }
}

