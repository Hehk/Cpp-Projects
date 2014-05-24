#include <iostream>
#include <stdexcept>

using namespace std;

template<class T> class Tree{
private:
  struct Node_t {
    T value;
    Node_t* left;
    Node_t* right;
  };

  Node_t* top;
  int size;

  Node_t* lowestFrom(Node_t* start){
    // moves left until the the end of the tree
    while(start->left != NULL){
      start = start->left;
    }
    // returns the lowest value Node
    return start;
  };

  Node_t* greatestFrom(Node_t* start){
    // moves right until the the end of the tree
    while(start->right != NULL){
      start = start->right;
    }
    // returns the greatest value Node
    return start;
  };

public:	

  Tree() : top(NULL), size(0) {};

  void add(T value) {

    //adds a value to the tree in a place dependent upon the value

    // make the new node that will be placed
    Node_t* newNode = new Node_t;
    newNode->value = value;
    newNode->right = NULL;
    newNode->left = NULL;

    if(top == NULL){
      // sets the top if it does not exit
      top = newNode;
    } else {
      // Making current and previous node 
      // to keep track of where you are in the tree
      Node_t* curNode = top;
      Node_t* prevNode;
      bool movedRight;
      
      // Loop through the tree
      // - goes right if greater
      // - goes left if less
      do {
        prevNode = curNode;
        if (curNode->value == value) {
          return;
        } else if (curNode->value < value){
          curNode = curNode->right;
          movedRight = true;
        } else {
          curNode = curNode->left;
          movedRight = false;
        }
      } while(curNode != NULL);
      
      // Assigns the new Node
      if(movedRight){
        prevNode->right = newNode;
      } else {
        prevNode->left = newNode;
      }
    }

    // increase size of tree
    size++;
  };

  bool contains(T value) {

    // returns true - if the tree contains the value
    // returns false - for anything else

    if(top == NULL){
      // returns false because the nothing is in the tree
      return false;
    } else {
      //makes the node used to travel through the tree
      Node_t* curNode = top;

      // loops throught the tree ending when
      // - the curNode has the desired value
      // - the curNode == NULL meaning you got throught the tree
      do {
        if (curNode->value == value) {
          return true;
        } else if (curNode->value < value){
          curNode = curNode->right;
        } else if (curNode->value > value){
          curNode = curNode->left;
        }
      } while(curNode != NULL);

      // method terminates because nothing was found
      return false;
    }
  };

  void pluck(T value){

    // removes a value from the tree

    if(contains(value)){
      // declaring the variables used in the method
      Node_t* curNode = top;
      Node_t* prevNode;
      bool movedRight;
      bool prevNodeSet= false;

      // loops until you get to the node being deleted
      while(curNode->value != value) {
        // sets the prevNode to the curNode before it is changed
        prevNode = curNode;
        prevNodeSet = true;

        // moves based on comparisons between value and the curNode
        if (curNode->value < value){
          movedRight = true;
          curNode = curNode->right;
        } else {
          movedRight = false;
          curNode = curNode->left;
        }
      }

      // changes execution dependent upon position in the tree
      if(!prevNodeSet){
        // Changes execution based on the links made by the curNode
        if(curNode->right == NULL && curNode->left == NULL){
          // resets the tree to when it was constructed
          top = NULL; 
        } else if (curNode->right != NULL && curNode->left == NULL) {
          // replaces top node with new one and deletes old top
          top = curNode->right;
          delete curNode;
        } else if (curNode->right == NULL && curNode->left != NULL) {
          // replaces top node with new one and deletes old top
          top = curNode->left;
          delete curNode;
        } else {
          // finds the lowest value in the subtree
          // plucks out the lowest value node
          // replaces the curNode with the lowest value
          Node_t* lowNode = lowestFrom(curNode->left);
          T save = lowNode->value;
          pluck(lowNode->value);
          curNode->value = save;
        }
      } else {
        if(curNode->right == NULL && curNode->left == NULL){
          // change prevNode's referance and deletes curNode
          if(movedRight){
            prevNode->right = NULL;
            delete curNode;
          } else {
            prevNode->left = NULL;
            delete curNode;
          }
        } else if (curNode->right != NULL && curNode->left == NULL) {
          // change prevNode's referance and deletes curNode
          if(movedRight){
            prevNode->right = curNode->right;
            delete curNode;
          } else {
            prevNode->left = curNode->right;
            delete curNode;
          }
        } else if (curNode->right == NULL && curNode->left != NULL) {
          // change prevNode's referance and deletes curNode
          if(movedRight){
            prevNode->right = curNode->left;
            delete curNode;
          } else {
            prevNode->left = curNode->left;
            delete curNode;
          }
        } else {
          // finds the lowest value in the subtree
          // plucks out the lowest value node
          // replaces the curNode with the lowest value
          Node_t* lowNode = lowestFrom(curNode->left);
          T save = lowNode->value;
          pluck(lowNode->value);
          curNode->value = save;
        }
      }
    }

    // reduce the size of the tree
    size--;
  };


  T getGreatest(){ return greatestFrom(top)->value; };
  T getLowest() { return lowestFrom(top)->value; };
  int getSize() { return size; };
};