#include "PolicemenBMacLayer.h"
#include "DataPkt_m.h"
#include <MacPkt_m.h>
#include <PhyUtils.h>
#include <MacToPhyInterface.h>
#include <ccomponent.h>

Define_Module(PolicemenBMacLayer)

/**
 * Initialize method of BMacLayer. Init all parameters, schedule timers.
 */
void PolicemenBMacLayer::initialize(int stage) {
	BMacLayer::initialize(stage);
}

bool PolicemenBMacLayer::alreadyInQueue(cPacket* msg) {
	debugEV << "asking for name: " << msg->getName() << " kind: "
			<< msg->getKind() << " src: " << getMACAddress() << endl;

	MacQueue::iterator it;
	for (it = macQueue.begin(); it != macQueue.end(); ++it) {
		debugEV << *it << endl;
		MacPkt* pkt = *it;
		debugEV << pkt->getName() << " kind: " << pkt->getKind() << " src: "
				<< pkt->getSrcAddr() << endl;
		if (strcmp(msg->getName(), pkt->getName()) == 0
				&& pkt->getSrcAddr() == getMACAddress()) {
			return true;
		}
	}
	return false;
}

bool PolicemenBMacLayer::queueIsEmpty() {
	return macQueue.empty();
}

/**
 * Handle own messages:
 * BMAC_WAKEUP: wake up the node, check the channel for some time.
 * BMAC_CHECK_CHANNEL: if the channel is free, check whether there is something
 * in the queue and switch the radio to TX. When switched to TX, the node will
 * start sending preambles for a full slot duration. If the channel is busy,
 * stay awake to receive message. Schedule a timeout to handle false alarms.
 * BMAC_SEND_PREAMBLES: sending of preambles over. Next time the data packet
 * will be send out (single one).
 * BMAC_TIMEOUT_DATA: timeout the node after a false busy channel alarm. Go
 * back to sleep.
 */
