/* -*- mode:c++ -*- ********************************************************
 * file:        AttackerMobility.h
 *
 * author:      Steffen Sroka
 *
 * copyright:   (C) 2004 Telecommunication Networks Group (TKN) at
 *              Technische Universitaet Berlin, Germany.
 *
 *              This program is free software; you can redistribute it
 *              and/or modify it under the terms of the GNU General Public
 *              License as published by the Free Software Foundation; either
 *              version 2 of the License, or (at your option) any later
 *              version.
 *              For further information see file COPYING
 *              in the top level directory
 ***************************************************************************
 * part of:     framework implementation developed by tkn
 **************************************************************************/


#ifndef CONST_SPEED_MOBILITY_H
#define CONST_SPEED_MOBILITY_H

#include "MiXiMDefs.h"
#include "BaseMobility.h"

/**
 * @brief Controls all movement related things of a host
 *
 * Parameters to be specified in omnetpp.ini
 *  - vHost : Speed of a host [m/s]
 *  - updateInterval : Time interval to update the hosts position
 *  - x, y, z : Starting position of the host, -1 = random
 *
 * @ingroup mobility
 * @author Steffen Sroka, Marc Loebbers, Daniel Willkomm
 * @sa ConnectionManager
 */
class MIXIM_API AttackerMobility : public BaseMobility
{
  private:
	/** @brief Copy constructor is not allowed.
	 */
	AttackerMobility(const AttackerMobility&);
	/** @brief Assignment operator is not allowed.
	 */
	AttackerMobility& operator=(const AttackerMobility&);

  protected:
    /** @name parameters to handle the movement of the host*/
    /*@{*/
    /** @brief Size of a step*/
    Coord stepSize;
    /** @brief Total number of steps */
    int numSteps;
    /** @brief Number of steps already moved*/
    int step;
    /*@}*/

    double outskirtsWidth;

    Coord targetPos;
    Coord stepTarget;

    //    double lastStep;

  public:
    AttackerMobility()
    	: BaseMobility()
    	, stepSize()
    	, numSteps(0)
    	, step(0)
    	, targetPos()
    	, stepTarget()
    {}

    /** @brief Initializes mobility model parameters.*/
    virtual void initialize(int);

  protected:
    /** @brief Calculate the target position to move to*/
    virtual void setTargetPosition();

    /** @brief Move the host*/
    virtual void makeMove();

    /** @brief Reset attacker's coordinates*/
    void resetAttackerCoordinates();

    //    void fixIfHostGetsOutside();
};

#endif
