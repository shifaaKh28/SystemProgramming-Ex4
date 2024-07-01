 Trees - STL, Templates, and Iterators:

```markdown
# Trees - STL, Templates, and Iterators

This project is a C++ implementation of a k-ary tree, demonstrating the use of STL, templates, and iterators. It supports various traversal methods, including pre-order, post-order, in-order, BFS, DFS, and heap traversal. The tree structure can also be visualized using the SFML (Simple and Fast Multimedia Library).

## Features

- Create k-ary trees with customizable node types.
- Support for various tree traversal methods:
  - Pre-order
  - Post-order
  - In-order (for binary trees)
  - BFS (Breadth-First Search)
  - DFS (Depth-First Search)
  - Heap traversal (for binary trees)
- Visualization of the tree structure using SFML.

## Tree Visualization Example

![Tree Visualization](file-kDYtyborZiTKSUKP3WzDGN4x)

## Dependencies

- SFML library
- C++17 or later

## Installation

1. Install the SFML library. Follow the instructions on the [SFML website](https://www.sfml-dev.org/download.php) to install it on your system.
2. Clone this repository to your local machine.
3. Navigate to the project directory.

## Building the Project

Use the provided `Makefile` to build the project. The `Makefile` includes targets for building the demo and running tests.

To build the demo and the tests, run:
```sh
make
```

To clean the build directory, run:
```sh
make clean
```

To build and run the demo executable, run:
```sh
make tree
./demo
```

To build and run the test executable, run:
```sh
make test
```

## Project Structure

### Files and Classes

#### `Demo.cpp`

- Contains the main function and demonstrates the usage of the tree class and its visualization.

#### `Tree.hpp`

- Header file for the tree class.

##### Classes and Methods

- **Tree Class**
  - `Tree()`: Constructs a tree with the given maximum number of children per node.
  - `int get_k() const`: Returns the maximum number of children per node.
  - `void add_root(const Node<T>& node)`: Adds a root node to the tree.
  - `void add_sub_node(const Node<T>& parent, const Node<T>& child)`: Adds a child node to a specified parent node.
  - `iterator begin_pre_order()`: Returns an iterator to the beginning of a pre-order traversal.
  - `iterator end_pre_order()`: Returns an iterator to the end of a pre-order traversal.
  - `iterator begin_post_order()`: Returns an iterator to the beginning of a post-order traversal.
  - `iterator end_post_order()`: Returns an iterator to the end of a post-order traversal.
  - `iterator begin_in_order()`: Returns an iterator to the beginning of an in-order traversal.
  - `iterator end_in_order()`: Returns an iterator to the end of an in-order traversal.
  - `iterator begin_bfs_scan()`: Returns an iterator to the beginning of a BFS traversal.
  - `iterator end_bfs_scan()`: Returns an iterator to the end of a BFS traversal.
  - `iterator begin_dfs_scan()`: Returns an iterator to the beginning of a DFS traversal.
  - `iterator end_dfs_scan()`: Returns an iterator to the end of a DFS traversal.
  - `void myHeap()`: Transforms the binary tree into a min-heap.
  - `iterator begin_heap()`: Returns an iterator to the beginning of the heap.
  - `iterator end_heap()`: Returns an iterator to the end of the heap.
  - `void render()`: Renders the tree using SFML.
  - `std::ostream& operator<<(std::ostream& os, Tree<T, K>& tree)`: Overload the stream insertion operator to launch the GUI for tree visualization.

#### `Node.hpp`

- Header file for the node class.

##### Classes and Methods

- **Node Class**
  - `Node(const T& key)`: Constructs a node with the given key.
  - `T get_key() const`: Returns the key of the node.
  - `void add_child(const std::shared_ptr<Node<T>>& child)`: Adds a child to the node.

#### `TreeVisualizer.hpp`

- Header file for the tree visualization class.

##### Classes and Methods

- **TreeVisualizer Class**
  - `TreeVisualizer()`: Constructor for the TreeVisualizer class.
  - `void render(std::shared_ptr<Node<T>> root)`: Renders the tree starting from the root node.
  - `void drawTree(std::shared_ptr<Node<T>> node)`: Draws the tree recursively.

#### `complex.hpp` and `complex.cpp`

- Implementation of the `Complex` class used in the demo.

##### Classes and Methods

- **Complex Class**
  - `Complex(double re, double im)`: Constructs a complex number with the given real and imaginary parts.
  - `double get_real() const`: Returns the real part of the complex number.
  - `double get_imag() const`: Returns the imaginary part of the complex number.
  - `bool operator<(const Complex& other) const`: Less-than comparison operator for complex numbers.
  - `bool operator>(const Complex& other) const`: Greater-than comparison operator for complex numbers.
  - `std::ostream& operator<<(std::ostream& os, const Complex& c)`: Overload the stream insertion operator to print complex numbers.

#### `test.cpp`

- Contains test cases for the tree operations using the Doctest framework.

##### Test Cases

- Tests for adding nodes and traversing a tree with integer values.
- Tests for adding nodes and traversing a tree with complex numbers.
- Tests for adding nodes and traversing a tree with string values.
- Tests for invalid operations on the tree, such as adding a child to a non-existent parent.

## Graphical User Interface (GUI)

The tree visualization part of the project uses SFML to render the tree structure. The `TreeVisualizer` class is responsible for the graphical representation of the tree. It provides methods to draw the tree and render it in a window.

### TreeVisualizer Class

- `TreeVisualizer()`: Initializes the visualizer.
- `void render(std::shared_ptr<Node<T>> root)`: Sets up the window and starts the drawing process from the root node.
- `void drawTree(std::shared_ptr<Node<T>> node)`: Recursively draws the tree nodes and edges.

The GUI provides a visual representation of the tree, making it easier to understand the structure and relationships between nodes.