void PolicemenBMacLayer::handleSelfMsg(cMessage *msg) {
	switch (macState) {
	case INIT:
		if (msg->getKind() == BMAC_START_BMAC) {
			debugEV << "State INIT, message BMAC_START, new state SLEEP"
					<< endl;
			changeDisplayColor(BLACK);
			phy->setRadioState(Radio::SLEEP);
			macState = SLEEP;
			scheduleAt(simTime() + dblrand() * slotDuration, wakeup);
			return;
		}
		break;
	case SLEEP:
		if (msg->getKind() == BMAC_WAKE_UP) {
			debugEV << "State SLEEP, message BMAC_WAKEUP, new state CCA"
					<< endl;
			scheduleAt(simTime() + checkInterval, cca_timeout);
			phy->setRadioState(Radio::RX);
			changeDisplayColor(GREEN);
			macState = CCA;
			return;
		}
		break;
	case CCA:
		if (msg->getKind() == BMAC_CCA_TIMEOUT) {
			// channel is clear
			// something waiting in eth queue?
			if (macQueue.size() > 0) {
				debugEV << "State CCA, message CCA_TIMEOUT, new state"
						" SEND_PREAMBLE" << endl;
				phy->setRadioState(Radio::TX);
				changeDisplayColor(YELLOW);
				macState = SEND_PREAMBLE;
				scheduleAt(simTime() + slotDuration, stop_preambles);
				return;
			}
			// if not, go back to sleep and wake up after a full period
			else {
				debugEV << "State CCA, message CCA_TIMEOUT, new state SLEEP"
						<< endl;
				scheduleAt(simTime() + slotDuration, wakeup);
				macState = SLEEP;
				phy->setRadioState(Radio::SLEEP);
				changeDisplayColor(BLACK);
				return;
			}
		}
		// during CCA, we received a preamble. Go to state WAIT_DATA and
		// schedule the timeout.
		if (msg->getKind() == BMAC_PREAMBLE) {
			nbRxPreambles++;
			debugEV << "State CCA, message BMAC_PREAMBLE received, new state"
					" WAIT_DATA" << endl;
			macState = WAIT_DATA;
			cancelEvent(cca_timeout);
			scheduleAt(simTime() + slotDuration + checkInterval, data_timeout);
			delete msg;
			return;
		}
		// this case is very, very, very improbable, but let's do it.
		// if in CCA and the node receives directly the data packet, switch to
		// state WAIT_DATA and re-send the message
		if (msg->getKind() == BMAC_DATA) {
			nbRxDataPackets++;
			debugEV << "State CCA, message BMAC_DATA, new state WAIT_DATA"
					<< endl;
			macState = WAIT_DATA;
			cancelEvent(cca_timeout);
			scheduleAt(simTime() + slotDuration + checkInterval, data_timeout);
			scheduleAt(simTime(), msg);
			return;
		}
		//in case we get an ACK, we simply dicard it, because it means the end
		//of another communication
		if (msg->getKind() == BMAC_ACK) {
			debugEV << "State CCA, message BMAC_ACK, new state CCA" << endl;
			delete msg;
			return;
		}
		break;

	case SEND_PREAMBLE:
		if (msg->getKind() == BMAC_SEND_PREAMBLE) {
			debugEV << "State SEND_PREAMBLE, message BMAC_SEND_PREAMBLE, new"
					" state SEND_PREAMBLE" << endl;
			sendPreamble();
			scheduleAt(simTime() + 0.5f * checkInterval, send_preamble);
			macState = SEND_PREAMBLE;
			return;
		}
		// simply change the state to SEND_DATA
		if (msg->getKind() == BMAC_STOP_PREAMBLES) {
			debugEV << "State SEND_PREAMBLE, message BMAC_STOP_PREAMBLES, new"
					" state SEND_DATA" << endl;
			macState = SEND_DATA;
			txAttempts = 1;
			return;
		}
		break;

	case SEND_DATA:
		if ((msg->getKind() == BMAC_SEND_PREAMBLE)
				|| (msg->getKind() == BMAC_RESEND_DATA)) {
			debugEV << "State SEND_DATA, message BMAC_SEND_PREAMBLE or"
					" BMAC_RESEND_DATA, new state WAIT_TX_DATA_OVER" << endl;
			// send the data packet
			sendDataPacket();
			macState = WAIT_TX_DATA_OVER;
			return;
		}
		break;

	case WAIT_TX_DATA_OVER:
		if (msg->getKind() == BMAC_DATA_TX_OVER) {
			if ((useMacAcks) && !LAddress::isL2Broadcast(lastDataPktDestAddr)) {
				debugEV << "State WAIT_TX_DATA_OVER, message BMAC_DATA_TX_OVER,"
						" new state WAIT_ACK" << endl;
				macState = WAIT_ACK;
				phy->setRadioState(Radio::RX);
				changeDisplayColor(GREEN);
				scheduleAt(simTime() + checkInterval, ack_timeout);
			} else {
				debugEV << "State WAIT_TX_DATA_OVER, message BMAC_DATA_TX_OVER,"
						" new state  SLEEP" << endl;
				delete macQueue.front();
				macQueue.pop_front();
				// if something in the queue, wakeup soon.
				if (macQueue.size() > 0)
					scheduleAt(simTime() + dblrand() * checkInterval, wakeup);
				else
					scheduleAt(simTime() + slotDuration, wakeup);
				macState = SLEEP;
				phy->setRadioState(Radio::SLEEP);
				changeDisplayColor(BLACK);
			}
			return;
		}
		break;
	case WAIT_ACK:
		if (msg->getKind() == BMAC_ACK_TIMEOUT) {
			// No ACK received. try again or drop.
			if (txAttempts < maxTxAttempts) {
				debugEV << "State WAIT_ACK, message BMAC_ACK_TIMEOUT, new state"
						" SEND_DATA" << endl;
				txAttempts++;
				macState = SEND_PREAMBLE;
				scheduleAt(simTime() + slotDuration, stop_preambles);
				phy->setRadioState(Radio::TX);
				changeDisplayColor(YELLOW);
			} else {
				debugEV << "State WAIT_ACK, message BMAC_ACK_TIMEOUT, new state"
						" SLEEP" << endl;
				//drop the packet
				delete macQueue.front();
				macQueue.pop_front();
				// if something in the queue, wakeup soon.
				if (macQueue.size() > 0)
					scheduleAt(simTime() + dblrand() * checkInterval, wakeup);
				else
					scheduleAt(simTime() + slotDuration, wakeup);
				macState = SLEEP;
				phy->setRadioState(Radio::SLEEP);
				changeDisplayColor(BLACK);
				nbMissedAcks++;
			}
			return;
		}
		//ignore and other packets
		if ((msg->getKind() == BMAC_DATA)
				|| (msg->getKind() == BMAC_PREAMBLE)) {
			debugEV << "State WAIT_ACK, message BMAC_DATA or BMAC_PREMABLE, new"
					" state WAIT_ACK" << endl;
			delete msg;
			return;
		}
		if (msg->getKind() == BMAC_ACK) {
			debugEV << "State WAIT_ACK, message BMAC_ACK" << endl;
			MacPkt* mac = static_cast<MacPkt *>(msg);
			const LAddress::L2Type& src = mac->getSrcAddr();
			// the right ACK is received..
			debugEV << "We are waiting for ACK from : " << lastDataPktDestAddr
					<< ", and ACK came from : " << src << endl;
			if (src == lastDataPktDestAddr) {
				debugEV << "New state SLEEP" << endl;
				nbRecvdAcks++;
				lastDataPktDestAddr = LAddress::L2BROADCAST;
				cancelEvent(ack_timeout);
				delete macQueue.front();
				macQueue.pop_front();
				// if something in the queue, wakeup soon.
				if (macQueue.size() > 0)
					scheduleAt(simTime() + dblrand() * checkInterval, wakeup);
				else
					scheduleAt(simTime() + slotDuration, wakeup);
				macState = SLEEP;
				phy->setRadioState(Radio::SLEEP);
				changeDisplayColor(BLACK);
				lastDataPktDestAddr = LAddress::L2BROADCAST;
			}
			delete msg;
			return;
		}
		break;
	case WAIT_DATA:
		if (msg->getKind() == BMAC_PREAMBLE) {
			//nothing happens
			debugEV << "State WAIT_DATA, message BMAC_PREAMBLE, new state"
					" WAIT_DATA" << endl;
			nbRxPreambles++;
			delete msg;
			return;
		}
		if (msg->getKind() == BMAC_ACK) {
			//nothing happens
			debugEV << "State WAIT_DATA, message BMAC_ACK, new state WAIT_DATA"
					<< endl;
			delete msg;
			return;
		}
		if (msg->getKind() == BMAC_DATA) {
			nbRxDataPackets++;
			MacPkt* mac = static_cast<MacPkt *>(msg);
			const LAddress::L2Type& dest = mac->getDestAddr();
			const LAddress::L2Type& src = mac->getSrcAddr();

			if (dest == myMacAddr) {
				if (ancQueue.empty()) {
					ancQueue.push_back(src);
				} else {
					AncestorQueue::iterator it;
					for (it = ancQueue.begin(); it != ancQueue.end(); ++it) {
						LAddress::L2Type addr = *it;
						debugEV << "Ancestor queue contains: " << addr
								<< " compared to src: " << src << endl;
						if (addr == src) {
							break;
						} else if (++it == ancQueue.end()) {
							debugEV << "ancQueue end" << endl;
							ancQueue.push_back(src);
						}
						--it;
					}
				}
				debugEV << "ancQueue size: " << ancQueue.size() << endl;
			}

			if ((dest == myMacAddr) || LAddress::isL2Broadcast(dest)) {
				sendUp(decapsMsg(mac));
			} else {
				delete msg;
				msg = NULL;
				mac = NULL;
			}

			cancelEvent(data_timeout);
			if ((useMacAcks) && (dest == myMacAddr)) {
				debugEV << "State WAIT_DATA, message BMAC_DATA, new state"
						" SEND_ACK" << endl;
				macState = SEND_ACK;
				lastDataPktSrcAddr = src;
				phy->setRadioState(Radio::TX);
				changeDisplayColor(YELLOW);
			} else {
				debugEV << "State WAIT_DATA, message BMAC_DATA, new state SLEEP"
						<< endl;
				// if something in the queue, wakeup soon.
				if (macQueue.size() > 0)
					scheduleAt(simTime() + dblrand() * checkInterval, wakeup);
				else
					scheduleAt(simTime() + slotDuration, wakeup);
				macState = SLEEP;
				phy->setRadioState(Radio::SLEEP);
				changeDisplayColor(BLACK);
			}
			return;
		}
		if (msg->getKind() == BMAC_DATA_TIMEOUT) {
			debugEV << "State WAIT_DATA, message BMAC_DATA_TIMEOUT, new state"
					" SLEEP" << endl;
			// if something in the queue, wakeup soon.
			if (macQueue.size() > 0)
				scheduleAt(simTime() + dblrand() * checkInterval, wakeup);
			else
				scheduleAt(simTime() + slotDuration, wakeup);
			macState = SLEEP;
			phy->setRadioState(Radio::SLEEP);
			changeDisplayColor(BLACK);
			return;
		}
		break;
	case SEND_ACK:
		if (msg->getKind() == BMAC_SEND_ACK) {
			debugEV << "State SEND_ACK, message BMAC_SEND_ACK, new state"
					" WAIT_ACK_TX" << endl;
			// send now the ack packet
			sendMacAck();
			macState = WAIT_ACK_TX;
			return;
		}
		break;
	case WAIT_ACK_TX:
		if (msg->getKind() == BMAC_ACK_TX_OVER) {
			debugEV << "State WAIT_ACK_TX, message BMAC_ACK_TX_OVER, new state"
					" SLEEP" << endl;
			// ack sent, go to sleep now.
			// if something in the queue, wakeup soon.
			if (macQueue.size() > 0)
				scheduleAt(simTime() + dblrand() * checkInterval, wakeup);
			else
				scheduleAt(simTime() + slotDuration, wakeup);
			macState = SLEEP;
			phy->setRadioState(Radio::SLEEP);
			changeDisplayColor(BLACK);
			lastDataPktSrcAddr = LAddress::L2BROADCAST;
			return;
		}
		break;
	}

//	opp_error("Undefined event of type %d in state %d (Radio state %d)!",
//				  msg->getKind(), macState, phy->getRadioState());
	debugEV << "Undefined event of type " << msg->getKind() << " in state "
			<< macState << " (Radio state " << phy->getRadioState() << ")!";
	delete msg;
}

std::list<LAddress::L2Type> PolicemenBMacLayer::GetAncestors() {
	return ancQueue;
}

PolicemenBMacLayer::~PolicemenBMacLayer() {
//	AncestorQueue::iterator it;
//	for (it = ancQueue.begin(); it != ancQueue.end(); ++it) {
//		delete (*it);
//	}
//	ancQueue.clear();
}
