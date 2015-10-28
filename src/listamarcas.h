#ifndef LISTAMARCAS_H
#define LISTAMARCAS_H

#include "marca.h"
#include <qt4/QtCore/QMutex>
#include <AprilTags.h>
#include <DifferentialRobot.h>

class listaMarcas
{

public:
	listaMarcas();
	~listaMarcas();
	
	void add(const RoboCompAprilTags::tag &t, RoboCompDifferentialRobot::TBaseState state);
	Marca get(int id);
	void clear();
	bool contains(int id);
  
private:
	QMap<int,Marca> lista;
	QMutex mutex;

};
#endif