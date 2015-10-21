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
	connect(Reset, SIGNAL(clicked()), this, SLOT(reset()));
	connect(&clk, SIGNAL(senal()), this, SLOT(reloj()));
	connect(&clk, SIGNAL(senal2()), this ,SLOT(pintarRobot()));
	
	connect(cotavision,SIGNAL(sliderMoved(int)),this,SLOT(slidercota(int)));
	connect(vellmax,SIGNAL(sliderMoved(int)),this,SLOT(slidervelL(int)));
	connect(velgmax,SIGNAL(sliderMoved(int)),this,SLOT(slidervelG(int)));
	connect(distanciadeseguridad,SIGNAL(sliderMoved(int)),this,SLOT(sliderdisS(int)));
	connect(distanciadegiro,SIGNAL(sliderMoved(int)),this,SLOT(sliderdisG(int)));
	
	clk.setseg(1000);
	scene =  new QGraphicsScene();
	Grafico->setScene(scene);
	startbutton=false;
	giro=false;
	rot=1.2;
	clk.start();
	st=State::INIT;
	id_tag=0;
	cota = 16;
	distsecurity = 440;
	threshold = 400;
	velmax=350;	//velocidad maxima del robot
	velmaxg=2.2;
	slidercota(cota);
	sliderdisG(threshold);
	sliderdisS(distsecurity);
	slidervelG(velmaxg*10);
	slidervelL(velmax);
}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker(){}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params)
{
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
	return 300+dismax*(pow(EulerC,-(aux)));
}
void SpecificWorker::compute()
{	
	if(startbutton)
	{
		switch(st)
		{
			case State::INIT:
			      moverse();
			      break;
			case State::SEARCH:
			      search();
			      break;
		}
	}
}
void SpecificWorker::getAprilTags()
{
}
bool SpecificWorker::esquina()
{
	RoboCompLaser::TLaserData ldata = laser_proxy->getLaserData();
	return (ldata.data()+cota)->dist<distsecurity&&((ldata.data())+100-cota)->dist<distsecurity;
}
void SpecificWorker::accionEsquina()
{	
	writeinfo("Esquina");
// 	marcas.clear();
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
// 	static int cont;		//CONTROL DEL GIRO ALEATORIO
	float distaux = 0;
	float angle = 0;
	RoboCompLaser::TLaserData ldata = laser_proxy->getLaserData();  //read laser data
	if(marcas.contains(id_tag))
	{
		std::sort( ldata.begin(), ldata.end(), [](RoboCompLaser::TData a, RoboCompLaser::TData b){ return (a.dist < b.dist); }) ;  //sort laser data from small to $
		distaux=(ldata.data())->dist;			//DISTANCIA MINIMA A LA PARED
		angle=(ldata.data())->angle;				//ANGULO AL QUE SE ENCUENTRA LA DISTANCIA MINIMA
	}
	else
	{
		std::sort( ldata.begin()+cota, ldata.end()-cota, [](RoboCompLaser::TData a, RoboCompLaser::TData b){ return (a.dist < b.dist); }) ;  //sort laser data from small to $
		distaux=(ldata.data()+cota)->dist;			//DISTANCIA MINIMA A LA PARED
		angle=(ldata.data()+cota)->angle;				//ANGULO AL QUE SE ENCUENTRA LA DISTANCIA MINIMA
	}
	int distmax=getdistmin(threshold,angle);			//CALCULA LA DISTANCIA A LA QUE DEBE DE GIRAR
	int vel=getvelocidadl(distmax,distaux);			//CALCULA LA VELOCIDAD LINEAL
	rot=getvelocidadg(angle,distmax,distaux);
	if(rot<0)
		giro=false;						//CONTROL DEL SENTIDO DE GIRO

	if(distaux<distmax){
		rot=getvelocidadg(angle,distmax,distaux);		//CALCULA EL ANGULO DE GIRO
		differentialrobot_proxy->setSpeedBase(vel, rot);	//ESTABLECE LA VELOCIDAD Y LA ROTACION SI SE INCUMPLE LA DISTANCIA
// 		marcas.clear();
// 		st=State::INIT;
	}
/*===========================GIRA CUANDO ESTA EN UNA DISTANCIA DE SEGURIDAD===============================*/
	else{
		differentialrobot_proxy->setSpeedBase(vel, 0);
	}
  
}
void SpecificWorker::pintarRobot()
{
	TBaseState state;
	differentialrobot_proxy->getBaseState(state);	
	scene->addRect(state.x/10,-state.z/10,40,40,QPen(Qt::black),QBrush(Qt::black));
}
QVec cambiarinversoPlano(float alpha, QVec punto, QVec plano)
{
	QMat Rt(3,3);
	Rt(0,0)=cos(alpha);
	Rt(0,1)=sin(alpha);
	Rt(0,2)=plano(0);
	Rt(1,0)=-sin(alpha);
	Rt(1,1)=cos(alpha);
	Rt(1,2)=plano(1);
	Rt(2,0)=0;
	Rt(2,1)=0;
	Rt(2,2)=1;
	QVec m(3);
	m(0)=punto(0);
	m(1)=punto(1);
	m(2)=1;
	QMat Rtinver=Rt.invert();
	
	QVec TagR(3);
	TagR=Rtinver*m;
	TagR=TagR/TagR(2);
	return TagR;
}

