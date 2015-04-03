#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <string>
#include "../../util/vec.h"

class Effect;

template<typename T>
class Node
{
private:
    T m_val;

public:
    Node();
    Node(T val);
    void setValue(T val);
    T getValue() const;
};

template<typename T>
Node<T>::Node()
{

}

template<typename T>
Node<T>::Node(T val) : m_val(val)
{

}

template<typename T>
void Node<T>::setValue(T val) {m_val = val;}

template<typename T>
T Node<T>::getValue() const {return m_val;}

template<typename T>
class NodeRef
{
private:
    Node<T>* m_node;

public:
    NodeRef(Node<T>* node);
    NodeRef();
    void connect(Node<T>* node);
    Node<T>* getNode();
    T getValue() const;
};

template<typename T>
NodeRef<T>::NodeRef() : m_node(NULL)
{

}

template<typename T>
NodeRef<T>::NodeRef(Node<T>* node) : m_node(node)
{

}

template<typename T>
void NodeRef<T>::connect(Node<T>* node)
{
    m_node = node;
}

template<typename T>
Node<T>* NodeRef<T>::getNode()
{
    return m_node;
}

template<typename T>
T NodeRef<T>::getValue() const
{
    return m_node->getValue();
}

template<typename T>
void operator>>(NodeRef<T>& in, Node<T>& out)
{
    in.connect(&out);
}

template<typename T>
void operator>>(NodeRef<T>& in, Node<T>* out)
{
    in.connect(out);
}

template<typename T>
void operator<<(Node<T>& out, T val)
{
    out.setValue(val);
}

#endif // NODE_H_INCLUDED
