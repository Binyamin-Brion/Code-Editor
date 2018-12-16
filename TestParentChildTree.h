//
// Created by Biny Brion on 10/20/2018.
//

#ifndef PERFORMANCEMONITOR_TESTPARENTCHILDTREE_H
#define PERFORMANCEMONITOR_TESTPARENTCHILDTREE_H


#include <QtCore/QObject>
#include "TestSuite.h"
#include "ParentChildTree.h"

class TestParentChildTree : public TestSuite
{
    Q_OBJECT

private slots:

    // Test case with all files and no folders
    void testNoParent();

    // Test case with files and one and two folders in root directory respectively
    void testOneParent();
    void testTwoParents();

    // Test case with files and one and two folders in other folders located in root folder, respectively
    void testOneParentTwoLevels();
    void testTwoParentsTwoLevels();

    // Note: See TestParentChilderTree.cpp file for a visual explanation of how directories are laid out for test

private:

    void createItemList(QList<QTreeWidgetItem*> &items, std::vector<QString> &contentNames, QTreeWidgetItem *parent = nullptr);
    void checkChildren(ParentChildTree &parentChildTree, QTreeWidgetItem *parent, std::vector<QString> &childrenNames);

    int findItem(const QList<QTreeWidgetItem*> &items, const QString &text);
    QTreeWidgetItem* findItemByName(ParentChildTree &parentChildTree, const QString &name);
};


#endif //PERFORMANCEMONITOR_TESTPARENTCHILDTREE_H