void SpecificWorker::search()
{	
	static int min;
	static bool encontrado=false;
	if(marcas.contains(id_tag)){
		Marca m=marcas.get(id_tag);
		float rot=0;
		RoboCompLaser::TLaserData ldata = laser_proxy->getLaserData();  //read laser data
		std::sort( ldata.begin()+cota, ldata.end()-cota, [](RoboCompLaser::TData a, RoboCompLaser::TData b){ return (a.dist < b.dist); }) ;  //sort laser data from small to $
		float distaux=(ldata.data()+cota)->dist;
		int distmax=0;
		int vel=getvelocidadl(distmax,distaux);
	
		TBaseState state;
		differentialrobot_proxy->getBaseState(state);	
		
		QVec plano(2);
		plano(0)=state.z;
		plano(1)=state.x;
		QVec punto(2);
		punto(0)=m.z;
		punto(1)=m.x;
		QVec tag=cambiarinversoPlano(state.alpha,punto,plano);
		if(espaciolibre()){	
			rot=atan2(tag(1),tag(0));
			differentialrobot_proxy->setSpeedBase(vel,rot);
		}
		
		
		float distance=(sqrt(m.x*m.x+m.z*m.z));
		writeinfoTag("Redirigiendo al tag "+ to_string(m.id)+":\n  Giro: "+to_string(rot)+" rad\n  Distancia: "+to_string(distance)+ "mm");
		encontrado=false;
		if(abs(tag(1))<750&&abs(tag(0))<750){
			min=LCDmin->intValue();
			id_tag++;
			differentialrobot_proxy->setSpeedBase(0,0);
			writeinfo("Hemos llegado al tag "+ to_string(m.id)+"\n  Distancia: "+to_string(distance)+ "mm\n"
			+"  Time: "+to_string(LCDhor->intValue())+":"+to_string(LCDmin->intValue())+":"+to_string(LCDseg->intValue()));
			sleep(2);
			encontrado=true;
		}
	}
	else
		writeinfoTag("No se ve el tag: "+ to_string(id_tag));
	if(LCDmin->intValue()==min+5&&encontrado){
		id_tag=0;
		writeinfo("Comenzamos de nuevo por exceso de tiempo");
		encontrado=false;
	}
	st=State::INIT;
}
void SpecificWorker::moverse()
{
	try
	{
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
		if(marcas.contains(id_tag)/*&&espaciolibre()*/){
			st=State::SEARCH;
		}
		else
			st=State::INIT;
	}
	catch(const Ice::Exception &ex)
	{
		writeinfo("ex");
	}
  
}
bool SpecificWorker::espaciolibre()
{
	RoboCompLaser::TLaserData ldata = laser_proxy->getLaserData();  //read laser data
	std::sort( ldata.begin(), ldata.end(), [](RoboCompLaser::TData a, RoboCompLaser::TData b){ return (a.dist < b.dist); }) ;  //sort laser data from small to $
	return(ldata.data()->dist>200);
}

void SpecificWorker::newAprilTag(const tagsList &tags)
{	
	TBaseState state;
	differentialrobot_proxy->getBaseState(state);
	for (auto t :tags){
	      marcas.add(t,state);
	}
	st=State::SEARCH;
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
void SpecificWorker::reset()
{
	slidercota(16);
	sliderdisG(400);
	sliderdisS(440);
	slidervelG(22);
	slidervelL(350);
	cotavision->setValue(16);
	vellmax->setValue(350);
	velgmax->setValue(22);
	distanciadeseguridad->setValue(440);
	distanciadegiro->setValue(400);
	
}
void SpecificWorker::slidercota(int val)
{
	cota=val;
	QString s=QString::number(val);
	Lcota->setText(s);
}
void SpecificWorker::sliderdisG(int val)
{
	threshold=val;
	QString s=QString::number(val);
	LdisG->setText(s);
}
void SpecificWorker::sliderdisS(int val)
{
	distsecurity=val;
	QString s=QString::number(val);
	LdisS->setText(s);
}
void SpecificWorker::slidervelG(int val)
{
	velmaxg=val/10;
	QString s;
	s.setNum(val/10);
	Lvelg->setText(s);
}
void SpecificWorker::slidervelL(int val)
{
	velmax=val;
	QString s=QString::number(val);
	Lvell->setText(s);
}
void SpecificWorker::writeinfoTag(string _info)
{	
	InfoTag->clear();
	QString *text=new QString(_info.c_str());
	InfoTag->append(*text);
}
void SpecificWorker::writeinfo(string _info)
{	
	QString *text=new QString(_info.c_str());
	InfoText->append(*text);
}  