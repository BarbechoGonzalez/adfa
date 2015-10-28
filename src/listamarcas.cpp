#include "listamarcas.h"

listaMarcas::listaMarcas()
{
}
listaMarcas::~listaMarcas()
{
}
void listaMarcas::add(const RoboCompAprilTags::tag &t, RoboCompDifferentialRobot::TBaseState state)
{
	Marca m(state.x,state.z,state.alpha, t.id, t.tz, t.tx, t.ty, t.rx, t.ry, t.rz);
	QMutexLocker ml(&mutex);
	lista.insert(t.id,m);
};
		
Marca listaMarcas::get(int id)
{
	QMutexLocker ml(&mutex);
	Marca m=lista.find(id).value();
	return m;
};

void listaMarcas::clear(){
	QMutexLocker ml(&mutex);
	lista.clear();
}
bool listaMarcas::contains(int id)
{
	QMutexLocker ml(&mutex);
	return lista.contains(id);
}  