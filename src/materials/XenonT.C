// this file is edited by Rafi February 13, 2017
// 
#include "XenonT.h"

template<>
InputParameters validParams<XenonT>()
{
  InputParameters params = validParams<Material>();
// we do not need to add any data from the input file
  params.addClassDescription("This is to calculate the temperature dependent  thermal conductivity of Xenon");
// the "temperature" variable has to be defined in the input files
  params.addCoupledVar("dep_variable", "The thermal conductivity is calculated from temperature");
  return params;
}


XenonT::XenonT(const InputParameters & parameters) :
    Material(parameters),

    // Declare  material properties.  This returns references that we
    // hold onto as member variables
    //_permeability(declareProperty<Real>("permeability")),
	_thermal_conductivity(declareProperty<Real>("thermal_conductivity")),
	//_dep_variable(isCoupled("dep_varible"))
	_dep_variable(coupledValue("dep_variable"))
{
}

void
XenonT::computeQpProperties()
{

  // Sample the LinearInterpolation object to get the permeability for the ball size
  //_permeability[_qp] = _permeability_interpolation.sample(_ball_radius);
  //_thermal_conductivity[_qp]=0.000000001+0.00000000001*_dep_variable[_qp];
  /*abobe correlation is wrong, is calculated wrong, the next equation is calcuated from Robinovich et al. Thermophy
	sical property of Neon, Argon, Krypton, and Xenon */

	_thermal_conductivity[_qp]=-5.27536E-09*_dep_variable[_qp]*_dep_variable[_qp] + 2.34089E-5*_dep_variable[_qp]+ 0.000127346 ;
	 
	
}

