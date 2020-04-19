// recursive tree network simulation

// used headers and/or libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>

// size of tree
int const N{(int)1e4};
// file name to save results
std::string const fileName{"data.txt"};

// choose a random integer from given [0, high] interval uniformly
auto ChooseNode = [](int const &high) {
    // check given parameter
    if (high <= 0 || std::abs(std::floor(high) - high) > 1e-15)
    {
        std::cout << "Invalid higher boundary for random number generation." << std::endl;
        std::exit(-1);
    }
    // generate random uniform integer
    std::random_device rd{};
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> Uni(0, high);
    return Uni(gen);
};

// addig a new node to the recursive tree
auto AddNode = [&](std::vector<int> &Nodes) {
    // randomly increase one node degree with 1
    Nodes[ChooseNode(static_cast<int>(Nodes.size()) - 1)] += 1;
    // add new node
    Nodes.push_back(1);
};

// write final graph to file
auto WriteToFile = [&](std::vector<int> const &Nodes) {
    std::ofstream data;
    data.open(fileName);
    for (int i{0}; i < N; i++)
        data << Nodes[i] << std::endl;
    data.close();
};

// main funcion
int main(int, char **)
{
    // container for nodes
    // initialization -> start from second step: two connected nodes (one edge)
    std::vector<int> Nodes(2, 1);

    // simulate node dynamics
    for (int i{2}; i < N; i++)
        AddNode(Nodes);

    // write to file final graph
    WriteToFile(Nodes);
}
