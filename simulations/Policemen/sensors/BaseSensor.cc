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

#include "BaseSensor.h"
#include "PolicemenApplLayer.h"

#include <ccomponent.h>
#include <BaseMobility.h>
#include <FWMath.h>
#include <FindModule.h>

Define_Module(BaseSensor);

const simsignalwrap_t BaseSensor::sensorAlertSignal = simsignalwrap_t(
		SIGNAL_SENSOR_ALERT_NAME);

BaseSensor::BaseSensor() {

}

BaseSensor::~BaseSensor() {

}

void BaseSensor::initialize(int stage) {
	BaseModule::initialize(stage);
	if (stage == 0) {
		hasPar("debug") ? debug = par("debug").boolValue() : debug = false;

		if (hasPar("stats")) {
			stats = par("stats");
		}
		if (hasPar("trace")) {
			trace = par("trace");
		}

		range = par("range");
		numNodes = getParentModule()->par("numNodes");
	} else if (stage == 1) {
			nbEvents = 0;
			nbMotionEvents = 0;
			nbAlerts = 0;
			nbSensedMovements = 0;
	}
}

void BaseSensor::finish() {
	if (stats) {
		recordScalar("nbBaseSensorEventsReceived", nbEvents);
		recordScalar("nbMotionEventsReceived", nbMotionEvents);
		recordScalar("nbAlertsEmited", nbAlerts);
		recordScalar("nbSensedAttackerMovements", nbSensedMovements);
	}
	cComponent::finish();
}

