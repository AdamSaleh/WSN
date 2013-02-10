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

#include "IDSLayer.h"

Define_Module(IDSLayer)

/**
 * Handle self messages
 */
void IDSLayer::handleSelfMsg(cMessage* msg){
	switch(msg->getKind()) {
	default:
		EV << "Unknown selfmessage! -> delete, kind: "<<msg->getKind() <<endl;
		delete msg;
		break;
	}
}

/**
 * Handle messages from upper layer
 */
void IDSLayer::handleUpperMsg(cMessage *msg){
	sendDown(msg);
}

/**
 * Handle messages from lower layer
 */
void IDSLayer::handleLowerMsg(cMessage *msg){
	sendUp(msg);
}

/**
 * Handle control messages from lower layer
 */
void IDSLayer::handleLowerControl(cMessage *msg){
	sendControlUp(msg);
}

/**
 * Handle control messages from upper layer
 */
void IDSLayer::handleUpperControl(cMessage *msg){
	sendControlDown(msg);
}

