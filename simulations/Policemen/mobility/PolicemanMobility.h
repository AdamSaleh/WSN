#ifndef POLICEMAN_SPEED_MOBILITY_H
#define POLICEMAN_SPEED_MOBILITY_H

#include "ConstSpeedMobility.h"

/**
 * @brief Controls all movement related things of a host
 *
 * Parameters to be specified in omnetpp.ini
 *  - vHost : Speed of a host [m/s]
 *  - updateInterval : Time interval to update the hosts position
 *  - x, y, z : Starting position of the host, -1 = random
 */
class MIXIM_API PolicemanMobility : public ConstSpeedMobility
{
  private:
	/** @brief Copy constructor is not allowed.
	 */
	PolicemanMobility(const PolicemanMobility&);
	/** @brief Assignment operator is not allowed.
	 */
	PolicemanMobility& operator=(const PolicemanMobility&);

  protected:
	/** @brief width of the outskirts without reliable reporting */
	double outskirtsWidth;
	/** @brief is the world 2 dimensional? */
	bool use2D;

  public:
    PolicemanMobility()
    	: ConstSpeedMobility(),
    	  outskirtsWidth(),
    	  use2D(true)
    {}

    /** @brief Initializes mobility model parameters.*/
    virtual void initialize(int);

  protected:
    /** @brief Calculate the target position to move to*/
    virtual void setTargetPosition();

};

#endif
