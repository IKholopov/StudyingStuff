#ifndef _IGRAPH_H__
#define _IGRAPH_H__

class Edge
{
    public:
        Edge(unsigned int from, unsigned int to)
        {
            this->From = from;
            this->To = to;
        }
        virtual Edge* GetReversed()
        {
            return new Edge(To, From);
        }
        unsigned int From;
        unsigned int To;
};

class IGraph
{
    public:
        virtual ~IGraph() {};
        virtual unsigned int Size() const = 0;
        virtual unsigned int NumberOfEdges() const = 0;
        virtual std::vector<unsigned int> GetChilds(unsigned int vertex) const = 0;
        virtual std::vector<unsigned int> GetParents(unsigned int vertex) const = 0;
        virtual void ReadFromFile(std::ifstream& file) = 0;
        virtual void WriteToFile(std::ofstream& file) = 0;
        virtual void RandomizeGraph(double probability) = 0;
        virtual void AddNodes(size_t amount) = 0;
        virtual bool AddEdge(int from, int to) = 0;
        virtual bool CheckEdge(int from, int to) = 0;
        virtual Edge* GetEdge(int from, int to) = 0;
        virtual void DeleteAllEdges() = 0;
    protected:
        virtual bool AddEdge(Edge *edge) = 0;
        virtual void InitializeNewGraph(unsigned int size) = 0;
};

#endif
