#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <locale>
#include <cmath>

using namespace std;

class Node {
private:
    
public:
    string name;
    string id;
    Node* left;
    Node* right;

    Node();
    Node(string name_, string id_);
    Node(string name_, string id_, Node* left_, Node* right_);
    ~Node();
    
    Node* insert(Node* root, string name, string id);
    Node* remove(Node* root, string id);
    void searchID(Node* root, string id);
    bool searchIDBool(Node* root, string id);
    void searchName(Node* root, string name);
    void printInorder(Node* root);
    void printPreorder(Node* root);
    void printPostorder(Node* root);
    void printLevelCount(Node* root);
    Node* removeInorder(Node* root, int node);
    vector<Node*> treeVectorInOrder(Node* root, vector<Node*> &treeVector_);
    vector<Node*> treeVectorPreOrder(Node* root, vector<Node*> &treeVector_);
    vector<Node*> treeVectorPostOrder(Node* root, vector<Node*> &treeVector_);
    Node* imbalancedNode(Node* root);
    Node* balanceTree(Node* root, Node* imbalancedNode);
    int threshold(Node* root);
    
    Node* rotateL(Node* node);
    Node* rotateR(Node* node);
    Node* rotateLR(Node* node);
    Node* rotateRL(Node* node);
};

// Default constructor
Node::Node()
{
    name = "";
    id = "";
    left = NULL;
    right = NULL;
}

// Constructor with name and id
Node::Node(string name_, string id_)
{
    name = name_;
    id = id_;
    left = NULL;
    right = NULL;
}

// Constructor with all attributes
Node::Node(string name_, string id_, Node* left_, Node* right_)
{
    name = name_;
    id = id_;
    left = left_;
    right = right_;
}

// Destructor
Node::~Node()
{
    if (left != NULL)
    {
        delete left;
    }

    if (right != NULL)
    {
        delete right;
    }
}

// Insertion function
Node* Node::insert(Node* root, string name, string id)
{
    // Gets the number of digits in id
    int idLength = id.length();
    bool nameValid = true;
    bool idExist = false;

    // If id contains only digits
    for (int i = 0; i < id.size(); i++)
    {
        if (!isdigit(id[i]))
        {
            cout << "unsuccessful\n";
            return root;
        }
    }

    int idInt = stoi(id);

    // If name contains anything that's not a space or letter, it is not valid
    for (int i = 0; i < name.length(); i++)
    {
        if (!(isalpha(name[i])) && !(name[i] == ' '))
        {
            nameValid = false;
            break;
        }
    }

    // Traverse list to see if id already exists
    idExist = Node::searchIDBool(root, id);
    
    
    // If id is not 8 digits, name is not valid, or id already exists, function is unsuccessful
    if (idLength != 8 || !nameValid || idExist)
    {
        cout << "unsuccessful\n";
        return root;
    }
    
    // If tree is empty
    else if (root == NULL)
    {
        Node* newNode = new Node(name, id);
        root = newNode;
        cout << "successful\n";
        return root;
    }
    
    // If tree is not empty
    else
    {
        Node* ptr = root;
        while(true)
        {
            // If id is less than ptr id
            if (idInt < stoi(ptr->id))
            {
                // If the ptr->left is null, insert the new node there
                if (ptr->left == NULL)
                {
                    Node* newNode = new Node(name, id);
                    ptr->left = newNode;
                    cout << "successful\n";
                    break;
                }
                // Else, traverse further down the list
                else
                {
                    ptr = ptr->left;
                }
            }
            // If id is greater than ptr id
            else if (idInt > stoi(ptr->id))
            {
                // If ptr->right is null, insert the new node there
                if (ptr->right == NULL)
                {
                    Node* newNode = new Node(name, id);
                    ptr->right = newNode;
                    cout << "successful\n";
                    break;
                }
                // Else, traverse further down the list
                else
                {
                    ptr = ptr->right;
                }
            }
        }
    }

    return root;
}

