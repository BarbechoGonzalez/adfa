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
// #define cota 16
// #define distsecurity 440
// #define threshold 400.0
const int cota = 16;
const int distsecurity = 440;
const float threshold = 400;
const int velmax=350;	//velocidad maxima del robot
const float velmaxg=2.2;

#include "specificworker.h"
static float sentido=M_PI;
/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(MapPrx& mprx) : GenericWorker(mprx){
	connect(Start, SIGNAL(clicked()), this, SLOT(iniciar()));
	connect(Stop, SIGNAL(clicked()), this, SLOT(parar()));
	connect(&clk, SIGNAL(senal()), this, SLOT(reloj()));
	clk.setseg(1000);
	scene =  new QGraphicsScene();
	Grafico->setScene(scene);
	startbutton=false;
	giro=false;
	rot=1.2;
	clk.start();
}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker(){}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params){
	timer.start(Period);
	return true;
}

int SpecificWorker::getvelocidadl(float distmin, float dist)
{
  	if(dist<distmin){
		return velmax*tanh(dist/distmin);
	}
	else
		return velmax;
}
float SpecificWorker::getvelocidadg(float angle, int dismax, int dis)
{
	if(dis<dismax){
		float resul;
		float aux=M_PI*angle*angle;
		resul = 1+velmaxg*(pow(EulerC,-(aux)));	      
		if (angle>0&&!giro)
			resul=-resul;
		return resul;
	}
	else return 0;
}
int SpecificWorker::getdistmin(int dismax,float angle)
{
	float aux=M_PI*angle*angle;
	return 350+dismax*(pow(EulerC,-(aux)));
}

void SpecificWorker::compute()
{
  moverse();
//   newAprilTag(new tag(tags_proxy->) );
  gototag();
  
}
void SpecificWorker::getAprilTags()
{
}

void SpecificWorker::gototag()
{
	static int cont_tag=0;
	  if(marcas.contains(cont_tag)){
	
		Marca m=marcas.get(cont_tag);
		qDebug() << m.id;
		writeinfo("El tag "+ to_string(m.id)+" esta en la posicion:");
		writeinfo("x = "+to_string(m.x));
		writeinfo("z = "+to_string(m.z));
// 		writeinfo("y = "+to_string(m.y));
// 		writeinfo("rx = "+to_string(m.rx));
// 		writeinfo("rz = "+to_string(m.rz));
// 		writeinfo("ry = "+to_string(m.ry));
		cont_tag++;
	}
}
bool SpecificWorker::esquina()
{
	RoboCompLaser::TLaserData ldata = laser_proxy->getLaserData();
	return (ldata.data()+cota)->dist<distsecurity&&((ldata.data())+100-cota)->dist<distsecurity;
}
void SpecificWorker::accionEsquina()
{
	writeinfo("¡¡¡Esquina!!!");
	differentialrobot_proxy->setSpeedBase(-400, 0); 				// DA MARCHA ATRAS
	usleep(1000000);
	RoboCompLaser::TLaserData ldata2 = laser_proxy->getLaserData();  //read laser data
	if(ldata2.data()->dist>(ldata2.data()+99)->dist)
	sentido=-sentido;
	differentialrobot_proxy->setSpeedBase(0, (sentido));			//GIRA SOBRE SÍ MISMO
	usleep(1000000);
	giro=false;
}

void SpecificWorker::accionNoEsquina()
{	
	static int cont;		//CONTROL DEL GIRO ALEATORIO

	RoboCompLaser::TLaserData ldata = laser_proxy->getLaserData();  //read laser data
	std::sort( ldata.begin()+cota, ldata.end()-cota, [](RoboCompLaser::TData a, RoboCompLaser::TData b){ return (a.dist < b.dist); }) ;  //sort laser data from small to $
	float distaux=(ldata.data()+cota)->dist;			//DISTANCIA MINIMA A LA PARED
	float angle=(ldata.data()+cota)->angle;				//ANGULO AL QUE SE ENCUENTRA LA DISTANCIA MINIMA

	int distmax=getdistmin(threshold,angle);			//CALCULA LA DISTANCIA A LA QUE DEBE DE GIRAR
	rot=getvelocidadg(angle,distmax,distaux);		//CALCULA EL ANGULO DE GIRO
	int vel=getvelocidadl(distmax,distaux);			//CALCULA LA VELOCIDAD LINEAL

	if(rot<0)
		giro=false;						//CONTROL DEL SENTIDO DE GIRO

	if((ldata.data()+cota)->dist<distmax)
		differentialrobot_proxy->setSpeedBase(vel, rot);	//ESTABLECE LA VELOCIDAD Y LA ROTACION SI SE INCUMPLE LA DISTANCIA
/*===========================GIRA CUANDO ESTA EN UNA DISTANCIA DE SEGURIDAD===============================*/
	else{
		cont++;
		if (cont==200){
			rot=rand()%100 -4;
			differentialrobot_proxy->setSpeedBase(vel, rot/10);
			usleep(rand()%(250000));
			cont=0;
		}
	else
	differentialrobot_proxy->setSpeedBase(vel, 0);

	}
/*=====================INFORMACION EN EL QTEXTEDIT====================*/
// 				writeinfo("Velocidad lineal = "+to_string(vel));
// 				writeinfo("Velocidad de rotacion = "+to_string(rot));
/*====================================================================*/

}
void SpecificWorker::pintarRobot()
{
	TBaseState state;
	differentialrobot_proxy->getBaseState(state);	
	scene->addRect(state.x/10,-state.z/10,40,40,QPen(Qt::black),QBrush(Qt::black));
}

void SpecificWorker::moverse()
{
	if(startbutton){
		try{
			
/*=================================DETECTA LAS ESQUINAS===================================*/
			if(esquina())
			{
				accionEsquina();
			}
/*========================================================================================*/
/*==================================SI NO ES UNA ESQUINA==================================*/
			else
			{
				accionNoEsquina();
			}
/*=============DIBUJO PASO DEL ROBOT QTGRAFICSVIEW====================*/
		pintarRobot();
/*====================================================================*/
		}
		catch(const Ice::Exception &ex){
			writeinfo("ex");
		}
    }
  
}

void SpecificWorker::newAprilTag(const tagsList &tags)
{
  for (auto t :tags){
	TBaseState State;
	differentialrobot_proxy->getBaseState(State);
	marcas.add(t,State);
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
	startbutton=true;
}
void SpecificWorker::parar()
{
	startbutton=false;
	differentialrobot_proxy->setSpeedBase(0, 0);
}
void SpecificWorker::writeinfo(string _info)
{
	QString *text=new QString(_info.c_str());
	InfoText->append(*text);
}