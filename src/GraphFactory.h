#ifndef GRAPHFACTORY_H
#define GRAPHFACTORY_H

class IGraphLoader;

class GraphFactory
{
public:
    static GraphFactory* getInstance();
    void getGraphFromFile(const std::string& , Graph<int>**);

private:
    GraphFactory();
    static GraphFactory *instance;
};

#endif
