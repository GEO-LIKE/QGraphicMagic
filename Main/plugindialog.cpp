#include "plugindialog.h"

PluginDIalog::PluginDIalog(const QStringList &fileNames, const QString &path, QWidget *parent)
    : QDialog(parent),
      label(new QLabel),
      treeWidget(new QTreeWidget),
      okButton(new QPushButton(tr("OK")))
{
    treeWidget->setAlternatingRowColors(false);
    treeWidget->setSelectionMode(QAbstractItemView::NoSelection);
    treeWidget->setColumnCount(1);
    treeWidget->header()->hide();

    okButton->setDefault(true);

    connect(okButton,&QPushButton::clicked,this,&PluginDIalog::close);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0,1);
    mainLayout->setColumnStretch(2,1);
    mainLayout->addWidget(label,0,0,1,3);
    mainLayout->addWidget(treeWidget,1,0,1,3);
    mainLayout->addWidget(okButton,2,1);

    setLayout(mainLayout);

    interfaceIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirOpenIcon),
                            QIcon::Normal, QIcon::On);
    interfaceIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirClosedIcon),
                            QIcon::Normal, QIcon::Off);
    featureIcon.addPixmap(style()->standardPixmap(QStyle::SP_FileIcon));

    setWindowTitle(tr("Plugin Information"));
    findPlugins(path, fileNames);

}

void PluginDIalog::findPlugins(const QString &path, const QStringList &fileNames)
{
    label->setText(tr("Plugins Found in %1").arg(QDir::toNativeSeparators(path)));

    const QDir dir(path);

//    for(auto plugin, QPluginLoader::staticInstances())
    // dynamic lib
    for(auto fileName: fileNames){
        QPluginLoader loader(dir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if(plugin)
            populateTreeWidget(plugin, fileName);
    }
}

void PluginDIalog::populateTreeWidget(QObject *plugin, const QString &text)
{
    QTreeWidgetItem *pluginItem = new QTreeWidgetItem(treeWidget);
    pluginItem->setText(0,"ShapePluginInterface");
    treeWidget->setItemExpanded(pluginItem,true);

    QFont boldFont = pluginItem->font(0);
    boldFont.setBold(true);
    pluginItem->setFont(0, boldFont);

    if(plugin){
        ShapePluginInterface *iShape = qobject_cast<ShapePluginInterface*>(plugin);
        if(iShape)
            addItems(pluginItem,text,iShape->description());
    }
}

void PluginDIalog::addItems(QTreeWidgetItem *pluginItem, const QString interfanceName, const QString &feature)
{
    QTreeWidgetItem *interfanceItem = new QTreeWidgetItem(pluginItem);
    interfanceItem->setText(0, interfanceName);
    interfanceItem->setIcon(0, interfaceIcon);

//    for(QString feature : features)
//        if(feature.endsWith("..."))
//            feature.chop(3);
        QTreeWidgetItem *featureItem = new QTreeWidgetItem(interfanceItem);
        featureItem->setText(0,feature);
        featureItem->setIcon(0, featureIcon);
}
