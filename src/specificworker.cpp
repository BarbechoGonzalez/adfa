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


#include "specificworker.h"
#include <qt4/Qt/qlocale.h>
#include <qt4/Qt/qvarlengtharray.h>
static float sentido=M_PI;
/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(MapPrx& mprx) : GenericWorker(mprx)
{
	connect(Start, SIGNAL(clicked()), this, SLOT(iniciar()));
	connect(Stop, SIGNAL(clicked()), this, SLOT(parar()));
// 	connect(Reset, SIGNAL(clicked()), this, SLOT(reset()));
	connect(&clk, SIGNAL(senal()), this, SLOT(reloj()));
	
	clk.setseg(1000);
	scene =  new QGraphicsScene();
	Grafico->setScene(scene);
	startbutton=false;
	clk.start();
	st=State::INIT;
	id_tag=0;
	cota = 16;
	distsecurity = 440;
	threshold = 400;
	velmax=270;	//velocidad maxima del robot
	velmaxg=1.5;
	inner = new InnerModel("/home/ivan/robocomp/files/innermodel/simpleworld.xml");
// 	inner = new InnerModel("/home/ivan/robocomp/files/innermodel/RoCKIn@home/world/apartment.xml");
	map = new ListDigraph::NodeMap<nodo>(Grafo);
	cost = new ListDigraph::ArcMap<float>(Grafo);
	differentialrobot_proxy->getBaseState(state);
	anterior.set_x_z(state.x,state.z);
	ListDigraph::Node  aux = Grafo.addNode();
	(*map)[aux]=anterior;
	pintarRobot( anterior, anterior);
	differentialrobot_proxy->setOdometerPose(0,0,state.alpha);
}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker(){  
}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params)
{
	timer.start(Period);
	return true;
}
void SpecificWorker::compute()
{	
	ldata = laser_proxy->getLaserData();
	ldatacota = laser_proxy->getLaserData();
	std::sort( ldata.begin(), ldata.end(), [](RoboCompLaser::TData a, RoboCompLaser::TData b){ return (a.dist < b.dist); }) ;  //sort laser data from small to $
	std::sort( ldatacota.begin()+cota, ldatacota.end()-cota, [](RoboCompLaser::TData a, RoboCompLaser::TData b){ return (a.dist < b.dist); }) ;  //sort laser data from small to $
	differentialrobot_proxy->getBaseState(state);
 	inner->updateTransformValues("base",state.x,0,state.z,0,state.alpha,0);
	switch(st)
	{
		case State::INIT:
		  
		      break;
		case State::MAPEAR:
			 if(esquina())
			{
				accionEsquina();
			}
			else
			{
				mapear();
			}
		  break;
		case State::ORIENTARSE:
			  NavState s=controller_proxy->getState();
			  if(s.state=="FINISH"||s.state=="IDLE"){
			  
				st=State::MAPEAR;
			  }
		   break;
	}
}
void SpecificWorker::mapear()
{
	QVec p=Seleccionarobjetivo();
	float z= p(2);
	float x= p(0);
	
	
	cout<<x<<","<<z<<endl;
	writeinfo("Point = ("+to_string(p(0))+","+to_string(p(2))+")");
	ListDigraph::Node  nodonuevo = Grafo.addNode();		
	
	nodo nuevo;
	nuevo.set_x_z(x,z);
	(*map)[nodonuevo]=nuevo;
	for(ListDigraph::NodeIt n(Grafo); n!=INVALID;++n)
	{
		if((*map)[n]==anterior)
		{
			ListDigraph::Arc a=Grafo.addArc(n,nodonuevo);
			nodo origen = (*map)[n];
			nodo destino =(*map)[nodonuevo];
			float x = origen.get_x()-destino.get_x();
			float z = origen.get_z()-destino.get_z() ;
			(*cost)[a]=sqrt(x*x+z*z);
			break;
		}
	}
	pintarRobot( anterior, nuevo);
	anterior.set_x_z(x,z);
	RoboCompController::TargetPose t;
	t.x=p(0);
	t.z=p(2);
	t.y=0;
	controller_proxy->go(t);
	
	st=State::ORIENTARSE;
	
}

QVec SpecificWorker::Seleccionarobjetivo(){
	nodo n;
	 
	QVec dist=QVec::zeros(ldata.size());
	for(int i=0;i<ldata.size();i++){
		float angle=ldata[i].angle;
		float dista =ldata[i].dist;
		n.set_x_z(dista*sin(angle),dista*cos(angle));
		float dismin=std::numeric_limits<float>::max();
		for(ListDigraph::NodeIt aux(Grafo); aux!=INVALID;++aux){
			nodo n_G = (*map)[aux];
			if(dismin>n_G.sqrt_nodo(n))
				dismin=n_G.sqrt_nodo(n);
		}
		dist(i) = dismin +ldata[i].dist;
	}
	int j;
	float m=dist.max(j);
	QVec p=inner->laserTo("world","laser",ldata[j].dist-420,ldata[j].angle);
	return p;
}

bool SpecificWorker::esquina()
{
	RoboCompLaser::TLaserData ldataaux = laser_proxy->getLaserData();
	return (ldataaux.data()+cota)->dist<distsecurity&&((ldataaux.data())+100-cota)->dist<distsecurity;
}
void SpecificWorker::accionEsquina()
{	
	writeinfo("Esquina");
// 	marcas.clear();
	differentialrobot_proxy->setSpeedBase(-400, 0); 				// DA MARCHA ATRAS
	usleep(1000000);
	RoboCompLaser::TLaserData ldataaux = laser_proxy->getLaserData();  //read laser data
	if(ldataaux.data()->dist<(ldataaux.data()+99)->dist)
		sentido=-sentido;
	differentialrobot_proxy->setSpeedBase(0, sentido);			//GIRA SOBRE SÍ MISMO
	usleep(1000000);
	differentialrobot_proxy->setSpeedBase(0, 0);
}
void SpecificWorker::newAprilTag(const tagsList &tags)
{	
	for (auto t :tags){
	      marcas.add(t,state);
	}
}
void SpecificWorker::reloj()
{
	static int seg=1;
	static int min=1;
	static int hor=1;
	if(startbutton){
		if(seg<60){
			LCDseg->display(seg++);
		}
		else if(seg==60&&min<60){
			seg=1;
			LCDseg->display(seg);
			LCDmin->display(min++);
		}
		else {
			seg=1;
			min=1;
			LCDseg->display(seg);
			LCDmin->display(min);
			LCDhor->display(hor++);
		}
	}
}
void SpecificWorker::iniciar()
{
	st=State::MAPEAR;
	startbutton=true;
}
void SpecificWorker::parar()
{
	startbutton=false;
	st=State::INIT;
	differentialrobot_proxy->setSpeedBase(0, 0);
}
void SpecificWorker::writeinfo(string _info)
{	
	QString *text=new QString(_info.c_str());
	InfoText->append(*text);
} 
void SpecificWorker::pintarRobot(nodo origen, nodo destino)
{	
// 	scene->addRect(state.x/10,-state.z/10,40,40,QPen(Qt::black),QBrush(Qt::black));
	scene->addLine(origen.x/10, -origen.z/10, destino.x/10, -destino.z/10, QPen(Qt::black));
	scene->addEllipse(destino.x/10-15, -destino.z/10-15, 30, 30, QPen(Qt::white), QBrush(Qt::black));
}