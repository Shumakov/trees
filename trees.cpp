#include <iostream>
#include <queue>

using namespace std;

class Node {
public:
    Node(int data) : data{ data } {}
    ~Node() {
        cout << "Delete Node  = " << data << endl;
    }
    int data;
    Node* left{};
    Node* right{};
    Node* parent{};

    void print() {
        cout << "Node " << data;
        if (parent)
            cout << " Parent " << parent->data;
        if (left)
            cout << " Left " << left->data;
        if (right)
            cout << " right " << right->data;

        cout << endl;
    }
};


class Tree {
    //корень
    Node* root;
    Node* add(Node*& parent, Node* node);
    //Node* search(Node* Node, int key);
    void print(Node* Node, bool detail);

    void delete_sheet(Node* z);
    void delete_one_sheet(Node* z);
    Node* min(Node* node);
    //int max_summ(Node* node);
    //void max_level(queue<Node*>&, int);

    void print3(queue<Node*>&, unsigned int counter =0 );
    void get_summ(queue<Node*>&);
public:
    Tree() : root{ nullptr } {};
    ~Tree() {};

    //печать от указанного узла (в глубину)
    void print(bool detail = false);


    //печать от указанного узла (в ширину)
    void print2();


    //печать от указанного узла (в ширину)
    void print3();


    void get_summ();

    //void max_level();


    //поиск от указанного узла
    //Node* search(int key);

    //вставка узла
    void add(Node* z);

    //удаление ветки для указанного узла,
    //0 - удаление всего дерева
    void del(Node* z = nullptr);

    //получить корень
    Node* getRoot() { return root; };

    //int max_summ();
};


//Рекурсивный обход дерева (в глубину)
void Tree::print(Node* node, bool detail) {
    if (node != 0) {
        print(node->left, detail);

        if (!detail)
            cout << node->data << " ";
        else
            node->print();

        print(node->right, detail);
    }
}

void Tree::print(bool detail) {
    print(root, detail);
    cout << endl;
}


void Tree::delete_sheet(Node* z) {
    if (z->parent->left == z)
        z->parent->left = nullptr;
    else
        z->parent->right = nullptr;
}

void Tree::delete_one_sheet(Node* z) {

    if (z->left) {
        z->left->parent = z->parent;
        if (z->parent->left == z)
            z->parent->left = z->left;
        else
            z->parent->right = z->left;
    }

    if (z->right) {
        z->right->parent = z->parent;
        if (z->parent->left == z)
            z->parent->left = z->right;
        else
            z->parent->right = z->right;
    }

}

void Tree::del(Node* z) {

    // Если удаляем лист
    if (!z->left && !z->right) {
        delete_sheet(z);
        delete z;
        return;
    }

    //Удаляем верщину с одним потомком
    if (!z->left || !z->right) {
        delete_one_sheet(z);
        delete z;
        return;
    }

    //Удаляем верщину
    Node* min_node = min(z->right);
    int d = min_node->data;
    del(min_node);
    z->data = d;
}

Node* Tree::min(Node* node) {

    //Поиск самого "левого" узла
    if (node != 0)
        while (node->left != 0)
            node = node->left;
    return node;
}

Node* Tree::add(Node*& parent, Node* z) {

    if (!parent) {
        parent = z;
        return parent;
    }

    if (z->data < parent->data) {
        parent->left = add(parent->left, z);
        parent->left->parent = parent;
    }

    //else if (z->data > parent->data){
    else if (z->data >= parent->data) {
        parent->right = add(parent->right, z);
        parent->right->parent = parent;
    }

    return  parent;
}

void Tree::add(Node* z) {
    add(root, z);
}


//обход дерева (в ширину)
void Tree::print2() {
    queue<Node*> q;
    q.push(root); // Положили в очередь корень

    while (!q.empty()) { // Выполняем пока очередь не пустая
        Node* t = q.front();// вынимаем первый элемент из очереди и выводим его на экран
        cout << t->data << "  ";
        q.pop();

        // Складываем в очередь потомков вершины, которую только-что вынули.
        if (t->left)
            q.push(t->left);
        if (t->right)
            q.push(t->right);
    }
    cout << endl;
}



void Tree::print3(queue<Node*>& q_in, unsigned int counter) {

    queue<Node*> q_out;

    /*
    static unsigned int counter{};

    Node* t = q_in.front();
    if (t == root)
        counter = 0;
    */

    cout << "Level " << counter++ <<"  ";


    while (!q_in.empty()) {
        Node* t = q_in.front();
        q_in.pop();

        cout << t->data << "\t";

        if (t->left)
            q_out.push(t->left);
        if (t->right)
            q_out.push(t->right);
    }

    cout << endl;

    if (!q_out.empty())
        print3(q_out, counter);


}



void Tree::get_summ(queue<Node*>& q_in) {

    queue<Node*> q_out;
    
    int sum{};

    while (!q_in.empty()) {
        Node* t = q_in.front();
        q_in.pop();

        cout << t->data << "\t";
        sum += t->data;

        if (t->left)
            q_out.push(t->left);
        if (t->right)
            q_out.push(t->right);
    }

    cout << "           Summ = " << sum;
    cout << endl;

    if (!q_out.empty())
        get_summ(q_out);


}

void Tree::get_summ() {
     
    queue<Node*> q;
    q.push(root);    
    get_summ(q);


}

/*На каждом уровне бинарного дерева найти максимальный элемент.*/



void Tree::print3() {

    /*
    Написать функцию, которая осуществляет послойный обход бинарного дерева,
    при котором значения вершин печатаются от уровня к уровню, начиная с корневой вершины.
    Значения вершин дерева на каждом уровне печатаются слева направо
    */

    queue<Node*> q;
    q.push(root);
    //counter = 0;
    print3(q);
    //q.pop();

}



int main(){


    Tree t;

    Node* t3 = new Node(3);

    t.add(new Node(7));
    t.add(new Node(9));
    t.add(t3);
    t.add(new Node(5));
    t.add(new Node(2));
    t.add(new Node(8));

    t.print();

    //t.del(t3);

    t.print2();

    t.print3();
    cout << endl << endl;
    t.print3();

    t.add(new Node(22));
    t.add(new Node(30));

    cout << endl << endl;
    t.print3();


    cout << endl << endl;
    t.get_summ();

    
}


/*
Домашнее задание


Реализовать базу данных ГАИ по штрафным квитанциям

с помощью бинарного дерева. Ключом будет служить

номер автомашины, значением узла — список право-

нарушений. Если квитанция добавляется в первый раз,

то в дереве появляется новый узел, а в списке данные по

правонарушению; если нет, то данные заносятся в су-

ществующий список. Необходимо также реализовать

следующие операции:

• Полная распечатка базы данных (по номерам машин

и списку правонарушений, числящихся за ними);

• Распечатка данных по заданному номеру;

• Распечатка данных по диапазону номеров.

*/
