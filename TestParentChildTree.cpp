//
// Created by Biny Brion on 10/20/2018.
//

#include <QtTest/qtestcase.h>
#include <assert.h>
#include "TestParentChildTree.h"

/* Following test cases test if the relationship between files and folders represented by ParentChildTree class are correct
 * For each test case, a hypothetical directory layout is shown, and tests determine that for each sub directory, the
 * files and number of files (and folders) are as expected. The layout of the test are:
 *
 *  1) Create a local list of items
 *  2) Create a relationship of the items using ParentChildTree
 *  3) For each directory (and sub-directory), test if the local list matches the respective level in the ParentChildTree
 */

/*
 *  testNoParent laid out like so:
 *
 *   - Root Folder
 *    |
 *    |- file1.txt
 *    |- file2.txt
 *    |- file3.txt
 *    |- file4.cpp
 */

void TestParentChildTree::testNoParent()
{

    std::vector<QString> files{"file1.txt", "file2.java", "file3.txt", "file4.cpp"};

    QList<QTreeWidgetItem*> items;

    createItemList(items, files);

    ParentChildTree parentChildTree;

    for(const auto &i : items)
    {
        parentChildTree.addItem(i->parent(), i);
    }

    checkChildren(parentChildTree, items.first(), files);
}

/*
 *  testOneParent laid out like so:
 *
 *   - Root Folder
 *   |
 *   |-Folder
 *      |
 *      |- anotherFile.txt
 *      |- main.py
 *      |- test.txt
 *   |-file2.java
 *   |- file3.txt
 *   |- file4.cpp
 */

void TestParentChildTree::testOneParent()
{
    std::vector<QString> files{"Folder", "file2.java", "file3.txt", "file4.cpp"};
    std::vector<QString> folderSubDirectory{"anotherFile.txt", "main.py", "test.txt"};

    QList<QTreeWidgetItem*> items;

    createItemList(items, files);

    createItemList(items, folderSubDirectory, items.first());

    ParentChildTree parentChildTree;

    for(const auto &i : items)
    {
        parentChildTree.addItem(i->parent(), i);
    }

    checkChildren(parentChildTree, items.first(), files);
    checkChildren(parentChildTree, findItemByName(parentChildTree, "anotherFile.txt"), folderSubDirectory);
}

/*
 *  testTwoParents laid out like so:
 *
 *  - Root
 *  |
 *  |-Folder
 *      |
 *      |-anotherFile.txt
 *      |-main.py
 *      |-test.txt
 *  |-file2.java
 *  |-Folder2
 *      |
 *      |-subFile.txt
 *      |-submain.py
 *      |-evenMore.txt
 *      |-newFile.txt
 *  |-file3.cpp
 */

void TestParentChildTree::testTwoParents()
{
    std::vector<QString> files{"Folder", "file2.java", "Folder2", "file3.cpp"};
    std::vector<QString> firstFolderSubDirectory{"anotherFile.txt", "main.py", "test.txt"};
    std::vector<QString> secondFolderSubDirectory{"subFile.txt", "submain.py", "evenMore.txt", "newFile.txt"};

    QList<QTreeWidgetItem*> items;

    createItemList(items, files);

    createItemList(items, firstFolderSubDirectory, items.first());

    createItemList(items, secondFolderSubDirectory, items[findItem(items, "Folder2")]);

    ParentChildTree parentChildTree;

    for(const auto &i : items)
    {
        parentChildTree.addItem(i->parent(), i);
    }

    checkChildren(parentChildTree, items.first(), files);

    checkChildren(parentChildTree, findItemByName(parentChildTree, "anotherFile.txt"), firstFolderSubDirectory);

    checkChildren(parentChildTree, findItemByName(parentChildTree, "evenMore.txt"), secondFolderSubDirectory);
}

/*
 *  testOneParentTwoLevels laid out like so:
 *
 *  - Root
 *  |
 *  |-Folder
 *      |
 *      |-anotherFile.txt
 *      |-AnotherFolder
 *          |-main.cs
 *          |-main.java
 *          |- ot4.txt
 *      |-test.txt
 *  |-file2.java
 *  |-Folder2
 *      |
 *      |-subFile.txt
 *      |-submain.py
 *      |-evenMore.txt
 *      |-newFile.txt
 */

void TestParentChildTree::testOneParentTwoLevels()
{
    std::vector<QString> files{"Folder", "file2.java", "Folder2", "file3.cpp"};
    std::vector<QString> firstFolderSubDirectory{"anotherFile.txt", "AnotherFolder", "test.txt"};
    std::vector<QString> secondFolderSubDirectory{"subFile.txt", "submain.py", "evenMore.txt", "newFile.txt"};

    std::vector<QString> anotherSubDirectory{"main.cs", "main.java", "ot4.txt"};

    QList<QTreeWidgetItem*> items;

    createItemList(items, files);

    createItemList(items, firstFolderSubDirectory, items.first());

    createItemList(items, secondFolderSubDirectory, items[findItem(items, "Folder2")]);

    createItemList(items, anotherSubDirectory, items[findItem(items, "AnotherFolder")]);

    ParentChildTree parentChildTree;

    for(const auto &i : items)
    {
        parentChildTree.addItem(i->parent(), i);
    }

    checkChildren(parentChildTree, items.first(), files);

    checkChildren(parentChildTree, findItemByName(parentChildTree, "anotherFile.txt"), firstFolderSubDirectory);

    checkChildren(parentChildTree, findItemByName(parentChildTree, "evenMore.txt"), secondFolderSubDirectory);

    checkChildren(parentChildTree, findItemByName(parentChildTree, "main.cs"), anotherSubDirectory);

}

