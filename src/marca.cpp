
#include "marca.h"



Marca::Marca(float x_r, float z_r,float alpha, int _id, float _z, float _x, float _y, float _rx, float _ry, float _rz)
{
	QVec TagC(2);
	TagC(0)=_z;
	TagC(1)=_x;
//	QVec PlanoC(2);
//	PlanoC(0)=180;
//	PlanoC(1)=0;
	QVec PlanoR(2);
	PlanoR(0)=z_r;
	PlanoR(1)=x_r;
//	QVec TagR = cambiarPlano(state.alpha,TagC,PlanoC);
	QVec TagM = cambiarPlano(alpha,TagC,PlanoR);
	id=_id;
	x = TagM(1);
	z = TagM(0);
	y = _y;
	rx = _rx;
	rz = _rz;
	ry = _ry;
}
Marca::~Marca()
{
  
}
QVec Marca::cambiarPlano(float alpha, QVec punto, QVec plano)
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
}

std::string Marca::getString(){
	std::string aux="id = "+std::to_string(id)+"\n";
	aux += "x = "+std::to_string(x)+"\n";
	aux += "z = "+std::to_string(z)+"\n";
	aux += "y = "+std::to_string(y)+"\n";
	aux += "rx = "+std::to_string(rx)+"\n";
	aux += "rz = "+std::to_string(rz)+"\n";
	aux += "ry = "+std::to_string(ry)+"\n";
	return aux;
}