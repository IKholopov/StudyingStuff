#include "VisualGraph.h"
#include <QFileDialog>
#include <fstream>

VisualGraph::VisualGraph(GraphScene* scene, GraphArea* view):scene_(scene), view_(view)
{
    idVertexCounter_ = 0;
    idEdgeCounter_ = 0;
}
VisualGraph::VisualGraph(GraphScene* scene, GraphArea* view,
                         const std::vector<std::vector<unsigned long long> >& graphData):scene_(scene), view_(view)
{
    unsigned long long size = 1;
    idVertexCounter_ = 0;
    idEdgeCounter_ = 0;
    for(auto e: graphData) {
        if(e.at(0) > size - 1)
            size = e.at(0) + 1;
        if(e.at(1) > size - 1)
            size = e.at(1) + 1;
    }
    for(unsigned long long i = 0; i < size; ++i)
        this->addNode(QPointF(30  + rand() % 400, 30 + rand() % 300));
    for(unsigned long long i = 0; i < graphData.size(); ++i)
        this->addEdge(graphData.at(i).at(0),graphData.at(i).at(1), graphData.at(i).at(2));
}
VisualGraph::VisualGraph(GraphScene* scene, GraphArea* view, std::string filename):scene_(scene), view_(view)
{
    std::ifstream stream(filename);
    unsigned long long numberOfVertices, numberOfEdges, from, to, capacity;
    stream >> numberOfVertices;
    stream >> numberOfEdges;
    idVertexCounter_ = 0;
    idEdgeCounter_ = 0;
    for(unsigned long long i = 0; i < numberOfVertices; ++i)
        this->addNode(QPointF(30 + rand() % 400, 30 + rand() % 300));
    for(unsigned long long i = 0; i < numberOfEdges; ++i) {
        stream >> from;
        stream >> to;
        stream >> capacity;
        this->addEdge(from - 1, to - 1, capacity);
    }
}
VisualGraph::~VisualGraph()
{
    for(auto v: verticies_)
        delete v;
    for(auto e: edges_)
        delete e;
}
std::vector<std::vector<unsigned long long>> VisualGraph::clone()
{
    std::vector<std::vector<unsigned long long>> list;
    list.resize(edges_.size());
    for(unsigned long long i = 0; i < edges_.size(); ++i)  {
        list[i].push_back(edges_[i]->getFrom()->getId());
        list[i].push_back(edges_[i]->getTo()->getId());
        list[i].push_back(edges_[i]->getCapacity());
    }
    return list;
}
void VisualGraph::addNode(QPointF position)
{
    Vertex* v = new Vertex(idVertexCounter_++, this, position);
    scene_->addItem(v);
    int offsetLimit = 30;
    v->setPos(QPointF(qMin(qMax(position.x(), scene_->sceneRect().left() + offsetLimit), scene_->sceneRect().right() - offsetLimit),
                      qMin(qMax(position.y(), scene_->sceneRect().top() + offsetLimit), scene_->sceneRect().bottom() - offsetLimit)));
    verticies_.push_back(v);
}
void VisualGraph::addEdge(unsigned long long from, unsigned long long to, unsigned long long capacity)
{
    Vertex* source = NULL;
    Vertex* dest = NULL;
    for(auto v: verticies_)
        if(v->getId() == from) {
            source = v;
            break;
        }
    for(auto v: verticies_)
        if(v->getId() == to) {
            dest = v;
            break;
        }
    VisualEdge* edge = new VisualEdge(scene_, idEdgeCounter_++,  source, dest, capacity);
    source->addEdge(edge);
    dest->addEdge(edge);
    edges_.push_back(edge);
}
VisualEdge* VisualGraph::getEdge(unsigned long long id)
{
    for(auto e: edges_)
        if(e->getId() == id)
            return e;
    return NULL;
}
Vertex* VisualGraph::getNode(unsigned long long id)
{
    for(auto v: verticies_)
        if(v->getId() == id)
            return v;
    return NULL;
}
unsigned long long VisualGraph::getSize()
{
    return verticies_.size();
}
void VisualGraph::hideEdge(unsigned long long id)
{
    getEdge(id)->hideEdge();
}
void VisualGraph::displayEdge(unsigned long long id)
{
    getEdge(id)->showEdge();
}
void VisualGraph::hideNode(unsigned long long id)
{
    getNode(id)->hideNode();
}
void VisualGraph::displayNode(unsigned long long id)
{
    getNode(id)->showNode();
}
void VisualGraph::update()
{
    for(auto v: verticies_)
        v->update();
    for(auto e: edges_)
        e->update();
    bool moved = false;
    for(auto v: verticies_) {
        v->updatePosition();
        moved |= v->advance();
    }
    nodeMoved_ = moved;
}
void VisualGraph::movedGraph()
{
    nodeMoved_ = true;
    if(!view_->getTimerId())
        view_->setTimerId(view_->startTimer(1000/100));
}
void VisualGraph::disableGraph()
{
    for(auto v: verticies_) {
        v->hideNode();//scene->addItem(v);
    }
    for(auto e: edges_) {
        e->hideEdge();
    }
}
void VisualGraph::displayGraph()
{
    this->active_ = true;
    for(auto v: verticies_) {
        if(v->getActive())
            v->showNode();//scene->addItem(v);
    }
    for(auto e: edges_) {
        if(e->getActive())
            e->showEdge();
    }
}
void VisualGraph::hideGraph()
{
    this->active_ = false;
    for(auto e: edges_) {
        e->getInfo()->hide();
        e->hide();
    }
    for(auto v: verticies_) {
        v->hide();
    }
}
void VisualGraph::setEdgeDisplayType(int dt)
{
    for(auto e: edges_)
        e->setDisplayType(dt);
}
void VisualGraph::setNodeDisplayType(LayeredOptions dt)
{
    for(auto v: verticies_)
        v->setDisplayType(dt);
}
void VisualGraph::removeGraph()
{
    for(auto e: edges_) {
        scene_->removeItem(e->getInfo());
        scene_->removeItem(e);
        delete e;
    }
    for(auto v: verticies_) {
        scene_->removeItem(v);
        delete v;
    }
    verticies_.clear();
    edges_.clear();
    this->idEdgeCounter_ = 0;
    this->idVertexCounter_ = 0;
}
void VisualGraph::save() const
{
    QString filename = QFileDialog::getSaveFileName(this->view_, "Save Graph As",
                                                    "~/", "All Files (*);;Graph Files (*.gr)");
    if(filename.isEmpty())
        return;
    std::ofstream stream(filename.toStdString());
    stream << verticies_.size();
    stream << " ";
    stream << edges_.size();
    stream << std::endl;
    for(auto e: edges_) {
        stream << e->getFrom()->getId() + 1;
        stream << " ";
        stream << e->getTo()->getId() + 1;
        stream << " ";
        stream << e->getCapacity();
        stream << "\n";
    }
    stream.close();

}
bool VisualGraph::isActive() const
{
    return active_;
}
bool VisualGraph::isMoved() const
{
    return nodeMoved_;
}
unsigned long long VisualGraph::size() const
{
    return verticies_.size();
}
const std::vector<Vertex*>*VisualGraph::verticies() const
{
    return &(this->verticies_);
}
GraphScene* VisualGraph::scene()
{
    return scene_;
}
GraphArea* VisualGraph::view()
{
    return view_;
}
