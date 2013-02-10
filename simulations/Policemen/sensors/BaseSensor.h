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

#ifndef BaseSensor_H_
#define BaseSensor_H_
#define SIGNAL_SENSOR_ALERT_NAME "sensorAlertSignal"

#include <BaseModule.h>

class BaseSensor: public BaseModule {
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
	BaseSensor();
	virtual ~BaseSensor();

	virtual void initialize(int);
	virtual void finish();
};

#endif /* BaseSensor_H_ */
