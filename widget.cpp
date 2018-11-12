#include "widget.h"
#include "ui_widget.h"
#include "bplustree.h"

const QString ptShow = QStringLiteral("->");

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

void addTreeNode(QTreeWidgetItem* parent, const bnode<int, int>* insertNode);

template <typename ParentType>
void addTreeChild(ParentType* parent, void *child)
{
    auto item = new QTreeWidgetItem(parent);
    item->setText(0, ptShow);
    addTreeNode(item, reinterpret_cast<const bnode<int, int>*>(child));
}

void addTreeNode(QTreeWidgetItem* parent, const bnode<int, int>* insertNode)
{
    for (size_t idx = 0; idx != insertNode->keys.size(); ++idx)
    {
        if (!insertNode->leaf)
        {
            addTreeChild(parent, insertNode->children[idx]);
        }
        auto item = new QTreeWidgetItem(parent);
        item->setText(0, QString::number(insertNode->keys[idx]));
    }
    if (!insertNode->leaf)
    {
        addTreeChild(parent, insertNode->children.back());
    }
}

void Widget::createBPlusTree()
{
    bplustree<int, int, 5> tree;
    for (auto i = 0; i != 30; ++i)
    {
        tree.insert(i, new int(i));
    }

    auto root = tree.getRoot();
    for (size_t idx = 0; idx != root->keys.size(); ++idx)
    {
        if (!root->leaf)
        {
            addTreeChild(ui->treeWidget, root->children[idx]);
        }
        auto item = new QTreeWidgetItem;
        item->setText(0, QString::number(root->keys[idx]));
        ui->treeWidget->addTopLevelItem(item);
    }
    if (!root->leaf)
    {
        addTreeChild(ui->treeWidget, root->children.back());
    }

    ui->treeWidget->expandAll();
}


