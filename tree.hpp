//shifaakhatib28@gmail.com
#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include "TreeVisualizer.hpp"
#include <vector>
#include <queue>
#include <stack>
#include <stdexcept>
#include <algorithm> // For heap transformations
#include <iostream>  // For logging errors
#include "string.h"


/**
 * @class Tree
 * @brief A class representing a k-ary tree.
 *
 * This class is used to represent a k-ary tree, where each node can have up to K children.
 * The tree contains nodes of any type T. By default, it represents a binary tree.
 *
 * @tparam T The type of the keys stored in the nodes.
 * @tparam K The maximum number of children per node. Default is 2 (binary tree).
 */
template <typename T, int K = 2>
class Tree {
private:
    std::shared_ptr<Node<T>> root; ///< Shared pointer to the root node of the tree.
    int k; ///< Maximum number of children per node.
    bool isBinaryTree; ///< Flag indicating if the tree is binary.

    // Vectors to store the nodes in the order of traversal
    std::vector<std::shared_ptr<Node<T>>> bfs_nodes; ///< Nodes in BFS traversal.
    std::vector<std::shared_ptr<Node<T>>> dfs_nodes; ///< Nodes in DFS traversal.
    std::vector<std::shared_ptr<Node<T>>> preOrder_nodes; ///< Nodes in pre-order traversal.
    std::vector<std::shared_ptr<Node<T>>> post_order_nodes; ///< Nodes in post-order traversal.
    std::vector<std::shared_ptr<Node<T>>> inOrder_nodes; ///< Nodes in in-order traversal.
    std::vector<std::shared_ptr<Node<T>>> heap_nodes; ///< Nodes in heap order.

    /**
     * @brief Recursively performs pre-order traversal and stores the nodes.
     *
     * @param node The current node in the traversal.
     */
    void pre_order_traversal(std::shared_ptr<Node<T>> node) {
        if (!node) return;
        preOrder_nodes.push_back(node); // Store the current node in pre-order vector
        for (auto child : node->children) { // Iterate over each child node
            pre_order_traversal(child); // Recursively perform pre-order traversal on the child nodes
        }
    }

    /**
     * @brief Recursively performs post-order traversal and stores the nodes.
     *
     * @param node The current node in the traversal.
     */
    void post_order_traversal(std::shared_ptr<Node<T>> node) {
        if (!node) return;
        for (auto child : node->children) { // Iterate over each child node
            post_order_traversal(child); // Recursively perform post-order traversal on the child nodes
        }
        post_order_nodes.push_back(node); // Store the current node in post-order vector
    }

    /**
     * @brief Recursively performs in-order traversal and stores the nodes.
     *
     * @param node The current node in the traversal.
     */
    void in_order_traversal(std::shared_ptr<Node<T>> node) {
        if (!node || K != 2) return; // Check if the node is null or if the tree is not binary
        if (!node->children.empty()) { // Check if the node has any children
            in_order_traversal(node->children[0]); // Recursively perform in-order traversal on the left child
        }
        inOrder_nodes.push_back(node); // Store the current node in in-order vector
        if (node->children.size() > 1) { // Check if the node has more than one child
            in_order_traversal(node->children[1]); // Recursively perform in-order traversal on the right child
        }
    }

    /**
     * @brief Performs BFS traversal and stores the nodes.
     *
     * @param node The starting node for the traversal.
     */
    void bfs_traversal(std::shared_ptr<Node<T>> node) {
        if (!node) return;
        std::queue<std::shared_ptr<Node<T>>> q;
        q.push(node); // Push the starting node to the queue
        while (!q.empty()) {
            std::shared_ptr<Node<T>> current = q.front();
            q.pop(); // Remove the node from the queue
            bfs_nodes.push_back(current); // Store the current node in BFS vector
            for (auto child : current->children) { // Iterate over each child node
                q.push(child); // Push the child node to the queue
            }
        }
    }

    /**
     * @brief Performs DFS traversal and stores the nodes.
     *
     * @param node The starting node for the traversal.
     */
    void dfs_traversal(std::shared_ptr<Node<T>> node) {
        if (!node) return;
        std::stack<std::shared_ptr<Node<T>>> s;
        s.push(node); // Push the starting node to the stack
        while (!s.empty()) {
            std::shared_ptr<Node<T>> current = s.top();
            s.pop(); // Remove the node from the stack
            dfs_nodes.push_back(current); // Store the current node in DFS vector
            for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) { // Iterate over each child node in reverse order
                s.push(*it); // Push the child node to the stack
            }
        }
    }

