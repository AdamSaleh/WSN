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

#include "MotionSensor.h"
#include "PolicemenApplLayer.h"

#include <ccomponent.h>
#include <BaseMobility.h>
#include <FWMath.h>
#include <FindModule.h>

Define_Module(MotionSensor);

const simsignalwrap_t MotionSensor::mobilityStateChangedSignal =
		simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);
const simsignalwrap_t MotionSensor::sensorAlertSignal = simsignalwrap_t(
		SIGNAL_SENSOR_ALERT_NAME);

MotionSensor::MotionSensor() {

}

MotionSensor::~MotionSensor() {

}

void MotionSensor::initialize(int stage) {
	BaseSensor::initialize(stage);
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
		EV << "subscribing..." << endl;
		findHost()->getParentModule()->subscribe(mobilityStateChangedSignal,
				this);
		nbEvents = 0;
		nbMotionEvents = 0;
		nbAlerts = 0;
		nbSensedMovements = 0;

	}
}

/**
 * Receive subscribed items
 */
void MotionSensor::receiveSignal(cComponent *source, simsignal_t signalID,
		cObject *obj) {
	debugEV << "receiving some (mobility) event\n";
	if (stats) {
		nbEvents++;
	}

	// position has changed
	if (signalID == mobilityStateChangedSignal) {
		debugEV << "received some mobility event\n";
		if (stats) {
			nbMotionEvents++;
		}
		BaseMobility* const mobility = check_and_cast<BaseMobility*>(obj);
		cModule* emitterNode = mobility->getParentModule();
		if (emitterNode->initialized()) {
			//if self-message, don't react
			if (emitterNode->getId() != findHost()->getId()) {
				Coord pos = mobility->getCurrentPosition();
				Coord hostPos = FindModule<BaseMobility*>::findSubModule(
						findHost())->getCurrentPosition();

				// if in range, report
				if (hostPos.distance(pos) <= range) {
					if (stats) {
						nbAlerts++;
					}
					nbSensedMovements++;
					emit(sensorAlertSignal, emitterNode);
				}
			}
		} else {
			nbEvents--;
			nbMotionEvents--;
		}
	}
}

void MotionSensor::finish() {
	if (stats) {
		//TODO repair the recorded values -- right now it produces a bit more messages based on the host index
		recordScalar("nbMotionSensorEventsReceived", nbEvents);
		recordScalar("nbMotionEventsReceived", nbMotionEvents);
		recordScalar("nbAlertsEmited", nbAlerts);
		recordScalar("nbSensedAttackerMovements", nbSensedMovements);
	}
	cComponent::finish();
}

