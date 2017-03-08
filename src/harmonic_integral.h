/** @file harmonic_integral.h
  @brief A brief, one sentence description.

  A more detailed multiline description...

  @author Peter Drysdale, Felix Fung,
*/

#ifndef NEUROFIELD_SRC_HARMONIC_INTEGRAL_H
#define NEUROFIELD_SRC_HARMONIC_INTEGRAL_H

// Other neurofield headers
#include "configf.h"    // Configf;
#include "population.h" // Population;
#include "propagator.h" // Propagator;

// C++ standard library headers
#include <string> // std::string;
#include <vector> // std::vector;

class HarmonicIntegral : public virtual Propagator {
  HarmonicIntegral();                        // No default constructor allowed.
  HarmonicIntegral(const HarmonicIntegral&); // No copy constructor allowed.
 protected:
  void init( Configf& configf ) override;
  //virtual void restart( Restartf& restartf );
  //virtual void dump( Dumpf& dumpf ) const;

  std::vector<double> oldp;
  std::vector<double> oldQ;
  std::vector<double> dpdt;
  double dQdt;

  // variables that initializes once
  double twoongamma;
  double expgamma;

  // variables that change every timestep
  double adjustedQ;
  double C1;
  double C1dtplusC2;
 public:
  HarmonicIntegral( size_type nodes, double deltat, size_type index, Population& prepop,
            Population& postpop, int longside, std::string topology );
  ~HarmonicIntegral(void) override;
  void step(void) override;
};

#endif //NEUROFIELD_SRC_HARMONIC_INTEGRAL_H