public:
    /**
     * @brief Constructs a tree with the given maximum number of children per node.
     */
    Tree() : root(nullptr), k(K), isBinaryTree(K == 2) {}

    /**
     * @brief Returns the maximum number of children per node.
     *
     * @return The maximum number of children per node.
     */
    int get_k() const {
        return k;
    }

    /**
     * @brief Adds a root node to the tree.
     *
     * @param node The node to be added as the root.
     * @throws std::runtime_error If the root node already exists.
     */
    void add_root(const Node<T>& node) {
        if (root == nullptr) {
            root = std::make_shared<Node<T>>(node.get_key());
        } else {
            throw std::runtime_error("Root node already exists. Updating the root's key.");
        }
    }

    /**
     * @brief Adds a child node to a specified parent node.
     *
     * @param parent The parent node.
     * @param child The child node to be added.
     * @throws std::runtime_error If the parent node is not found or if the parent node has reached the maximum number of children.
     */
    void add_sub_node(const Node<T>& parent, const Node<T>& child) {
    // Check if the root node is null
    if (root == nullptr) {
        throw std::runtime_error("Root node not found. Please add a root node before adding sub-nodes."); // Throw an exception if the root node is not found
    }

    std::queue<std::shared_ptr<Node<T>>> q; // Create a queue to perform BFS
    q.push(root); // Push the root node to the queue

    std::shared_ptr<Node<T>> parent_ptr = nullptr; // Initialize the parent pointer to null

    // Perform BFS to find the parent node
    while (!q.empty()) {
        std::shared_ptr<Node<T>> node = q.front(); // Get the front node from the queue
        q.pop(); // Remove the front node from the queue

        // Check if the current node's key matches the parent's key
        if (node->get_key() == parent.get_key()) {
            parent_ptr = node; // Set the parent pointer to the current node
            break; // Break the loop as the parent node is found
        }

        // Iterate over each child node and push them to the queue
        for (auto& child_node : node->children) {
            q.push(child_node);
        }
    }

    // Check if the parent node was found
    if (parent_ptr == nullptr) {
        throw std::runtime_error("Parent node not found. Cannot add the child node."); // Throw an exception if the parent node is not found
    }

    // Check if the parent node has reached the maximum number of children
    if (parent_ptr->children.size() >= static_cast<size_t>(k)) {
        throw std::runtime_error("Parent node has reached the maximum number of children."); // Throw an exception if the parent node has reached the maximum number of children
    }

    // Add the child node to the parent node
    parent_ptr->add_child(std::make_shared<Node<T>>(child));
}

    /**
     * @class iterator
     * @brief An iterator for traversing the tree.
     */
    class iterator {
    private:
        typename std::vector<std::shared_ptr<Node<T>>>::iterator it; ///< Underlying iterator for the vector.

    public:
        /**
         * @brief Constructs an iterator with the given vector iterator.
         *
         * @param iter The vector iterator to be used.
         */
        iterator(typename std::vector<std::shared_ptr<Node<T>>>::iterator iter) : it(iter) {}

        /**
         * @brief Increments the iterator.
         *
         * @return A reference to the incremented iterator.
         */
        iterator& operator++() {
            ++it;
            return *this;
        }

        /**
         * @brief Compares two iterators for inequality.
         *
         * @param other The other iterator to compare to.
         * @return True if the iterators are not equal, false otherwise.
         */
        bool operator!=(const iterator& other) const {
            return it != other.it;
        }

        /**
         * @brief Dereferences the iterator to access the node.
         *
         * @return A reference to the node.
         */
        Node<T>& operator*() const {
            return **it;
        }

        /**
         * @brief Accesses the node pointed to by the iterator.
         *
         * @return A pointer to the node.
         */
        Node<T>* operator->() const {
            return it->get();
        }
    };

    /**
     * @brief Returns an iterator to the beginning of a pre-order traversal.
     *
     * @return An iterator to the beginning of a pre-order traversal.
     */
    iterator begin_pre_order() {
        preOrder_nodes.clear();
        pre_order_traversal(root);
        return iterator(preOrder_nodes.begin());
    }

    /**
     * @brief Returns an iterator to the end of a pre-order traversal.
     *
     * @return An iterator to the end of a pre-order traversal.
     */
    iterator end_pre_order() {
        return iterator(preOrder_nodes.end());
    }

    /**
     * @brief Returns an iterator to the beginning of a post-order traversal.
     *
     * @return An iterator to the beginning of a post-order traversal.
     */
    iterator begin_post_order() {
        post_order_nodes.clear();
        post_order_traversal(root);
        return iterator(post_order_nodes.begin());
    }

    /**
     * @brief Returns an iterator to the end of a post-order traversal.
     *
     * @return An iterator to the end of a post-order traversal.
     */
    iterator end_post_order() {
        return iterator(post_order_nodes.end());
    }

    /**
     * @brief Returns an iterator to the beginning of an in-order traversal.
     *
     * @return An iterator to the beginning of an in-order traversal.
     */
    iterator begin_in_order() {
        inOrder_nodes.clear();
        in_order_traversal(root);
        return iterator(inOrder_nodes.begin());
    }

    /**
     * @brief Returns an iterator to the end of an in-order traversal.
     *
     * @return An iterator to the end of an in-order traversal.
     */
    iterator end_in_order() {
        return iterator(inOrder_nodes.end());
    }

    /**
     * @brief Returns an iterator to the beginning of a BFS traversal.
     *
     * @return An iterator to the beginning of a BFS traversal.
     */
    iterator begin_bfs_scan() {
        bfs_nodes.clear();
        bfs_traversal(root);
        return iterator(bfs_nodes.begin());
    }

    /**
     * @brief Returns an iterator to the end of a BFS traversal.
     *
     * @return An iterator to the end of a BFS traversal.
     */
    iterator end_bfs_scan() {
        return iterator(bfs_nodes.end());
    }

    /**
     * @brief Returns an iterator to the beginning of a DFS traversal.
     *
     * @return An iterator to the beginning of a DFS traversal.
     */
    iterator begin_dfs_scan() {
        dfs_nodes.clear();
        dfs_traversal(root);
        return iterator(dfs_nodes.begin());
    }

    /**
     * @brief Returns an iterator to the end of a DFS traversal.
     *
     * @return An iterator to the end of a DFS traversal.
     */
    iterator end_dfs_scan() {
        return iterator(dfs_nodes.end());
    }

