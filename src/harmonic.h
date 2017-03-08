/** @file harmonic.h
  @brief A brief, one sentence description.

  A more detailed multiline description...

  @author Peter Drysdale, Felix Fung,
*/

#ifndef NEUROFIELD_SRC_HARMONIC_H
#define NEUROFIELD_SRC_HARMONIC_H

// Other neurofield headers
#include "configf.h"    // Configf;
#include "de.h"         // DE; RK4;
#include "population.h" // Population;
#include "propagator.h" // Propagator;

// C++ standard library headers
#include <string> // std::string;
#include <vector> // std::vector;

class Harmonic : public virtual Propagator {
  Harmonic();                // No default constructor allowed.
  Harmonic(const Harmonic&); // No copy constructor allowed.

  // variables that are initialized once to speed up computation
  double gammasquared = 0.0; ///< == gamma^2;
  double twoongamma = 0.0;   ///< == 2.0/gamma;

  struct HarmonicDE : public DE {
    double gammasquared = 0.0, twoongamma = 0.0;
    virtual void init( const double pinit);
    HarmonicDE( size_type nodes, double deltat) : DE(nodes, deltat, 3) {}
    ~HarmonicDE(void) override = default;
    void rhs( const std::vector<double>& y, std::vector<double>& dydt ) override;
  };
  HarmonicDE* de;
  RK4* rk4;

 protected:
  void init( Configf& configf ) override;
  //virtual void restart( Restartf& restartf );
  //virtual void dump( Dumpf& dumpf ) const;

 public:
  Harmonic( size_type nodes, double deltat, size_type index, Population& prepop,
            Population& postpop, int longside, std::string topology );
  ~Harmonic(void) override;
  void step(void) override;
};

#endif //NEUROFIELD_SRC_HARMONIC_H
