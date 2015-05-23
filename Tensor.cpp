#include "Tensor.h"

using namespace phs;

Tensor::Tensor()
{
	comp[0][0]=0.0;
	comp[0][1]=0.0;
	comp[0][2]=0.0;
	comp[1][0]=0.0;
	comp[1][1]=0.0;
	comp[1][2]=0.0;
	comp[2][0]=0.0;
	comp[2][1]=0.0;
	comp[2][2]=0.0;
}

Tensor::Tensor(const Tensor& t)
{
	comp[0][0]=t.get(0,0);
	comp[0][1]=t.get(0,1);
	comp[0][2]=t.get(0,2);
	comp[1][0]=t.get(1,0);
	comp[1][1]=t.get(1,1);
	comp[1][2]=t.get(1,2);
	comp[2][0]=t.get(2,0);
	comp[2][1]=t.get(2,1);
	comp[2][2]=t.get(2,2);
}

Tensor::Tensor(double xa, double xb, double xc, double ya, double yb, double yc, double za, double zb, double zc)
{
	comp[0][0]=xa;
	comp[0][1]=xb;
	comp[0][2]=xc;
	comp[1][0]=ya;
	comp[1][1]=yb;
	comp[1][2]=yc;
	comp[2][0]=za;
	comp[2][1]=zb;
	comp[2][2]=zc;
}


Tensor::~Tensor()
{}
