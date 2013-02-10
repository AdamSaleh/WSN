//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef MOTIONSENSOR_H_
#define MOTIONSENSOR_H_
#define SIGNAL_SENSOR_ALERT_NAME "sensorAlertSignal"

#include "BaseSensor.h"

class MotionSensor: public BaseSensor {
protected:
	bool debug;
	bool stats;
	bool trace;

	int numNodes;
	long nbEvents;
	long nbMotionEvents;
	long nbAlerts;
	long nbSensedMovements;
	double range;

	/** @brief A signal used to subscribe to mobility state changes. */
	const static simsignalwrap_t mobilityStateChangedSignal;
	/** @brief A signal used to subscribe to sensor alert messages. */
	const static simsignalwrap_t sensorAlertSignal;

public:
	MotionSensor();
	virtual ~MotionSensor();

	virtual void initialize(int);
	virtual void finish();

	/**
	 * @brief Called by the signalling mechanism to inform of movement.
	 *
	 * ChannelAccess is subscribed to position changes and informs the
	 * ConnectionManager.
	 */
	virtual void receiveSignal(cComponent *source, simsignal_t signalID,
			cObject *obj);
};

#endif /* MOTIONSENSOR_H_ */