// Search by ID and return boolean
bool Node::searchIDBool(Node* root, string id)
{
    string target = id;
    Node* node = root;
    bool found = false;
    
    while (node != NULL)
    {
        // If finds target id, return true
        if (node->id == target)
        {
            found = true;
            return found;
        }
        
        // If target is less than current node id, branch to left child
        else if (target < node->id)
        {
            node = node->left;
        }
        
        // If target is greater than current node id, branch to right child
        else if (target > node->id)
        {
            node = node->right;
        }
    }
    
    // If target not found, return false
    return found;
}

// Print nodes in order
void Node::printInorder(Node* root)
{
    // Create a vector of the nodes in order
    vector<Node*> treeVector;
    treeVector = Node::treeVectorInOrder(root, treeVector);
    
    // Iterate through the vector and print
    for (int i = 0; i < treeVector.size(); i++)
    {
        cout << treeVector[i]->name;

        if (i != treeVector.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "\n";
}

// Prints nodes in pre order
void Node::printPreorder(Node* root)
{
    // Create a vector of the nodes in pre order
    vector<Node*> treeVector;
    treeVector = Node::treeVectorPreOrder(root, treeVector);
    
    // Iterate through the vector and print
    for (int i = 0; i < treeVector.size(); i++)
    {
        cout << treeVector[i]->name;

        if (i != treeVector.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "\n";
}

// Prints nodes in post order
void Node::printPostorder(Node* root)
{
    // Create a vector of the nodes in post order
    vector<Node*> treeVector;
    treeVector = Node::treeVectorPostOrder(root, treeVector);
    
    // Iterate through the vector and print
    for (int i = 0; i < treeVector.size(); i++)
    {
        cout << treeVector[i]->name;

        if (i != treeVector.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "\n";
}

// Print the number of levels
void Node::printLevelCount(Node* root)
{
    // Create 2 separate queues that traverse through the left side and right side of the root
    std::queue<Node*> leftList;
    std::queue<Node*> rightList;
    
    int left = 0;
    int right = 0;
    
    // If root is not null, the level is 1
    if (root != NULL)
    {
        left = 1;
        right = 1;
    }

    // If root->left is not null, push it to the beginning of the left list and increase left height by 1
    if (root->left != NULL)
    {
        leftList.push(root->left);
        left++;
    }
    
    // If root->right is not null, push it to the beginning of the right list and increase right height by 1
    if (root->right != NULL)
    {
        rightList.push(root->right);
        right++; 
    }
    
    // Traverse through the left side of the root and calculate the left height
    while (!leftList.empty())
    {
        if ((leftList.front()->left != NULL) || (leftList.front()->right != NULL))
        {
            left++;
        }

        if (leftList.front()->left != NULL)
        {
            leftList.push(leftList.front()->left);
        }
        
        if (leftList.front()->right != NULL)
        {
            leftList.push(leftList.front()->right);
        }
        
        leftList.pop();
        
    }
    
    // Traverse through the right side of the root and calculate the right height
    while (!rightList.empty())
    {

        if ((rightList.front()->left != NULL) || (rightList.front()->right != NULL))
        {
            right++;
        }
        
        if (rightList.front()->left != NULL)
        {
            rightList.push(rightList.front()->left);
        }
        
        if (rightList.front()->right != NULL)
        {
            rightList.push(rightList.front()->right);
        }

        rightList.pop();
        
    }
    
    // If value of left height is greater than right height, print out the left height
    if (left > right)
    {
        cout << to_string(left) + "\n";
    }
    // If value of right height is greater than left height, print out the right height
    else if (right > left)
    {
        cout << to_string(right) + "\n";
    }
    // If right and left height are 0, then print out 0
    else if ((left == 0) && (right == 0))
    {
        cout << "0\n";
    }
    // If left and right height are equal, print out left height since they are the same
    else if (left == right)
    {
        cout << to_string(left) + "\n";
    }
}

// Translate the tree into a vector in order
vector<Node*> Node::treeVectorInOrder(Node* root, vector<Node*> &treeVector_)
{
    vector<Node*> treeVector = treeVector_;
    Node* ptr = root;

    // Recursively add nodes to the vector in order
    if (ptr != NULL)
    {
        treeVector = treeVectorInOrder(ptr->left, treeVector);
        treeVector.push_back(ptr);
        treeVector = treeVectorInOrder(ptr->right, treeVector);
    }

    return treeVector;
}

// Translate the tree into a vector pre order
vector<Node*> Node::treeVectorPreOrder(Node* root, vector<Node*> &treeVector_)
{
    vector<Node*> treeVector = treeVector_;
    Node* ptr = root;

    // Recursively add nodes to the vector pre order
    if (ptr != NULL)
    {
        treeVector.push_back(ptr);
        treeVector = treeVectorPreOrder(ptr->left, treeVector);
        treeVector = treeVectorPreOrder(ptr->right, treeVector);
    }

    return treeVector;
}

// Translate the tree into a vector post order
vector<Node*> Node::treeVectorPostOrder(Node* root, vector<Node*> &treeVector_)
{
    vector<Node*> treeVector = treeVector_;
    Node* ptr = root;

    // Recursively add nodes to the vector post order
    if (ptr != NULL)
    {
        treeVector = treeVectorPostOrder(ptr->left, treeVector);
        treeVector = treeVectorPostOrder(ptr->right, treeVector);
        treeVector.push_back(ptr);
    }

    return treeVector;
}

// Search by name
void Node::searchName(Node* root, string name)
{
    // Create a vector of the nodes in pre order
    vector<Node*> treeVector;
    treeVector = Node::treeVectorPreOrder(root, treeVector);
    bool found = false;

    // Traverse the vector and print out the id of nodes that have the target name
    for (int i = 0; i < treeVector.size(); i++)
    {
        if (treeVector[i]->name == name)
        {
            found = true;
            cout << treeVector[i]->id + "\n";
        }
    }

    // If no name was found, print unsuccessful
    if (!found)
    {
        cout << "unsuccessful\n";
    }
}

// Search by ID
void Node::searchID(Node* root, string id)
{
    string target = id;
    Node* node = root;
    bool found = false;
    
    while (node != NULL)
    {
        // If finds target id, print out name and exit
        if (node->id == target)
        {
            cout << node->name + "\n";
            found = true;
            return;
        }
        
        // If target is less than current node id, branch to left child
        else if (stoi(target) < stoi(node->id))
        {
            node = node->left;
        }
        
        // If target is greater than current node id, branch to right child
        else if (stoi(target) > stoi(node->id))
        {
            node = node->right;
        }
    }
    
    // If target not found, print unsuccessful
    if (!found)
    {
        cout << "unsuccessful\n";
    }
}

// Remove function
Node* Node::remove(Node* root, string id)
{
    // Call the function searchIDBool to determine of the ID exists
    bool idExist = false;
    idExist = Node::searchIDBool(root, id);

    // If id does not exist, print unsuccessful and exit
    if (!idExist)
    {
        cout << "unsuccessful\n";
        return root;
    }

    // Else if id does exist, iterate through nodes until the node with target id is found
    else if (idExist)
    {
        Node* ptr = root;
        while (ptr != NULL)
        {
            // If node with target id is found
            if (id == ptr->id)
            {
                cout << "successful\n";

                while (ptr != NULL)
                {
                    // If ptr->right isn't null, transfer the ptr->right data to the current ptr
                    if (ptr->right != NULL)
                    {
                        ptr->id = ptr->right->id;
                        ptr->name = ptr->right->name;

                        // If the ptr->right->right isn't null, set the ptr to the ptr right child because there is more info to transfer
                        if (ptr->right->right != NULL)
                        {
                            ptr = ptr->right;
                        }

                        // If ptr->right has no left and right child, set ptr->right to null to essentially delete the node
                        else if (ptr->right->left == NULL && ptr->right->right == NULL)
                        {
                            ptr->right = NULL;
                            return root;
                        }

                        // Else if ptr->right has a left child, transfer the left child info to the ptr->right
                        else if (ptr->right->left != NULL)
                        {
                            ptr->right->id = ptr->right->left->id;
                            ptr->right->name = ptr->right->left->name;
                            return root;
                        }
                    }

                    // If target delete node is at the bottom of tree
                    else if (ptr->left == NULL && ptr->right == NULL)
                    {
                        // Create a vector of the nodes in order
                        vector<Node*> treeVector;
                        treeVector = treeVectorInOrder(root, treeVector);

                        // If target id is located at the first node in order, the node's parent will set that node to null
                        if (treeVector[0]->id == id)
                        {
                            treeVector[1]->left = NULL;
                            return root;
                        }

                        // Else, traverse the vector until the node with target id is found
                        for (int i = 0; i < treeVector.size(); i++)
                        {
                            // If the node with target id is found
                            if (treeVector[i]->id == id)
                            {
                                // If the node is a right child of the parent, set the parent's right to null
                                if (treeVector[i-1]->right->id == id)
                                {
                                    treeVector[i-1]->right = NULL;
                                    return root;
                                }

                                // If the node is a left child of the parent, set the parent's left to null
                                else if (treeVector[i+1]->left->id == id)
                                {
                                    treeVector[i+1]->left = NULL;
                                    return root;
                                }
                            }
                        }

                        return root;
                    }

                    // If target delete node has one left child, transfer the left child info to the current node
                    else if (ptr->left != NULL && ptr->right == NULL)
                    {
                        ptr->id = ptr->left->id;
                        ptr->name = ptr->left->name;
                        ptr->left = NULL;
                        return root;
                    }
                }
            }

            // Else if target id is less than ptr id, set current ptr to ptr->left
            else if (stoi(id) < stoi(ptr->id))
            {
                ptr = ptr->left;
            }
            // Else if target id is greater than ptr id, set current ptr to ptr->right
            else if (stoi(id) > stoi(ptr->id))
            {
                ptr = ptr->right;
            }
        }
    }

    return root;
}

// Find the difference of height between left and right subtree of a node
int Node::threshold(Node* root)
{
    // Create a queue for the left and right side of the root to find their heights
    std::queue<Node*> leftList;
    std::queue<Node*> rightList;
    
    int left = 0;
    int right = 0;
    
    // If root is null, return 0 and end
    if (root == NULL)
    {
        return 0;
    }

    // If root left isn't null, increase left height to 1 and push it to left list
    if (root->left != NULL)
    {
        leftList.push(root->left);
        left++;
    }
    
    // If root right isn't null, increase right height to 1 and push it to right list
    if (root->right != NULL)
    {
        rightList.push(root->right);
        right++; 
    }
    
    // Continue down left list and add it's child nodes and increase height until empty
    while (!leftList.empty())
    {
        if ((leftList.front()->left != NULL) || (leftList.front()->right != NULL))
        {
            left++;
        }

        if (leftList.front()->left != NULL)
        {
            leftList.push(leftList.front()->left);
        }
        
        if (leftList.front()->right != NULL)
        {
            leftList.push(leftList.front()->right);
        }
        
        leftList.pop();
        
    }
    
    // Continue down right list and add it's child nodes and increase height until empty
    while (!rightList.empty())
    {

        if ((rightList.front()->left != NULL) || (rightList.front()->right != NULL))
        {
            right++;
        }
        
        if (rightList.front()->left != NULL)
        {
            rightList.push(rightList.front()->left);
        }
        
        if (rightList.front()->right != NULL)
        {
            rightList.push(rightList.front()->right);
        }

        rightList.pop();
        
    }
    
    // Return the difference between left and right height to calculate the nodes threshold
    return left-right;
}

// Remove the Nth node
Node* Node::removeInorder(Node* root, int node)
{
    // Create a vector of the nodes in order
    vector<Node*> treeVector;
    treeVector = treeVectorInOrder(root, treeVector);

    // If requested node in order is out of index, it is unsuccessful
    if (node >= treeVector.size())
    {
        cout << "unsuccessful\n";
        return root;
    }

    // Else, if requested node in order is valid, call the remove function to remove the node
    else
    {
        root = remove(root, treeVector[node]->id);
        return root;
    }

    return root;
}

// Find the imbalanced node
Node* Node::imbalancedNode(Node* root)
{
    std::queue<Node*> list;
    Node* imbalancedNode = NULL;

    // If root is null, return
    if (root == NULL)
    {
        return NULL;
    }
    
    // Calculate if the root is the imbalanced node
    if (abs(root->threshold(root)) > 1)
    {
        imbalancedNode = root;
    }

    list.push(root);
    
    // Traverse the list through a queue and determine the imbalanced node at the lowest level
    while (!list.empty())
    {
        if (abs(list.front()->threshold(list.front())) > 1)
        {
            imbalancedNode = list.front();
        }

        if (list.front()->left != NULL)
        {
            list.push(list.front()->left);
        }
        
        if (list.front()->right != NULL)
        {
            list.push(list.front()->right);
        }
        
        list.pop();
        
    }

    return imbalancedNode;
}

// Rotate node left
Node* Node::rotateL(Node *node)
{
    Node* root = node->right;
    Node* curr = root->left;
    
    root->left = node;
    node->right = curr;
    return root;
}

// Rotate node right
Node* Node::rotateR(Node *node)
{
    Node* root = node->left;
    Node* curr = root->right;
    
    root->right = node;
    node->left = curr;
    return root;
}

// Rotate node Left-Right
Node* Node::rotateLR(Node* node)
{
    Node* root = node;
    node->left = rotateL(root->left);
    
    root = rotateR(root);
    return root;
}

// Rotate node Right-Left
Node* Node::rotateRL(Node* node)
{
    Node* root = node;
    node->right = rotateR(root->right);
    
    root = rotateL(root);
    return root;
}

// Balance the tree
Node* Node::balanceTree(Node* root, Node* imbalancedNode)
{
    // If the imbalanced node is null, no need to balance tree and return root
    if (imbalancedNode == NULL)
    {
        return root;
    }

    // Create a vector of the nodes in order
    vector<Node*> treeVector;
    treeVector = root->treeVectorInOrder(root, treeVector);

    // If the root is imbalanced
    if (root == imbalancedNode)
    {
        // Calculate the threshold of the imbalanced node
        int threshold = 0;
        threshold = imbalancedNode->threshold(imbalancedNode);

        // If threshold is 2
        if (threshold == 2)
        {
            // Calculate the threshold of the left child
            int thresholdChild = 0;
            thresholdChild = imbalancedNode->left->threshold(imbalancedNode->left);

            // If child threshold is 1, perform right rotation
            if (thresholdChild == 1)
            {
                imbalancedNode = imbalancedNode->rotateR(imbalancedNode);
                root = imbalancedNode;
                return root;
            }

            // If child threshold is -1, perform Left-Right rotation
            else if (thresholdChild == -1)
            {
                imbalancedNode = imbalancedNode->rotateLR(imbalancedNode);
                root = imbalancedNode;
                return root;
            }
        }

        // If threshold of imbalanced node is -2
        else if (threshold == -2)
        {
            // Calculate threshold of the right child
            int thresholdChild = 0;
            thresholdChild = imbalancedNode->right->threshold(imbalancedNode->right);

            // If the child threshold is 1, perform Right-Left rotation
            if (thresholdChild == 1)
            {
                imbalancedNode = imbalancedNode->rotateRL(imbalancedNode);
                root = imbalancedNode;
                return root;
            }

            // If the child threshold is -1, perform left rotation
            else if (thresholdChild == -1)
            {
                imbalancedNode = imbalancedNode->rotateL(imbalancedNode);
                root = imbalancedNode;
                return root;
            }
        }
    }

    // If imbalanced node is not the root, traverse the vector until imbalanced node is found
    for (int i = 0; i < treeVector.size(); i++)
    {
        // If the imbalanced node is found in the vector
        if (treeVector[i] == imbalancedNode)
        {
            // Calculate the threshold of the imbalanced node
            int threshold = 0;
            threshold = imbalancedNode->threshold(imbalancedNode);

            Node* parent = NULL;
            bool parentLeftChild;

            // If the imbalanced node is a right child of the parent, set that node to parent and left child is false
            if (treeVector[i-1]->right == imbalancedNode)
            {
                parent = treeVector[i-1];
                parentLeftChild = false;
            }

            // If the imbalanced node is a left child of the parent, set that node to parent and left child to true
            else if (treeVector[i+1]->left == imbalancedNode)
            {
                parent = treeVector[i+1];
                parentLeftChild = true;
            }

            // If threshold of the imbalanced node is 2
            if (threshold == 2)
            {
                // Calculate threshold of the node's left child
                int thresholdChild = 0;
                thresholdChild = imbalancedNode->left->threshold(imbalancedNode->left);

                // If child threshold is 1
                if (thresholdChild == 1)
                {
                    // Perform right rotation and if the imbalanced node is a left child of parent, then the parent's left child is the new root of the rotation
                    imbalancedNode = imbalancedNode->rotateR(imbalancedNode);
                    if (parentLeftChild == true)
                    {
                        parent->left = imbalancedNode;
                    }

                    // Perform right rotation and if the imbalanced node is a right child of parent, then the parent's right child is the new root of the rotation
                    else if (parentLeftChild == false)
                    {
                        parent->right = imbalancedNode;
                    }
                    return root;
                }

                // If child threshold is -1
                else if (thresholdChild == -1)
                {
                    // Perform Left-Right rotation and if the imbalanced node is a left child of parent, then the parent's left child is the new root of the rotation
                    imbalancedNode = imbalancedNode->rotateLR(imbalancedNode);
                    if (parentLeftChild == true)
                    {
                        parent->left = imbalancedNode;
                    }

                    // Perform Left-Right rotation and if the imbalanced node is a right child of parent, then the parent's right child is the new root of the rotation
                    else if (parentLeftChild == false)
                    {
                        parent->right = imbalancedNode;
                    }
                    return root;
                }
            }

            // If the threshold of the imbalanced node is -2
            else if (threshold == -2)
            {
                // Calculate the threshold of the node's right child
                int thresholdChild = 0;
                thresholdChild = imbalancedNode->right->threshold(imbalancedNode->right);

                // If child threshold is 1
                if (thresholdChild == 1)
                {
                    // Perform Right-Left rotation and if the imbalanced node is a left child of parent, then the parent's left child is the new root of the rotation
                    imbalancedNode = imbalancedNode->rotateRL(imbalancedNode);
                    if (parentLeftChild == true)
                    {
                        parent->left = imbalancedNode;
                    }

                    // Perform Right-Left rotation and if the imbalanced node is a right child of parent, then the parent's right child is the new root of the rotation
                    else if (parentLeftChild == false)
                    {
                        parent->right = imbalancedNode;
                    }
                    return root;
                }

                // If child threshold is -1
                else if (thresholdChild == -1)
                {
                    // Perform left rotation and if the imbalanced node is a left child of parent, then the parent's left child is the new root of the rotation
                    imbalancedNode = imbalancedNode->rotateL(imbalancedNode);
                    if (parentLeftChild == true)
                    {
                        parent->left = imbalancedNode;
                    }

                    // Perform left rotation and if the imbalanced node is a right child of parent, then the parent's right child is the new root of the rotation
                    else if (parentLeftChild == false)
                    {
                        parent->right = imbalancedNode;
                    }
                    return root;
                }
            }
        }
    }

    return root;
}

int main()
{
    // Initial tree is empty
    Node* root = NULL;

    int numInstructions = 0;
    string cmd1 = "";
    string cmd2 = "";
    string cmd3 = "";
    string cmd4 = "";

    // Input the number of instructions
    cin >> numInstructions;

    // Loop for the number of instructions
    for (int i = 0; i < numInstructions; i++)
    {
        // First string of the command
        cin >> cmd1;

        // Print in order command
        if (cmd1 == "printInorder")
        {
            root->printInorder(root);
        }

        // Print pre order command
        else if (cmd1 == "printPreorder")
        {
            root->printPreorder(root);
        }

        // Print post order command
        else if (cmd1 == "printPostorder")
        {
            root->printPostorder(root);
        }

        // Print level count command
        else if (cmd1 == "printLevelCount")
        {
            root->printLevelCount(root);
        }

        // Search command
        else if (cmd1 == "search")
        {
            // Input 2nd part of command which is either a name or id
            cin >> cmd2;
            
            // If it's name, search by name
            if (!isdigit(cmd2[0]))
            {
                // If the name has a first and last name, add both to fullName string
                if (isalpha(cmd2[cmd2.size() - 1]))
                {
                    cin >> cmd3;
                    cmd2 = cmd2.substr(1, cmd2.size() - 1);
                    cmd3 = cmd3.substr(0, cmd3.size() - 1);
                    string fullName = cmd2 + " " + cmd3;

                    root->searchName(root, fullName);
                }

                // If there is only the first name, then get rid of the quotation marks around the string and proceed
                else 
                {
                    cmd2 = cmd2.substr(1, cmd2.size() - 2);
                
                    root->searchName(root, cmd2);
                }
            }

            // If it's number, search by id
            else if (isdigit(cmd2[0]))
            {
                root->searchID(root, cmd2);
            }
        }

        // Remove in order command
        else if (cmd1 == "removeInorder")
        {
            // Input 2nd part of command which is the desired Nth node to delete
            cin >> cmd2;

            // Remove Nth node and balance tree if necessary
            root = root->removeInorder(root, stoi(cmd2));
            Node* imbalancedNode;
            imbalancedNode = root->imbalancedNode(root);
            root = root->balanceTree(root, imbalancedNode);
        }

        // Remove command
        else if (cmd1 == "remove")
        {
            // Input 2nd part of command and input id
            cin >> cmd2;

            // Remove id and balance tree if necessary
            root = root->remove(root, cmd2);
            Node* imbalancedNode;
            imbalancedNode = root->imbalancedNode(root);
            root = root->balanceTree(root, imbalancedNode);
        }

        // Insert command
        else if (cmd1 == "insert")
        {
            // Insert 2nd and 3rd part of command, which are the name and id/last name
            cin >> cmd2;
            cin >> cmd3;

            // If there is a last name, add the first and last name together, and input the number into cmd4
            if (isalpha(cmd2[cmd2.size() - 1]))
            {
                cmd2 = cmd2.substr(1, cmd2.size() - 1);
                cmd3 = cmd3.substr(0, cmd3.size() - 1);
                string fullName = cmd2 + " " + cmd3;
                cin >> cmd4;

                // Insert node and balance tree
                root = root->insert(root, fullName, cmd4);
                Node* imbalancedNode;
                imbalancedNode = root->imbalancedNode(root);
                root = root->balanceTree(root, imbalancedNode);
            }

            // If there is only the first name, then get rid of the quotation marks around the string and proceed
            else 
            {
                cmd2 = cmd2.substr(1, cmd2.size() - 2);
                
                // Insert node and balance tree
                root = root->insert(root, cmd2, cmd3);
                Node* imbalancedNode;
                imbalancedNode = root->imbalancedNode(root);
                root = root->balanceTree(root, imbalancedNode);
            }
        }
    }

    return 0;
}

// Incorrect Cases: 9, 10, 11, 12, 14, 15 (ALL RUNTIME ERRORS)