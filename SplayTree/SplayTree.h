
//
//  SplayTree.h
//  SplayTree
//
//  Created by RogerChen on 14/12/14.
//  Copyright (c) 2014年 RogerChen. All rights reserved.
//

#ifndef SplayTree_SplayTree_h
#define SplayTree_SplayTree_h

class SplayTree {
    struct Node {
        Node *parent = nullptr;
        Node *left   = nullptr;
        Node *right  = nullptr;
        int key;
        int value;
        
        Node(int k, int v) :
            key(k),
            value(v) { }
    };
    Node *root_ = nullptr;//be careful
    
private:
    void splay(Node *n) {
        while (n -> parent != nullptr && n -> parent -> parent != nullptr) {
            if (n == n -> parent -> left) {
                if (n -> parent == n -> parent -> parent -> left) {
                    rotateWithLeft(n -> parent -> parent);
                    rotateWithLeft(n -> parent);
                }
                else {
                    rotateWithLeft(n -> parent);
                    rotateWithRight(n -> parent);
                }
            }
            else { //n is rchild of its parent
                if (n -> parent == n -> parent -> parent -> right) {
                    rotateWithRight(n -> parent -> parent);
                    rotateWithRight(n -> parent);
                }
                else {
                    rotateWithRight(n -> parent);
                    rotateWithLeft(n -> parent);
                }
            }
        }
        if (n -> parent == nullptr) {
            return;
        }
        if (n == n -> parent -> left) {
            rotateWithLeft(n -> parent);
        }
        else {
            rotateWithRight(n -> parent);
        }
    }
    
    void insert(Node *n) {
        if (root_ == nullptr) {
            root_ = n;
            return;
        }
        Node *x = root_;
        Node *px = root_;
        while (x != nullptr) {
            px = x;
            if (n -> key >= x -> key) {
                x = x -> right;
            }
            else {
                x = x -> left;
            }
        }
        if (n -> key >= px -> key) {
            px -> right = n;
            px -> right -> parent = px;
        }
        else {
            px -> left = n;
            px -> left -> parent = px;
        }
    }
    
    void rotateWithLeft(Node *n) {
        Node *x = n -> left;
        if (n -> parent == nullptr) {
            root_ = x;
        }
        else if (n == n -> parent -> left) {
            n -> parent -> left = x;
        }
        else {
            n -> parent -> right = x;
        }
        x -> parent = n -> parent;
        n -> left = x -> right;
        if (x -> right != nullptr) {
            n -> left -> parent = n;
        }
        x -> right = n;
        n -> parent = x;
    }
    
    void rotateWithRight(Node *n) {
        Node *x = n -> right;
        if (n -> parent == nullptr) {
            root_ = x;
        }
        else if (n == n -> parent -> left) {
            n -> parent -> left = x;
        }
        else {
            n -> parent -> right = x;
        }
        x -> parent = n -> parent;
        n -> right = x -> left;
        if (x -> left != nullptr) {
            n -> right -> parent = n;
        }
        x -> left = n;
        n -> parent = x;
    }
    
public:
    void insert(int k, int s) {
        Node *x = new Node(k, s);
        insert(x);
    }
    
    int get(int key) {
        Node *x = root_;
        while (x != nullptr) {
            if (key > x -> key) {
                x = x -> right;
            }
            else if (key < x -> key) {
                x = x -> left;
            }
            else {
                splay(x);
                return x -> value;
            }
        }
        if (x != nullptr) {
            return x -> value;
        }
        else {
            return 0;
        }
    }
    
    Node * findMax(Node *n) {
        if (n == nullptr) {
            return n;
        }
        while (n -> right != nullptr) {
            n = n -> right;
        }
        return n;
    }
    
    Node * findMin(Node *n) {
        if (n == nullptr) {
            return n;
        }
        while (n -> left != nullptr) {
            n = n -> left;
        }
        return n;
    }
    
    void remove(int key) {
        if (root_ == nullptr) {
            return;
        }
        get(key);
        Node *left = root_ -> left;
        if (left != nullptr) {
            left -> parent = nullptr;
        }
        Node *right = root_ -> right;
        if (right != nullptr) {
            right -> parent = nullptr;
        }
        delete root_;
        if (left != nullptr) {
            Node *lmax = findMax(left);
            splay(lmax);
            root_ = lmax;
            root_ -> right = right;
            if (root_ -> right != nullptr) {
                root_ -> right -> parent = root_;
            }
        }
        else if (right != nullptr) {
            Node *rmin = findMin(right);
            splay(rmin);
            root_ = rmin;
            root_ -> left = left;
            if (root_ -> left != nullptr) {
                root_ -> left -> parent = root_;
            }
        }
    }
};

#endif
