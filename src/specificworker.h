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


const double EulerC=std::exp(1.0);
class SpecificWorker : public GenericWorker
{
Q_OBJECT
	bool giro;		//CONTROL DEL SENTIDO DE GIRO
	float rot;		//VELOCIDAD DE GIRO rad/s
	bool startbutton;	//BOTON DE STARTINICIADO
	QGraphicsScene *scene;	//GRAFICOS DEL ROBOT


public:
	SpecificWorker(MapPrx& mprx);	
	~SpecificWorker();
	bool setParams(RoboCompCommonBehavior::ParameterList params);
public slots:
	void compute();
	void iniciar();
	void parar();
	void reloj();

private:
  
	void pintarRobot();
	void accionNoEsquina();
	void accionEsquina();
	bool esquina();
	void moverse();
	void getAprilTags();
	MyQTimer clk;
	int getdistmin(int dismax, float angle);
	int getvelocidadl(float distmin, float dist);
	float getvelocidadg(float angle, int dismax, int dis);
	void writeinfo(string _info);
	void newAprilTag(const tagsList &tags);
	void gototag();
	struct Marca
	      {	
		
		Marca(TBaseState State, int _id, float _z, float _x, float _y, float _rx, float _ry, float _rz)
		{
			id=_id;
// 			qDebug()<<id<< _id;
			float alpha=atan2(State.x,State.z);
			qDebug()<<State.alpha;
			x=State.x+cos(alpha)*_x-sin(alpha)*_z;
			z=State.z+sin(alpha)*_x+cos(alpha)*_z+337;
			y=0;
			rx=_rx;
			rz=_rz;
			ry=_ry;
		};
		int id;
		float distance;
		float z;
		float x;
		float y;
		float rx;
		float ry;
		float rz;
	      };
	struct listamarcas{
	      
	      QMap<int,Marca> lista;
	      QMutex mutex;
	      void add(const tag &t,TBaseState State)
	      {
		Marca m(State,t.id, t.tz, t.tx, t.ty, t.rx, t.ry, t.rz);
		QMutexLocker ml(&mutex);
		lista.insert(t.id,m);
// 		qDebug()<<lista.find(t.id).value().id;
	      };
	      Marca get(int id)
	      {
		QMutexLocker ml(&mutex);
		return lista.find(id).value();
	      };
	      bool contains(int id)
	      {
		QMutexLocker ml(&mutex);
		return lista.contains(id);
	      }
	      
	};
	listamarcas marcas;
};

#endif

