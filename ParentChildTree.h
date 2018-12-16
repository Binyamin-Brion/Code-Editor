//
// Created by Biny Brion on 10/19/2018.
//

#ifndef PERFORMANCEMONITOR_PARENTCHILDTREE_H
#define PERFORMANCEMONITOR_PARENTCHILDTREE_H

#include <vector>

#include <QtWidgets/QTreeWidgetItem>

// Provides a hierarchical representation of the folders and their contents for file structures
// Works as binary tree, but with each node having the ability to have more than two children

class ParentChildTree
{
    friend class TestParentChildTree;

public:

    void addItem(QTreeWidgetItem *parent, QTreeWidgetItem *newItem);

    void checkRelatedEntries(QTreeWidgetItem *parent);

private:

    struct Node
    {
        Node(QTreeWidgetItem* data, Node *parent);

        void changeCheckState();

        QTreeWidgetItem *data = nullptr;
        std::vector<Node*> children;
        bool checked = false;

        Node *parent = nullptr;
    };

    // Root node does not contain any data, but its children member will hold all the data in this data structure
    // It is used as a place holder so that a known reference point for searching this data structure exists
    Node root{nullptr, nullptr};

    Node* findParentNode(Node *node, QTreeWidgetItem *parent);

    Node* findParentNode(Node *node, const QString &nodeText);

    void _checkRelatedEntries(Node *parentLocation);

};

#endif //PERFORMANCEMONITOR_PARENTCHILDTREE_H
