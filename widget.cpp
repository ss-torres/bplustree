#include "widget.h"
#include "ui_widget.h"
#include "bplustree.h"

const QString ptShow = QStringLiteral("#");

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    createBPlusTree();
}

Widget::~Widget()
{
    delete ui;
}

void addTreeNode(QTreeWidgetItem* parent, const bnode<int, int>* insertNode)
{
    for (size_t idx = 0; idx != insertNode->keys.size(); ++idx)
    {
        if (!insertNode->leaf)
        {
            auto item = new QTreeWidgetItem(parent);
            item->setText(0, ptShow);
            addTreeNode(item, reinterpret_cast<bnode<int,int>*>(insertNode->children[idx]));
        }
        auto item = new QTreeWidgetItem(parent);
        item->setText(0, QString::number(insertNode->keys[idx]));
    }
    if (!insertNode->leaf)
    {
        auto item = new QTreeWidgetItem(parent);
        item->setText(0, ptShow);
        addTreeNode(item, reinterpret_cast<bnode<int, int>*>(insertNode->children.back()));
    }
}

void Widget::createBPlusTree()
{
    bplustree<int, int, 5> tree;
    for (auto i = 0; i != 12; ++i)
    {
        tree.insert(i, new int(i));
    }

    auto root = tree.getRoot();
    for (size_t idx = 0; idx != root->keys.size(); ++idx)
    {
        if (!root->leaf)
        {
            auto item = new QTreeWidgetItem;
            item->setText(0, ptShow);
            addTreeNode(item, reinterpret_cast<bnode<int, int>*>(root->children[idx]));
            ui->treeWidget->addTopLevelItem(item);
        }
        auto item = new QTreeWidgetItem;
        item->setText(0, QString::number(root->keys[idx]));
        ui->treeWidget->addTopLevelItem(item);
    }
    if (!root->leaf)
    {
        auto item = new QTreeWidgetItem;
        item->setText(0, ptShow);
        addTreeNode(item, reinterpret_cast<bnode<int, int>*>(root->children.back()));
        ui->treeWidget->addTopLevelItem(item);
    }

    ui->treeWidget->expandAll();
}