/*  - Root
 *  |
 *  |-Folder
 *      |
 *      |-anotherFile.txt
 *      |-AnotherFolder
 *          |-main.cs
 *          |-main.java
 *          |- ot4.txt
 *      |-test.txt
 *  |-file2.java
 *  |-Folder2
 *      |
 *      |-subFile.txt
 *      |-submain.py
 *      |-evenMore.txt
 *      |-Folder3
 *          |
 *          |-someDay.txt
 *          |-test.java
 *          -aRan8omFile.txt
 */

void TestParentChildTree::testTwoParentsTwoLevels()
{
    std::vector<QString> files{"Folder", "file2.java", "Folder2", "file3.cpp"};
    std::vector<QString> firstFolderSubDirectory{"anotherFile.txt", "AnotherFolder", "test.txt"};
    std::vector<QString> secondFolderSubDirectory{"subFile.txt", "submain.py", "evenMore.txt", "Folder3"};

    std::vector<QString> anotherSubDirectory{"main.cs", "main.java", "ot4.txt"};
    std::vector<QString> secondSubDirectory{"someDay.txt", "test.java", "aRan8omFile.txt"};

    QList<QTreeWidgetItem*> items;

    createItemList(items, files);

    createItemList(items, firstFolderSubDirectory, items.first());

    createItemList(items, secondFolderSubDirectory, items[findItem(items, "Folder2")]);

    createItemList(items, anotherSubDirectory, items[findItem(items, "AnotherFolder")]);

    createItemList(items, secondSubDirectory, items[findItem(items, "Folder3")]);

    ParentChildTree parentChildTree;

    for(const auto &i : items)
    {
        parentChildTree.addItem(i->parent(), i);
    }

    checkChildren(parentChildTree, items.first(), files);

    checkChildren(parentChildTree, findItemByName(parentChildTree, "anotherFile.txt"), firstFolderSubDirectory);

    checkChildren(parentChildTree, findItemByName(parentChildTree, "evenMore.txt"), secondFolderSubDirectory);

    checkChildren(parentChildTree, findItemByName(parentChildTree, "main.cs"), anotherSubDirectory);

    checkChildren(parentChildTree, findItemByName(parentChildTree, "someDay.txt"), secondSubDirectory);

}

void TestParentChildTree::createItemList(QList<QTreeWidgetItem *> &items, std::vector<QString> &contentNames,
                                         QTreeWidgetItem *parent)
{
    // Add items to the list using the given names (names are those of files and directories)
    // If a parent is given to this function, then the add item has a parent of the input for parent.

    for(const auto &i : contentNames)
    {
        items.push_back(parent == nullptr ? new QTreeWidgetItem : new QTreeWidgetItem{parent});

        items.back()->setText(0, i);
    }
}

void TestParentChildTree::checkChildren(ParentChildTree &parentChildTree, QTreeWidgetItem *parent, std::vector<QString> &childrenNames)
{
    // Find the level in parentChildTree that the current sub-directory is stored

    auto parentLocation = parentChildTree.findParentNode(&parentChildTree.root, parent);

    /* Compare the parent node children size with the expected number of children, given by the length of children names
     * Remember: parentLocation returns a pointer to an element in children. To get access to the entire
     *           vector of children that must be compared, the parent node has to be accessed (think of doubly-linked list)
     *
     *   |Node: Children| <- Need this node to access all children for this sub-level     <-|
     *          ^                                                                           |
     *          |                                                                           |
     *          |Ptr to Node||Ptr to Node||Ptr to Node|                                     |
     *            ^                                                                         |
     *            |                                                                         |
     *            |Node: Children| <- But a pointer to this is returned. Have to go back to |
     *
     *  For example: In test case testTwoParentsTwoLevels, to compare all files in sub-level containing main.cs, the node
     *               representing AnotherFolder has to be accessed.
     */

    QCOMPARE(parentLocation->parent->children.size(), childrenNames.size());

    // Check that all files and folders in the sub-level match the expected names

    for(int i = 0; i < childrenNames.size(); ++i)
    {
        QCOMPARE(childrenNames[i], parentLocation->parent->children[i]->data->text(0));
    }
}

int TestParentChildTree::findItem(const QList<QTreeWidgetItem*> &items, const QString &text)
{
    // Find at what index into items the file or folder with the given name is located at

    for(int i = 0; i < items.size(); ++i)
    {
        if(items[i]->text(0) == text)
        {
            return i;
        }
    }

    assert(false && "Unable to find the requested item widget in the item list!");
}

QTreeWidgetItem* TestParentChildTree::findItemByName(ParentChildTree &parentChildTree, const QString &name)
{
    // Get a pointer to the file or folder in the ParentChildTree with the given name

    auto result = parentChildTree.findParentNode(&parentChildTree.root, name);

    if(result)
    {
        return result->data;
    }

    assert(false && "Unable to find the requested item by name!");
}


static TestParentChildTree TEST_PARENTCHILDTREE;