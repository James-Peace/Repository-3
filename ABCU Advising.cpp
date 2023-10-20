//============================================================================
// Name        : Project 2 ABCU Advising -- BinarySearchTree
// Author      : James Peace
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Adapted from Binary Search Tree Module 5 assignment
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================


// define a structure to hold course information
struct Course {
    string courseId;
    string courseName;
    vector<string> preRequisite;
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {
private:
    void addNode(Node* node, Course course);
    Node* removeNode(Node* node, string courseId);

public:
    Node* root;

    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(BinarySearchTree* tree, Node* node);
    void displayCourse(Node* node);
    void Remove(string course);
    Course Search(string courseId);

};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(BinarySearchTree* tree, Node* node) {
    // FIXME (5) Implement inserting a bid into the tree
    // if root equarl to null ptr
    if (tree->root == nullptr) {
        // root is equal to new node bid
        tree->root = node;
    }
    // else
    else {
        Node* currentNode = tree->root;
        while (currentNode != nullptr) {

            if (node->course.courseId < currentNode->course.courseId) {
                if (currentNode->left == nullptr) {
                    currentNode->left = node;
                    currentNode = nullptr;
                }
                else {
                    currentNode = currentNode->left;
                }
            }
            else {

                if (currentNode->right == nullptr) {
                    currentNode->right = node;
                    currentNode = nullptr;
                }
                else {
                    currentNode = currentNode->right;
                }
            }

        }
    }
}

/**
 * Removes nodes and deletes them
 */
void BinarySearchTree::Remove(string courseId) {
    removeNode(root, courseId);
}
Node* BinarySearchTree::removeNode(Node* node, string courseId) {
    // if no node exists
    if (!node) {
        return nullptr;
    }
    // if they match
    if (courseId == node->course.courseId) {
        // node is a leaf
        if (!node->left && !node->right) {
            return nullptr;
        }
    }
    // target is lesser than node value
    else if (courseId < node->course.courseId) {
        //search and remove node in left subtree
        node->left = removeNode(node->left, courseId);
        return node;
    }
    // target is greater than node value
    else {
        // search and remove node in right subtree
        node->right = removeNode(node->right, courseId);
        return node;
    }
}

/**
 * Search for a bid
 */
Course BinarySearchTree::Search(string courseId) {
    // set current node equal to root
    Node* currentNode = root;
    // keep looping downwards until bottom reached or matching bidId found
    while (currentNode != nullptr) {
        // if match found, return current bid
        if (currentNode->course.courseId.compare(courseId) == 0) {
            cout << currentNode->course.courseId << ", " << currentNode->course.courseName << endl;
            cout << "Prerequisites: ";
                for (string preRequisite : currentNode->course.preRequisite) {
                    if (preRequisite == currentNode->course.preRequisite.back()) {

                        cout << preRequisite << endl;
                    }
                    else {
                        cout << preRequisite << ", ";
                    }
                }
        }
        // if bid is smaller than current node then traverse left
        if (courseId.compare(currentNode->course.courseId) < 0) {
            currentNode = currentNode->left;
        }
        // else larger so traverse right
        else {
            currentNode = currentNode->right;
        }
    }
    Course course;
    return course;
}

/**
 * Add a course to some node (recursive)

 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // FIXME (8) Implement inserting a bid into the tree
    // if node is larger then add to left
    if (node->course.courseId.compare(course.courseId) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
        }
        // else recurse down the left node
        else {
            addNode(node->left, course);
        }
    }
    // else
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
        }
        //else
        else {
            // recurse down the left node
            addNode(node->right, course);
        }
    }
}

/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the bid info
 */
void BinarySearchTree::displayCourse(Node* node) {

    if (node == nullptr) {
        return;
    }
    displayCourse(node->left);
    cout << node->course.courseId << ",  " << node->course.courseName << endl;
    displayCourse(node->right);
}

/**
 * Load a file containing courses into a container
 * 
 * Will load .csv or .txt files
 */
void loadCourse(string filename, BinarySearchTree* bst) {
    ifstream file(filename);
    if (file.is_open()) {
        cout << "File loaded." << endl << "Course Schedule Available." << endl;

        int number;
        string line;
        string word;

        while (getline(file, line)) {

            number = 0;
            Node* node = new Node();
            stringstream str(line);

            while (number < 2) {
                getline(str, word, ',');
                if (number == 0) {
                    node->course.courseId = word;
                }
                else {
                    node->course.courseName = word;
                }
                number++;
            }
            while (getline(str, word, ',')) {
                node->course.preRequisite.push_back(word);
            }

            //inserts node into tree
            bst->Insert(bst, node);
        }
    }
    //file error if file not found
    else {
        cout << "File not found. " << endl;
        return;
    }
}

    /**
     * The one and only main() method
     */
int main() {
    BinarySearchTree* newTree;
    newTree = new BinarySearchTree();

    string userFile;
    string userCourse;

    int userInput = 0;

    cout << "Welcome to the course planner." << endl << endl;
    //Display menu
    while (userInput != 9) {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit." << endl << endl;
        cout << "What would you like to do? ";
        cin >> userInput;

        switch (userInput) {
            //loads file
        case 1:
            cout << endl << "Enter File Name: ";
            cin >> userFile;
            cout << endl;

            loadCourse(userFile, newTree);
            cout << endl;
            break;

            //prints courses in alphanumeric order
        case 2:
            cout << endl;
            cout << "Here is a sample schedule:" << endl << endl;
            //prints course data  	
            newTree->displayCourse(newTree->root);
            cout << endl;
            break;

            //prints user search results
        case 3:
            cout << endl;
            cout << "What course do you want to know about? ";
            cin >> userCourse;
            cout << endl;

            std::transform(userCourse.begin(), userCourse.end(), userCourse.begin(), ::toupper);
            newTree->Search(userCourse);

            cout << endl;
            break;

            //exits the program
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

            //default error output
        default:
            cout << userInput << " is not a valid option." << endl << endl;
            break;
        }
    }
}
