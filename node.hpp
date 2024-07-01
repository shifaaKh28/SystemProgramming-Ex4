//shifaakhatib28@gmail.com
#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>

/**
 * @class Node
 * @brief A class representing a node in a k-ary tree.
 *
 * This class is used to represent a node in a k-ary tree, where each node can have up to k children.
 * The node contains a key of any type T and a vector of pointers to its child nodes.
 *
 * @tparam T The type of the key stored in the node.
 */
template <typename T>
class Node {
public:
    T key;  ///< The key stored in the node.
    std::vector<std::shared_ptr<Node<T>>> children;  ///< A vector of shared pointers to the child nodes.

    /**
     * @brief Constructs a node with the given key.
     *
     * @param k The key to be stored in the node.
     */
    Node(T k) : key(k) {}

    /**
     * @brief Returns the key stored in the node.
     *
     * @return The key stored in the node.
     */
    T get_key() const;

    /**
     * @brief Adds a child node to this node.
     *
     * @param child A shared pointer to the child node to be added.
     */
    void add_child(std::shared_ptr<Node<T>> child);
};


template <typename T>
T Node<T>::get_key() const {
    return key;
}


template <typename T>
void Node<T>::add_child(std::shared_ptr<Node<T>> child) {
    children.push_back(child);
}

#endif // NODE_HPP
