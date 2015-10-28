#ifndef MARCA_H
#define MARCA_H
#include <qmat/QMatAll>

class Marca
{

public:
	Marca(float x_r, float z_r, float alpha, int _id, float _z, float _x, float _y, float _rx, float _ry, float _rz);
	~Marca();
    
	QVec cambiarPlano(float alpha, QVec punto, QVec plano);
	std::string getString();
	int id;
	float distance;
	float z;
	float x;
	float y;
	float rx;
	float ry;
	float rz;

};

#endif