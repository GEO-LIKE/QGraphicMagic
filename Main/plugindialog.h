#ifndef PLUGINDIALOG_H
#define PLUGINDIALOG_H

#include "shapeplugininterface.h"
#include <QDialog>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QHeaderView>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QDir>
#include <QPluginLoader>
#include <QString>
class PluginDIalog : public QDialog
{
    Q_OBJECT
public:
    PluginDIalog(const QStringList &fileNames, const QString &path,
                 QWidget *parent = 0);

private:
    void findPlugins(const QString &path, const QStringList &fileNames);
    void populateTreeWidget(QObject *plugin, const QString &text);
    void addItems(QTreeWidgetItem *pluginItem, const QString interfanceName,
                  const QString &features);
    QLabel *label;
    QTreeWidget *treeWidget;
    QPushButton *okButton;
    QIcon interfaceIcon;
    QIcon featureIcon;
};

#endif // PLUGINDIALOG_H
