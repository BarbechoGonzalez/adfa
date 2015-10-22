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
	enum class State  { INIT, SEARCH} ;  
	State st;
	int cota;
	int distsecurity;
	float threshold;
	int velmax;	//velocidad maxima del robot
	float velmaxg;
	TBaseState state;
	RoboCompLaser::TLaserData ldata;
	RoboCompLaser::TLaserData ldatacota;
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

	struct Marca
	      {	
		int id;
		float distance;
		float z;
		float x;
		float y;
		float rx;
		float ry;
		float rz;
		QVec cambiarPlano(float alpha, QVec punto, QVec plano)
		{
			QMat Rt(3,3);
			Rt(0,0)=cos(alpha);
			Rt(0,1)=-sin(alpha);
			Rt(0,2)=plano(0);
			Rt(1,0)=sin(alpha);
			Rt(1,1)=cos(alpha);
			Rt(1,2)=plano(1);
			Rt(2,0)=0;
			Rt(2,1)=0;
			Rt(2,2)=1;
			QVec m(3);
			m(0)=punto(0);
			m(1)=punto(1);
			m(2)=1;
			QVec sol(3);
			sol=Rt*m;
			sol=sol/sol(2);
			return sol;
		};
		Marca(TBaseState state, int _id, float _z, float _x, float _y, float _rx, float _ry, float _rz)
		{
			QVec TagC(2);
			TagC(0)=_z;
			TagC(1)=_x;
			QVec PlanoC(2);
			PlanoC(0)=180;
			PlanoC(1)=0;
			QVec PlanoR(2);
			PlanoR(0)=state.z;
			PlanoR(1)=state.x;
			QVec TagR = cambiarPlano(state.alpha,TagC,PlanoC);
			QVec TagM = cambiarPlano(state.alpha,TagC,PlanoR);
			id=_id;
			x = TagM(1);
			z = TagM(0);
			y = _y;
			rx = _rx;
			rz = _rz;
			ry = _ry;
		};
		string getString(){
			string aux="id = "+to_string(id)+"\n";
			aux += "x = "+to_string(x)+"\n";
			aux += "z = "+to_string(z)+"\n";
			aux += "y = "+to_string(y)+"\n";
			aux += "rx = "+to_string(rx)+"\n";
			aux += "rz = "+to_string(rz)+"\n";
			aux += "ry = "+to_string(ry)+"\n";
			return aux;
		};
	      };
	struct listamarcas{
		QMap<int,Marca> lista;
		QMutex mutex;
		void add(const tag &t, TBaseState state)
		{
			Marca m(state, t.id, t.tz, t.tx, t.ty, t.rx, t.ry, t.rz);
			QMutexLocker ml(&mutex);
			lista.insert(t.id,m);
		};
		Marca get(int id)
		{
			QMutexLocker ml(&mutex);
			Marca m=lista.find(id).value();
// 			lista.remove(id);
// 			lista.clear();
			return m;
		};
		void clear(){
			QMutexLocker ml(&mutex);
			lista.clear();
		}
		bool contains(int id)
		{
			QMutexLocker ml(&mutex);
			return lista.contains(id);
		}      
	};
	listamarcas marcas;
};
#endif

