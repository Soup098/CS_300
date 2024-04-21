

/*
* TODO:
* *fix case 3 to show prereqs
* *comment all methods, classes and structures
* *Title
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Course {// structure for the courses to be loaded into. everything after the second string in the file gets loaded onto the preReqs vector
    string Id;
    string Name;
    vector<string> preReqs;
};

struct Node {
    Course course;
    Node* left;
    Node* right;

    //default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    //initialize the Node structure with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

class BinaryTree {//Declaration of the binary tree class with private and public members
    private:

        Node* root;
        void inOrder(Node* node);
    public:
        BinaryTree();
        void InOrder();
        void Insert(const Course& course);
        Course* Search(const string& courseId);
};

BinaryTree::BinaryTree() : root(nullptr) {}//Constructor for the BinaryTree class. Initializes the root variable of the binary tree to an empty pointer

void BinaryTree::InOrder() {//Defining the InOrder public member of the BinaryTree class. this 
    inOrder(root);
}

void BinaryTree::inOrder(Node* node) {//Recursive function that performs an in order traversal of the binary tree
    if (node != nullptr) {
        inOrder(node->left);
        cout << endl;
        if (!node->course.preReqs.empty()) {// if there is anything contained in the preReqs vector, those items will be printed
            cout << "Course ID: " << node->course.Id << ", Course Name: " << node->course.Name << ", Prerequisites: ";
            for (const string& prereq : node->course.preReqs) {
                cout << prereq << " ";
            }  
        }
        else {// if nothing in vector, this else statement will execute
            cout << "Course ID: " << node->course.Id << ", Course Name: " << node->course.Name;
        }
        inOrder(node->right);
    }
    
}

void BinaryTree::Insert(const Course& course) {//Function to insert a new course into the binary tree. Called within the LoadCourses() function toinsert course into tree after loading from file
    Node* newNode = new Node(course);

    if (root == nullptr) {// if the root is empty, the course is inserted at the root.
        root = newNode;
        return;
    }

    Node* current = root;
    while (current != nullptr) {// if the root is not empty, the tree is traversed to find the correct position for the course
        if (course.Id < current->course.Id) {
            if (current->left == nullptr) {
                current->left = newNode;
                return;
            }
            current = current->left;
        }
        else {
            if (current->right == nullptr) {
                current->right = newNode;
                return;
            }
            current = current->right;
        }
    }
}

Course* BinaryTree::Search(const string& courseId) {//Function to search for a course based on the input from the user. 
    Node* current = root;// current variable set to the root of the tree
    
    while (current != nullptr) {// while the root is not empty
        if (courseId == current->course.Id) {// if current course id matches user search, return that course
            return &(current->course);
        }
        else if (courseId < current->course.Id) {//  if user input is less than current id, go left
            current = current->left;
        }
        else {
            current = current->right;//  if user input is greater than current id, go right
        }
    }
    return nullptr;// return nullptr if the course does not exist in the tree
}

void loadCourses(BinaryTree& tree, const string& filename) {//this function is responsible for loading the information from the file into the course structure.
    ifstream file(filename);
    string line;

    if (file.is_open()) {//if the file was successfully opened, perform the tasks to load the information into the course tructure.
        while (getline(file, line)) {
            Course newCourse;
            istringstream iss(line);
            string courseId;
            string courseName;
            string preReq;

            getline(iss, courseId, ',');
            newCourse.Id = courseId;
            getline(iss, courseName, ',');
            newCourse.Name = courseName;

            while (getline(iss, preReq, ',')) {
                newCourse.preReqs.push_back(preReq);
            }

            tree.Insert(newCourse);
        }
        file.close();// close the file after the operation
    }
    else {
        cerr << "file not opened" << "Course.txt" << endl;// print a message if the file fails to open.
    }
}

int main() {
    BinaryTree tree;// create new binary tree object called tree
    int choice = 0;//initiate the users choice at 0

    while (choice != 4) {// menu for user choices
        cout << endl;
        cout << "Please make a selection" << endl;
        cout << "1: Load Data Structure" << endl;
        cout << "2: Print Course List" << endl;
        cout << "3: Print Course" << endl;
        cout << "4: Exit Program" << endl;
        
        cin >> choice;

        switch (choice){
            case 1:// user choice number one loads the courses from the file into the program.
                loadCourses(tree, "Courses.txt");
                cout << endl;
                cout << "File Loaded" << endl;
                break;
            case 2: // user choice number two prints out all of the courses in the file
                tree.InOrder();
                break;
            case 3:// user choice number 3 takes the course ID as an input and outputs the course in question
            {
                string courseId;
                cout << "Enter ID for course you wish to see: ";
                cin >> courseId;
                Course* courseChoice = tree.Search(courseId);
                if (courseChoice != nullptr) {
                    cout << endl;
                    cout << "Course Found" << endl;
                    cout << "ID: " << courseChoice->Id << " " << "Name: " << courseChoice->Name << " " << endl;
                }
                else {
                    cout << "Course not found..." << endl;
                }
            }
                
            break;
            case 4: // user choice 4 outputs a farewall message and breaks the while loop, exiting the program
                cout << endl;
                cout << "Have a nice day" << endl;
                break;
        }
    }
}

