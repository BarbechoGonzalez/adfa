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
#include <listamarcas.h>


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
	void pintarRobot();
	void reloj();
	void iniciar();
	void parar();
	void reset();
	void slidercota(int val);
	void slidervelL(int val);
	void slidervelG(int val);
	void sliderdisS(int val);
	void sliderdisG(int val);
private:
//=====================Variables==================
	int id_tag;
	float rot;		//VELOCIDAD DE GIRO rad/s
	bool giro;		//CONTROL DEL SENTIDO DE GIRO
	bool startbutton;	//BOTON DE STARTINICIADO
	MyQTimer clk;
	QGraphicsScene *scene;	//GRAFICOS DEL ROBOT
	enum class State  { INIT, BUSCAR, ORIENTARSE} ;  
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

	//=====================Funciones==================  
	int getvelocidadl(float distmin, float dist);
	float getvelocidadg(float angle, int dismax, int dis);
	int getdistmin(int dismax, float angle);
	void getAprilTags();
	bool esquina();
	void accionEsquina();
	void accionNoEsquina();
	void search();
	void moverse();
	bool espaciolibre();
	void newAprilTag(const tagsList &tags);
	void writeinfo(string _info);
	void writeinfoTag(string _info);
};
#endif

