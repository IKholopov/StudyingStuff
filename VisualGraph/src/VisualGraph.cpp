#include "VisualGraph.h"

#include <fstream>

VisualGraph::VisualGraph(GraphScene* scene, GraphArea* view):scene(scene), view(view)
{
    idVertexCounter = 0;
    idEdgeCounter = 0;
}
VisualGraph::VisualGraph(GraphScene* scene, GraphArea* view,
                         const std::vector<std::vector<unsigned long long> >& graphData):scene(scene), view(view)
{
    unsigned long long size = 1;
    idVertexCounter = 0;
    idEdgeCounter = 0;
    for(auto e: graphData)
    {
        if(e.at(0) > size - 1)
            size = e.at(0) + 1;
        if(e.at(1) > size - 1)
            size = e.at(1) + 1;
    }
    for(unsigned long long i = 0; i < size; ++i)
        this->AddNode(QPointF(30  + rand() % 400, 30 + rand() % 300));
    for(unsigned long long i = 0; i < graphData.size(); ++i)
        this->AddEdge(graphData.at(i).at(0),graphData.at(i).at(1), graphData.at(i).at(2));
}
VisualGraph::VisualGraph(GraphScene* scene, GraphArea* view, std::string filename):scene(scene), view(view)
{
    std::ifstream stream(filename);
    unsigned long long numberOfVertices, numberOfEdges, from, to, capacity;
    stream >> numberOfVertices;
    stream >> numberOfEdges;
    idVertexCounter = 0;
    idEdgeCounter = 0;
    for(unsigned long long i = 0; i < numberOfVertices; ++i)
        this->AddNode(QPointF(30 + rand() % 400, 30 + rand() % 300));
    for(unsigned long long i = 0; i < numberOfEdges; ++i)
    {
        stream >> from;
        stream >> to;
        stream >> capacity;
        this->AddEdge(from, to, capacity);
    }
}
VisualGraph::~VisualGraph()
{
    for(auto v: verticies)
        delete v;
    for(auto e: edges)
        delete e;
}
std::vector<std::vector<unsigned long long>> VisualGraph::Clone()
{
    std::vector<std::vector<unsigned long long>> list;
    list.resize(edges.size());
    for(unsigned long long i = 0; i < edges.size(); ++i)
    {
        list[i].push_back(edges[i]->GetFrom()->GetId());
        list[i].push_back(edges[i]->GetTo()->GetId());
        list[i].push_back(edges[i]->GetCapacity());
    }
    return list;
}
void VisualGraph::AddNode(QPointF position)
{
    Vertex* v = new Vertex(idVertexCounter++, this, position);
    scene->addItem(v);
    int offsetLimit = 30;
    v->setPos(QPointF(qMin(qMax(position.x(), scene->sceneRect().left() + offsetLimit), scene->sceneRect().right() - offsetLimit),
                      qMin(qMax(position.y(), scene->sceneRect().top() + offsetLimit), scene->sceneRect().bottom() - offsetLimit)));
    verticies.push_back(v);
}
void VisualGraph::AddEdge(unsigned long long from, unsigned long long to, unsigned long long capacity)
{
    Vertex* source = NULL;
    Vertex* dest = NULL;
    for(auto v: verticies)
        if(v->GetId() == from)
        {
            source = v;
            break;
        }
    for(auto v: verticies)
        if(v->GetId() == to)
        {
            dest = v;
            break;
        }
    VisualEdge* edge = new VisualEdge(scene, idEdgeCounter++,  source, dest, capacity);
    source->AddEdge(edge);
    dest->AddEdge(edge);
    edges.push_back(edge);
}
VisualEdge* VisualGraph::GetEdge(unsigned long long id)
{
    for(auto e: edges)
        if(e->GetId() == id)
            return e;
    return NULL;
}
Vertex* VisualGraph::GetNode(unsigned long long id)
{
    for(auto v: verticies)
        if(v->GetId() == id)
            return v;
    return NULL;
}
unsigned long long VisualGraph::GetSize()
{
    return verticies.size();
}
void VisualGraph::HideEdge(unsigned long long id)
{
    GetEdge(id)->HideEdge();
}
void VisualGraph::DisplayEdge(unsigned long long id)
{
    GetEdge(id)->ShowEdge();
}
void VisualGraph::HideNode(unsigned long long id)
{
    GetNode(id)->HideNode();
}
void VisualGraph::DisplayNode(unsigned long long id)
{
    GetNode(id)->ShowNode();
}
void VisualGraph::Update()
{
    for(auto v: verticies)
        v->Update();
    for(auto e: edges)
        e->Update();
    bool moved = false;
    for(auto v: verticies)
    {
        v->UpdatePosition();
        moved |= v->advance();
    }
    nodeMoved = moved;
}
void VisualGraph::MovedGraph()
{
    nodeMoved = true;
    if(!view->GetTimerId())
        view->SetTimerId(view->startTimer(1000/100));
}
void VisualGraph::DisableGraph()
{
    for(auto v: verticies)
    {
        v->HideNode();//scene->addItem(v);
    }
    for(auto e: edges)
    {
        e->HideEdge();
    }
}
void VisualGraph::DisplayGraph()
{
    this->active = true;
    for(auto v: verticies)
    {
        if(v->GetActive())
            v->ShowNode();//scene->addItem(v);
    }
    for(auto e: edges)
    {
        if(e->GetActive())
            e->ShowEdge();
    }
}
void VisualGraph::HideGraph()
{
    this->active = false;
    for(auto e: edges)
    {
        e->GetInfo()->hide();
        e->hide();
    }
    for(auto v: verticies)
    {
        v->hide();
    }
}
void VisualGraph::SetEdgeDisplayType(int dt)
{
    for(auto e: edges)
        e->SetDisplayType(dt);
}
void VisualGraph::SetNodeDisplayType(int dt)
{
    for(auto v: verticies)
        v->SetDisplayType(dt);
}
void VisualGraph::RemoveGraph()
{
    for(auto e: edges)
    {
        scene->removeItem(e->GetInfo());
        scene->removeItem(e);
        delete e;
    }
    for(auto v: verticies)
    {
        scene->removeItem(v);
        delete v;
    }
    verticies.clear();
    edges.clear();
    this->idEdgeCounter = 0;
    this->idVertexCounter = 0;
}
void VisualGraph::Save() const
{
    std::ofstream stream("graph.gr");
    stream << verticies.size();
    stream << " ";
    stream << edges.size();
    stream << std::endl;
    for(auto e: edges)
    {
        stream << e->GetFrom()->GetId();
        stream << " ";
        stream << e->GetTo()->GetId();
        stream << " ";
        stream << e->GetCapacity();
        stream << "\n";
    }
    stream.close();

}
bool VisualGraph::IsActive() const
{
    return active;
}
bool VisualGraph::IsMoved() const
{
    return nodeMoved;
}
unsigned long long VisualGraph::Size() const
{
    return verticies.size();
}
const std::vector<Vertex*>*VisualGraph::Verticies() const
{
    return &(this->verticies);
}
GraphScene* VisualGraph::Scene()
{
    return scene;
}
GraphArea* VisualGraph::View()
{
    return view;
}
