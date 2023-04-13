#include <iostream>

using namespace std;

class Node{
    private:
        int value;
        Node* left;
        Node* right;
        Node* parent;
    public:
        Node(int v, Node* l, Node* r, Node* p);
        int getValue();
        Node* getLeft();
        Node* getRight();
        Node* getParent();
        void setValue(int v);
        void setLeft(Node* l);
        void setRight(Node* r);
        void setParent(Node* p);
};
Node::Node(int v, Node* l, Node* r, Node* p){
    this->value = v;
    this->left = l;
    this->right = r;
    this->parent = p;
};
int Node::getValue(){
    return value;
};
Node* Node::getLeft(){
    return left;
};
Node* Node::getRight(){
    return right;
};
Node* Node::getParent(){
    return parent;
};
void Node::setValue(int v){
    this->value = v;
};
void Node::setLeft(Node* l){
    this->left = l;
};
void Node::setRight(Node* r){
    this->right = r;
};
void Node::setParent(Node* p){
    this->parent=p;
};

class BSTree{
    private:
        Node* root;
    public:
        BSTree();                        //tworzy puste drzewo
        Node* getRoot();            //zwraca wska¿nik do root - metoda pomocnicza w testowaniu
        bool empty(Node* p);        //zwraca prawdê gdy (pod)drzewo o korzeniu p jest puste
        void inorder(Node* p);      //wyœwietla w porz¹dku inorder
        void preorder(Node* p);
        void postorder(Node* p);
    //BST
        void insert(int x);            //wstawia wêze³ z wartoœci¹ x
        Node* search(int x);         //zwraca wskaŸnik do wêz³a z wartoœci¹ x (lub NULL jeœli nie istnieje)
        Node* minimum(Node* p);            //zwraca wskaŸnik do wêz³a z minimaln¹ wartoœci¹ w (pod)drzewie p
        Node* maximum(Node* p);            //zwraca wskaŸnik do wêz³a z maksymaln¹ wartoœci¹ w (pod)drzewie p
        Node* successor(Node* p);    //zwraca wskaŸnik do nastênika p
        Node* predecessor(Node* p);    //zwraca wskaŸnik do poprzednika p
        void del(Node* p);            //usuwa wêze³ wskazywany przez p
        int size(Node* p);                  //zwraca rozmiar (pod)drzewa o korzeniu p
        int hight(Node* p);              //zwraca wysokoœæ (pod)drzewa o korzeniu p
        void clear(Node* p);           //usuwa wszystkie wêz³y z (pod)drzewa o korzeniu p
};
BSTree::BSTree(){
    root = NULL;
};
Node* BSTree::getRoot(){
    return root;
};
bool BSTree::empty(Node* p){
    if(p==NULL){
        return true;
    }
    else return false;
};
void BSTree::inorder(Node* p){
    if(!empty(p)){
        inorder(p->getLeft());
        cout << " " << p->getValue() << " ";
        inorder(p->getRight());
    }
};
void BSTree::preorder(Node* p){
    if(!empty(p)){
        cout << " " << p->getValue() << " ";
        preorder(p->getLeft());
        preorder(p->getRight());
    }
};
void BSTree::postorder(Node* p){
    if(!empty(p)){
        postorder(p->getLeft());
        postorder(p->getRight());
        cout << " " << p->getValue() << " ";
    }
};
void BSTree::insert(int x){
    //przypadek 0 - drzewo puste
    if(empty(getRoot())){
        Node* e = new Node(x, NULL,NULL,NULL);
        root = e;
    }
    //przypadek 1 - drzewo nie jest puste
    else {
        bool stop = false;
        Node* e = new Node(x, NULL, NULL, NULL);
        Node* p = root;
        while(!stop){
            if(p->getValue()>x){
                if(!empty(p->getLeft())){
                    p = p->getLeft();
                }
                else {
                    p -> setLeft(e);
                    e -> setParent(p);
                    stop = true;
                }
            }
            if(p->getValue()<x){
                if(!empty(p->getRight())){
                    p = p->getRight();
                }
                else{
                     p -> setRight(e);
                     e -> setParent(p);
                     stop = true;
                }
            }
        }
    }
};
Node* BSTree::search(int x){
    Node* n = root;
    while(!empty(n) && n->getValue() != x){
        if(n->getValue()>x){
            n = n -> getLeft();
        }
        else {
            n = n -> getRight();
        }
    }
    return n;
};
Node* BSTree::minimum(Node* p){
    if(empty(root)){
        return NULL;
    }
    else{
        Node* n = p;
        while(!empty(n->getLeft())){
            n = n -> getLeft();
        }
        return n;
    }
};
Node* BSTree::maximum(Node* p){
    if(empty(root)){
        return NULL;
    }
    else{
        Node* n = p;
        if(!empty(n -> getRight())){
            n = n -> getRight();
        }
        return n;
    }
};
Node* BSTree::successor(Node* p){
    //przypadek 0 - drzewo puste
    if(empty(root)){
        return NULL;
    }
    //istnieje prawe poddrzewo
    if(!empty(p -> getRight())){
        return minimum(p -> getRight());
    }
    //nie istnieje prawe poddrzewo
    if(empty(p->getRight())){
        Node* n = p->getParent();
        while(!empty(n)&&p==n->getRight()){
            p = n;
            n = n -> getParent();
        }
        return n;
    }
};
Node* BSTree::predecessor(Node* p){
    //przypadek 0 - drzewo puste
    if(empty(root)){
        return NULL;
    }
    //istnieje prawe poddrzewo
    if(!empty(p -> getLeft())){
        return maximum(p -> getLeft());
    }
    //nie istnieje prawe poddrzewo
    if(empty(p->getLeft())){
        Node* n = p->getParent();
        while(!empty(n)&&p==n->getLeft()){
            p = n;
            n = n -> getParent();
        }
        return n;
    }
};
void BSTree::del(Node* p){
    if(empty(p)){
        cout << "Element nie istnieje";
    }
        //Przypadek 1 p jest liœciem
    if(empty(p->getLeft()) && empty(p->getRight())){
        Node* n = p->getParent();
        if(empty(n)){
            root = NULL;
        }
        else{
            if(n->getLeft()==p){
                n->setLeft(NULL);
            }
            else{
                n->setRight(NULL);
            }
            delete p;
        }
    }
    //Przypadek 2 p nie jest liœciem i ma jednego syna
    if(empty(p->getLeft()) && !empty(p->getRight()) || !empty(p->getLeft()) && empty(p->getRight())){
        Node* r = NULL;
        if(empty(p->getLeft())){
            r = p->getRight();
        }
        else{
            r = p->getLeft();
        }
        Node* parent = p->getParent();
        if(empty(parent)){
            root = r;
        }
        else{
            if(parent->getLeft()==p){
                parent->setLeft(r);
            }else{
                parent->setRight(r);
            }
            delete p;
        }
    }
        //3 przypadek p istnieje i ma dwóch synów
    else {
        Node* succ = successor(p);
        p->setValue(succ->getValue());
        delete successor(p);
        delete succ;
    }
};
int BSTree::size(Node* p){
    if(empty(p)){
        return 0;
    }
    else {
            return (1+size(p->getLeft())+size(p->getRight()));
    }
};
int BSTree::hight(Node* p){
    if(empty(p)){
        return -1;
    }else{
        return (1+max(hight(p->getLeft()),hight(p->getRight())));
    }
}
void BSTree::clear(Node* p){
    if(!empty(p)){
        clear(p->getLeft());
        clear(p->getRight());
        delete p;
    }
};
int main(){

    cout<<endl<<"Zadanie 1 - test"<<endl;
    BSTree* t = new BSTree();
   /* t->insert(15);
    t->insert(13);
    t->insert(18);
    cout << endl << "Inorder"; t->inorder(t->getRoot());
    cout <<endl<<"Wartosc korzenia: ";
    cout << t->getRoot()->getValue();
    cout << endl << "Minimum: ";
    cout << t->minimum(t->getRoot())->getValue();
    cout << endl << "Maximum: ";
    cout << t->maximum(t->getRoot())->getValue();
    Node* namax = t->maximum(t->getRoot());
    t->insert(16);
    cout << endl << "16: " << t->getRoot()->getRight()->getLeft()->getValue();
    t->insert(100);
    cout << endl << "Maximum, po dodaniu 100: ";
    cout << t->maximum(t->getRoot())->getValue();
    cout << endl << "Search(100): ";
    cout << t->search(100);
    cout << endl << "Search(100)->getValue(): ";
    cout << t->search(100)->getValue();
    t->insert(24);
    t->insert(34);
    t->insert(19);
    Node* namin = t->successor(namax);
    cout << endl << "Succesor 18: ";
    cout << t->successor(namax)->getValue();
    cout << endl << "Predecesor 19: ";
    cout << t->predecessor(namin)->getValue();
    cout << endl << "Inorder"; t->inorder(t->getRoot());
    cout << endl << "Preorder"; t->preorder(t->getRoot());
    cout << endl << "Postorder"; t->postorder(t->getRoot());
    t->del(namax);
    cout <<endl<<"19: " <<t->getRoot()->getRight()->getValue();
    t->clear(t->getRoot()->getRight());
    cout << endl << "Postorder"; t->postorder(t->getRoot());
    cout << endl << "height(): "<< t->hight(t->getRoot());
    cout << endl << "size(): "<< t->size(t->getRoot());
    */
    t->insert(40);
    t->insert(30);
    t->insert(10);
    t->insert(35);
    t->insert(1);
    t->insert(12);
    t->insert(32);
    t->insert(37);
    t->insert(50);
    t->insert(48);
    t->insert(42);
    t->insert(49);
    t->insert(60);
    t->insert(55);
    t->insert(70);
    t->postorder(t->getRoot());
}
