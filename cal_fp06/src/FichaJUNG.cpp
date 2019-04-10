#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

void exercicio1();
void exercicio2();
void exercicio3();


void exercicio1()
{
    GraphViewer * gv = new GraphViewer(600, 600, true);
    gv->createWindow(600, 600);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");
    gv->addNode(0);
    gv->rearrange();
    gv->addNode(1);
    gv->rearrange();
    gv->addEdge(0, 0, 1, EdgeType::DIRECTED);
    gv->rearrange();
//    gv->removeNode(1);
    gv->rearrange();
    gv->addNode(2);
    gv->setVertexLabel(2, "This is a node");
    gv->setEdgeLabel(0, "This an edge");
    gv->setVertexColor(2, "green");
    gv->setEdgeColor(0, "yellow");
    gv->setBackground("image.png");
    gv->closeWindow();
}

void exercicio2()
{
    GraphViewer * gv = new GraphViewer(600, 600, false);
    gv->createWindow(600, 600);
    gv->addNode(0, 300, 50);
    gv->addNode(1, 318, 58);
    gv->addNode(2, 325, 75);
    gv->addNode(3, 318, 93);
    gv->addNode(4, 300, 100);
    gv->addNode(5, 282, 93);
    gv->addNode(6, 275, 75);
    gv->addNode(7, 282, 58);
    gv->addNode(8, 150, 200);
    gv->addNode(9, 300, 200);
    gv->addNode(10, 450, 200);
    gv->addNode(11, 300, 400);
    gv->addNode(12, 200, 550);
    gv->addNode(13, 400, 550);
    gv->rearrange();
    gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
    gv->addEdge(1, 1, 2, EdgeType::UNDIRECTED);
    gv->addEdge(2, 2, 3, EdgeType::UNDIRECTED);
    gv->addEdge(3, 3, 4, EdgeType::UNDIRECTED);
    gv->addEdge(4, 4, 5, EdgeType::UNDIRECTED);
    gv->addEdge(5, 5, 6, EdgeType::UNDIRECTED);
    gv->addEdge(6, 6, 7, EdgeType::UNDIRECTED);
    gv->addEdge(7, 7, 0, EdgeType::UNDIRECTED);
    gv->addEdge(8, 4, 9, EdgeType::UNDIRECTED);
    gv->addEdge(9, 9, 8, EdgeType::UNDIRECTED);
    gv->addEdge(10, 9, 10, EdgeType::UNDIRECTED);
    gv->addEdge(11, 9, 11, EdgeType::UNDIRECTED);
    gv->addEdge(12, 11, 12, EdgeType::UNDIRECTED);
    gv->addEdge(13, 11, 13, EdgeType::UNDIRECTED);
    gv->rearrange();
    sleep(1);
    gv->removeNode(12);
    gv->removeNode(13);
    gv->rearrange();
    sleep(1);
    gv->addNode(14, 250, 550);
    gv->addNode(15, 350, 550);
    gv->rearrange();
}

void exercicio3()
{

}


int main() {
//	exercicio1();

	exercicio2();
	//exercicio3();
	getchar();
	return 0;
}