/**
 * @brief Transforms the binary tree into a min-heap.
 *
 * This method converts the tree into a min-heap, where each parent node is less than or equal to its children.
 * It supports only binary trees (k = 2). The tree is traversed and its nodes are stored in a vector, which is then
 * transformed into a heap. The tree is rebuilt based on the heap order.
 *
 * @throws std::runtime_error If the tree is not binary (k != 2).
 */
void myHeap() {
    // Check if the tree is binary
    if (K != 2) {
        throw std::runtime_error("Heap transformation is only supported for binary trees.");
    }

    // Clear the heap_nodes vector
    heap_nodes.clear();

    // Traverse the tree and store its nodes in a vector
    std::queue<std::shared_ptr<Node<T>>> q;
    if (root) q.push(root);
    while (!q.empty()) {
        std::shared_ptr<Node<T>> current = q.front();
        q.pop();
        heap_nodes.push_back(current);
        for (auto child : current->children) {
            q.push(child);
        }
    }

    // Define a comparison function for min-heap
    auto compare = [](std::shared_ptr<Node<T>> a, std::shared_ptr<Node<T>> b) {
         return a->key < b->key;
          };

    // Transform the vector into a heap
    std::make_heap(heap_nodes.begin(), heap_nodes.end(), compare);

    // Sort the heap to maintain heap property
    std::sort_heap(heap_nodes.begin(), heap_nodes.end(), compare);

    // Rebuild the tree as a min-heap
    for (size_t i = 0; i < heap_nodes.size(); ++i) {
        heap_nodes[i]->children.clear(); // Clear existing children
        size_t left_index = 2 * i + 1;   // Index of the left child in the heap
        size_t right_index = 2 * i + 2;  // Index of the right child in the heap
        if (left_index < heap_nodes.size()) {
            heap_nodes[i]->children.push_back(heap_nodes[left_index]);
        }
        if (right_index < heap_nodes.size()) {
            heap_nodes[i]->children.push_back(heap_nodes[right_index]);
        }
    }

    // Set the root to the first element of the heap
    root = heap_nodes.empty() ? nullptr : heap_nodes[0];
}


/**
 * @brief Returns an iterator to the beginning of the heap.
 *
 * This method first transforms the tree into a heap and then returns an iterator
 * to the beginning of the heap.
 *
 * @return An iterator to the beginning of the heap.
 */
iterator begin_heap() {
    myHeap(); // Transform the tree into a heap
    return iterator(heap_nodes.begin()); // Return an iterator to the beginning of the heap
}

/**
 * @brief Returns an iterator to the end of the heap.
 *
 * This method returns an iterator to the end of the heap.
 *
 * @return An iterator to the end of the heap.
 */
iterator end_heap() {
    return iterator(heap_nodes.end()); // Return an iterator to the end of the heap
}

    /**
     * @brief Renders the tree using SFML.
     */
    void render() {
        TreeVisualizer<T> t;
        t.render(root);
    }

    /**
     * @brief Overload the stream insertion operator to launch the GUI for tree visualization.
     *
     * @param os Output stream.
     * @param tree Tree object to visualize.
     * @return Output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, Tree<T, K>& tree) {
        tree.render();
        return os;
    }
};

#endif // TREE_HPP
