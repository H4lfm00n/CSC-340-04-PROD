#include <iostream>
#include <fstream>
#include "json.hpp"
#include "binary_search_tree.h"

using json = nlohmann::json;

int main() {
    // 1) Match the very first line of your reference output
    std::cout << "Testing out global.\n" << std::endl;

    // 2) Load just TestCase1
    std::ifstream in("testCase1.json");
    json j; 
    in >> j;

    // 3) Process actions for “testCase1”
    for (auto& group : j["cacheManager"]) {
        for (auto& [caseName, actions] : group.items()) {
            std::cout << "Processing actions for: " << caseName << std::endl;
            BinarySearchTree bst;

            // Execute each action
            for (auto& act : actions) {
                auto it = act.begin();
                std::string op = it.key();
                auto  v  = it.value();

                if (op == "isEmpty") {
                    std::cout << "Tree is empty: "
                              << (bst.isEmpty() ? "Yes" : "No")
                              << std::endl;
                }
                else if (op == "add") {
                    int k = v["key"];
                    bst.addToTree(k);
                    std::cout << "Added key: " << k << std::endl;
                }
                else if (op == "remove") {
                    int k = v["key"];
                    bool ok = bst.removeNode(k);
                    std::cout << (ok ? "Removed key: " : "Failed to remove key: ")
                              << k << std::endl;
                }
                else if (op == "clear") {
                    bst.clear();
                    std::cout << "Tree cleared." << std::endl;
                }
            }

            // 4) Final summary & traversals
            std::cout << "Height of Tree is: "
                      << bst.getHeightOfTree() << std::endl;
            std::cout << "Count of Tree nodes is: "
                      << bst.getNumberOfTreeNodes() << std::endl;
            std::cout << "Listed on the next line is the Root node" << std::endl;
            bst.printNodeFromTree(bst.getRoot());
            bst.printBreadthFirst();
            bst.printDepthFirst();
            bst.printInOrder();
            bst.printPostOrder();
            bst.printPreOrder();
        }
    }

    return 0;
}
