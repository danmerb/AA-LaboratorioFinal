#include <iostream>
using namespace std;

enum Color {RED, BLACK};

struct Node{
    int dato;
    bool color;
    struct Node* parent;
    struct Node* izq;
    struct Node* der;
} Nodo;

class RBTree{
    private:
        Node *root;
    public:
        Node* createNode(int dato, Color nuevoColor){
            Node *t = new Node;
            t->dato = dato;
            t->izq = t->der =  t->parent = nullptr;
            t->color = nuevoColor;
            return  t;
        }

        
        void Recolorear(Node *&nodoT, Node *&T){
            Node *parent = nullptr;
            Node *grandParent = nullptr;

             while( (T != nodoT) && (T->color !=BLACK) && (T->parent->color == RED) ){
                parent = T->parent;
                grandParent = T->parent->parent;

                if(parent == grandParent ->izq){
                    Node* uncle = grandParent->der;
                    if(uncle != nullptr && uncle->color==RED){
                        grandParent->color=RED;
                        parent->color=BLACK;
                        uncle->color=BLACK;
                        T = grandParent;
                    }else{
                        if(T==parent->der){
                            rotIzq(nodoT, parent);
                            parent=T->parent;
                        }
                        rotDer(nodoT, grandParent);
                        int aux = parent->color;
                        parent->color=grandParent->color;
                        grandParent->color=aux;
                    }
                }else{
                    Node* uncle = grandParent->izq;
                    if(uncle != nullptr && uncle->color==RED){
                        grandParent->color=RED;
                        parent->color=BLACK;
                        uncle->color=BLACK;
                        T = grandParent;
                    }else{
                        if(T==parent->izq){
                            rotDer(nodoT, parent);
                            parent=T->parent;
                        }
                        rotIzq(nodoT, grandParent);
                        int aux = parent->color;
                        parent->color=grandParent->color;
                        grandParent->color=aux;
                    }
                }
            }

            root->color = BLACK;
        }

        void RecolorearInsertar(int value, Color color){
            Node *v = createNode(value, color);
            root = insert(root, v);
            Recolorear(root, v);
        }

        Node* insert(Node *nodoT, Node *R){
            if(nodoT == nullptr) return R;

            if(R->dato < nodoT->dato){
                nodoT->izq = insert(nodoT->izq , R);
                nodoT->izq->parent = nodoT;
            }
            else if(R->dato > nodoT->dato){
                nodoT->der = insert(nodoT->der,R);
                nodoT->der->parent = nodoT;
            }
            return nodoT;
        }

         void preorder(){
            preorderF(root);
        }
        void preorderF(Node* nodoT){
            if(nodoT == nullptr) {
              cout << "nil" << "-" ;
              return;  }
                cout<<nodoT->dato<<"-";
                preorderF(nodoT->izq);            
                preorderF(nodoT->der);
        }

        void rotDer(Node *&nodoT, Node *&T){

            Node *Izq = T->izq;
            T->izq = Izq -> der;

            if(T->izq != nullptr)
                T->izq->parent = T;

            Izq->parent =T->parent;

            if(T->parent == nullptr)
                nodoT = Izq;
            else if(T == T->parent->izq)
                T->parent->izq = Izq;
            else
                T->parent->der = Izq;

            Izq->der = T;
            T->parent = Izq;
        }

        void rotIzq(Node *&nodoT, Node *&T){

            Node *Der = T->der;
            T->der = Der -> izq;

            if(T->der == nullptr)
                T->der->parent = T;

            Der->parent = T->parent;

            if(T->parent!= nullptr)
                nodoT = Der;
            else if(T == T->parent->izq)
                T->parent->izq = Der;
            else
                T->parent->der = Der;

            Der->izq =T;
            T->parent = Der;
        }      





   


       

};

int main() {
    RBTree prueba{};
    prueba.RecolorearInsertar(50, BLACK);
    prueba.RecolorearInsertar(10,RED);
    prueba.RecolorearInsertar(40, BLACK);
    prueba.RecolorearInsertar(60, RED);
    prueba.RecolorearInsertar(70, BLACK);
    prueba.RecolorearInsertar(80, RED);   
    prueba.preorder();

}