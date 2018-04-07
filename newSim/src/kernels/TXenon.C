// this file is edited by rafi fro temperature dependent thermal conductivity
#include "TXenon.h"


template<>
InputParameters validParams<TXenon>()
{
  InputParameters params = validParams<Diffusion>();
  params.addClassDescription("This will solve heat diffusion with temperature dependent thermal conductivity");
  return params;
}

TXenon::TXenon(const InputParameters & parameters) :
    Diffusion(parameters),
	_thermal_conductivity(getMaterialProperty<Real>("thermal_conductivity"))  /*be sure u use the "thermal_conductivity, otherwise it will
not read the thermal_conductivity from the input*/
{
}

Real
TXenon::computeQpResidual()
{
  //return _grad_u[_qp] * _grad_test[_i][_qp];
  //Real _k=0.606+0.0351*_u[_qp]; // from D.E. Burkes et al./ Journal of Nuc Material 2010

/* return _thermal_conductivity[_qp]*Diffusion::computeQpResidual() + 380E3*_test[_i][_qp]; */

// the above one for a constant forcing function

  return _thermal_conductivity[_qp]*Diffusion::computeQpResidual();
}

Real
TXenon::computeQpJacobian()
{
  //Real _k=0.606+0.0351*_u[_qp];
  //return _grad_phi[_j][_qp] * _grad_test[_i][_qp];

  return _thermal_conductivity[_qp]*Diffusion::computeQpJacobian() + 
	(-2*5.27536E-09*_u[_qp]*2.+2.34089E-5)*_grad_u[_qp]*_grad_test[_i][_qp];
}
