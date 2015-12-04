/*
 *    Copyright (C) 2015 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
       \brief
       @author authorname
*/







#ifndef SPECIFICWORKER_H
#define SPECIFICWORKER_H

#include <genericworker.h>
#include <innermodel/innermodel.h>
#include <myqtimer.h>
#include <qt4/QtCore/qmap.h>
#include <qt4/QtCore/qmutex.h>
#include <qt4/QtGui/qplaintextedit.h>
#include <qt4/Qt/qdebug.h>
#include <qt4/Qt/qvarlengtharray.h>
#include <listamarcas.h>
#include <lemon/list_graph.h>


using namespace lemon;

const double EulerC=std::exp(1.0);
class SpecificWorker : public GenericWorker
{
Q_OBJECT

public:
	SpecificWorker(MapPrx& mprx);	
	~SpecificWorker();
	bool setParams(RoboCompCommonBehavior::ParameterList params);
public slots:
	void compute();
	
	void reloj();
	void iniciar();
	void parar();
// 	void reset();
private:
//=====================Variables==================
	int id_tag;
	bool startbutton;	//BOTON DE STARTINICIADO
	MyQTimer clk;
	QGraphicsScene *scene;	//GRAFICOS DEL ROBOT
	enum class State  { INIT, MAPEAR, ORIENTARSE} ;  
	State st;
	int cota;
	int distsecurity;
	float threshold;
	int velmax;	//velocidad maxima del robot
	float velmaxg;
	
	
	TBaseState state;
	RoboCompLaser::TLaserData ldata;
	RoboCompLaser::TLaserData ldatacota;
	listaMarcas marcas;
	InnerModel *inner;
	ListDigraph Grafo;
	struct nodo{
		float x;
		float z;
		void set_x_z(float _x,float _z){
			x=_x;
			z=_z;
		};
		void set_x(float _x){
			x=_x;
		};
		void set_z(float _z){
			z=_z;
		};
		float get_x(){
			return x;
		}; 
		float get_z(){
			return z;
		};
		bool operator ==(const nodo &n){
			return(this->x==n.x&&this->z==n.z);
		};
		nodo& operator =(const nodo &n ){
			this->x=n.x;
			this->z=n.z;
			return *this;
		};
		float sqrt_nodo(nodo n1){
			float x = n1.x-this->x;
			float z = n1.z-this->z;
			return sqrt(x*x+z*z);
		};
	};
	ListDigraph::NodeMap<nodo> *map;
	ListDigraph::ArcMap<float> *cost;
	nodo anterior;
	
	
	

	//=====================Funciones==================  
	QVec Seleccionarobjetivo();
	void mapear();
	bool esquina();
	void accionEsquina();
	void newAprilTag(const tagsList &tags);
	void writeinfo(string _info);
	void writeinfoTag(string _info);
	void pintarRobot(nodo origen, nodo destino);
};
#endif

