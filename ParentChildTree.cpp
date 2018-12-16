//
// Created by Biny Brion on 10/19/2018.
//

#include "ParentChildTree.h"

ParentChildTree::Node::Node(QTreeWidgetItem *data, Node *parent) : data{data}, parent{parent}
{

}

ParentChildTree::Node *ParentChildTree::findParentNode(ParentChildTree::Node *node, QTreeWidgetItem *parent)
{
    // Recursively search the data structure until the desired node is found. Search is done comparing pointers
    // (the address they are pointing to)

    for(auto &i : node->children)
    {
        if(i->data == parent)
        {
            return i;
        }

        auto recursionResult = findParentNode(i, parent);

        if(recursionResult != nullptr)
        {
            return recursionResult;
        }
    }

    return nullptr;
}

ParentChildTree::Node *ParentChildTree::findParentNode(ParentChildTree::Node *node, const QString &nodeText)
{
    // Recursively search the data structure until the desired node is found. Search is done comparing the text of each
    // node, which is the text field from the QTreeWidget *data member

    for(auto &i : node->children)
    {
        if(i->data->text(0) == nodeText)
        {
            return i;
        }

        auto recursionResult = findParentNode(i, nodeText);

        if(recursionResult != nullptr)
        {
            return recursionResult;
        }
    }

    return nullptr;
}

void ParentChildTree::Node::changeCheckState()
{
    // Alternate between check and unchecked state for each QTreeWidgetItem (checkboxes for file-directory view)
    // Note: Trying to alternative between checkedState using the QTreeWidgetItem's checkState() function for some
    //       reason does not work

    if(!checked)
    {
        data->setCheckState(0, Qt::Checked);
    }
    else
    {
        data->setCheckState(0, Qt::Unchecked);
    }

    checked = !checked;
}

void ParentChildTree::addItem(QTreeWidgetItem *parent, QTreeWidgetItem *newItem)
{
    // Find the parent of the new item, so that it can be placed in the parent's children member so that a
    // hierarchy can be formed

    auto parentLocation = findParentNode(&root, parent);

    // If a parent in the data structure was found, add it to its children. If not, then it must be a top-level file or directory
    // Therefore add to the root's children

    if(parentLocation != nullptr)
    {
        parentLocation->children.push_back(new Node{newItem, parentLocation});
    }
    else
    {
        root.children.push_back(new Node{newItem, &root});
    }
}

void ParentChildTree::checkRelatedEntries(QTreeWidgetItem *parent)
{
    // Change the checkbox state not only for the box that was clicked, but for all boxes that the clicked box (and
    // therefore QTreeWidgetItem) is a parent of (in fileA is in FolderB, then if FolderB is selected, so is fileA)

    auto parentLocation = findParentNode(&root, parent);

    // If the requested parent is not found, then it is not in the data structure and no checkboxes are changed

    if(nullptr == parentLocation)
    {
        printf("Parent Location is null! \n");

        return;
    }

    parentLocation->changeCheckState();

    // Call a function that is itself recursive to change checkboxes of all children of the parent

    _checkRelatedEntries(parentLocation);
}

void ParentChildTree::_checkRelatedEntries(Node *parentLocation)
{
    // Recursively call this function to get at all parent's children. The children's boxes are changed to that of the
    // parent, and their 'checked' variable used to flip between unchecked and checked state are updated to reflect that
    // of the parent's 'checked' variable

    for(auto &i : parentLocation->children)
    {
        i->data->setCheckState(0, parentLocation->data->checkState(0));

        i->checked = parentLocation->checked;

        _checkRelatedEntries(i);
    }
}
