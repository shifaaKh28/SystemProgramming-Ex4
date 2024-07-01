//shifaakhatib28@gmail.com
#ifndef TREEVIEW_HPP
#define TREEVIEW_HPP

#include <SFML/Graphics.hpp>
#include "node.hpp"
#include <cmath>
#include <sstream>
#include <memory>
#include <iostream> // Added to use std::cerr and std::endl


/**
 * @class TreeView
 * @brief A class for visualizing a k-ary tree using SFML.
 *
 * This class is used to visualize a k-ary tree using the SFML graphics library.
 * It provides methods to render the tree and draw individual nodes and edges.
 *
 * @tparam T The type of the keys stored in the nodes.
 */
template <typename T>
class TreeVisualizer {
public:
    TreeVisualizer();
    void drawTree(std::shared_ptr<Node<T>> root);
    void render(std::shared_ptr<Node<T>> root);

private:
    void drawNode(sf::RenderWindow &window, std::shared_ptr<Node<T>> node, int x, int y, int hSpacing);
    sf::RenderWindow window;
    sf::Font font;

    /**
     * @brief Formats the key value for display.
     *
     * Converts the key to a string with appropriate formatting.
     *
     * @param key The key value to format.
     * @return A string representation of the key.
     */
    std::string formatKey(T key) const;
};

/**
 * @brief Constructs a TreeView object.
 *
 * Initializes the SFML window and loads the font.
 *
 * @tparam T The type of the keys stored in the nodes.
 */
template <typename T>
TreeVisualizer<T>::TreeVisualizer() {
    // Create a window with a title and dimensions
    window.create(sf::VideoMode(800, 600), "Tree Visualization");

    // Load a font from a file
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
}

/**
 * @brief Draws the tree starting from the root node.
 *
 * @tparam T The type of the keys stored in the nodes.
 * @param root The root node of the tree.
 */
template <typename T>
void TreeVisualizer<T>::drawTree(std::shared_ptr<Node<T>> root) {
    if (!root) return;

    int windowWidth = window.getSize().x;
    int windowHeight = window.getSize().y;

    // Start drawing from the root node
    drawNode(window, root, windowWidth / 2, 50, windowWidth / 4);
}

/**
 * @brief Renders the tree using SFML.
 *
 * Opens a window and continuously renders the tree until the window is closed.
 *
 * @tparam T The type of the keys stored in the nodes.
 * @param root The root node of the tree.
 */
template <typename T>
void TreeVisualizer<T>::render(std::shared_ptr<Node<T>> root) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window with a more vibrant pink background color
        window.clear(sf::Color(255, 105, 180)); // RGB values (Hot Pink)

        drawTree(root);
        window.display();
    }
}

/**
 * @brief Draws an individual node and its children.
 *
 * @tparam T The type of the keys stored in the nodes.
 * @param window The SFML window to draw on.
 * @param node The current node to draw.
 * @param x The x-coordinate to draw the node at.
 * @param y The y-coordinate to draw the node at.
 * @param hSpacing The horizontal spacing between nodes.
 */
template <typename T>
void TreeVisualizer<T>::drawNode(sf::RenderWindow &window, std::shared_ptr<Node<T>> node, int x, int y, int hSpacing) {
    if (!node) return;

    // Draw the node as a circle
    sf::CircleShape circle(50); // set radius to 50
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition(x - circle.getRadius(), y - circle.getRadius());
    window.draw(circle);

    // Draw the key of the node
    sf::Text text;
    text.setFont(font);
    text.setString(formatKey(node->get_key())); // Format the key for display
    text.setCharacterSize(18); // Adjust character size to fit inside the larger circle
    text.setFillColor(sf::Color::Black);

    // Calculate text position to center it within the circle
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(x-1, y-1); // Center text position within the circle

    window.draw(text);

    // Draw lines to the children and recursively draw them
    int childX = x - hSpacing * (node->children.size() - 1) / 2;
    int childY = y + 120; // Adjusted for larger circles

    for (auto child : node->children) {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(x, y)),
            sf::Vertex(sf::Vector2f(childX, childY))
        };
        window.draw(line, 2, sf::Lines);

        drawNode(window, child, childX, childY, hSpacing / 2);
        childX += hSpacing;
    }
}

/**
 * @brief Formats the key value for display.
 *
 * Converts the key to a string with appropriate formatting.
 *
 * @param key The key value to format.
 * @return A string representation of the key.
 */
template <typename T>
std::string TreeVisualizer<T>::formatKey(T key) const {
    std::ostringstream oss;
    oss << key;
    return oss.str();
}

#endif // TREEVIEW_HPP
