/***************************************************************************
 * file:        AttackerMobility.cc
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

#include "AttackerMobility.h"

#include <FWMath.h>

Define_Module(AttackerMobility);

/**
 * Reads the updateInterval and the velocity
 *
 * If the host is not stationary it calculates the sink position and
 * schedules a timer to trigger the first movement
 */
void AttackerMobility::initialize(int stage) {
	BaseMobility::initialize(stage);

	if (stage == 0) {
		outskirtsWidth = par("outskirtsWidth");
		move.setSpeed(par("speed").doubleValue());

		if (move.getSpeed() <= 0)
			move.setSpeed(0);

		numSteps = 0;
		step = -1;
		stepSize = Coord(0, 0, 0);

		if (move.getSpeed() > 0) {
			// we have an attacker initial coordinates restrictions -> reinitializing coordinates for attacker
			resetAttackerCoordinates();
			debugEV << "Initialize: move speed: " << move.getSpeed() << " ("
					<< par("speed").doubleValue() << ")" << " pos: "
					<< move.info() << endl;
			setTargetPosition();
		}
	} else if (stage == 1) {
		stepTarget = move.getStartPos();
	}
}

/**
 * Reset initial coordinates for attacker nodes
 */
void AttackerMobility::resetAttackerCoordinates() {
	Coord pos = Coord::ZERO;
	/**
	 * _________ _
	 *|__rect0__|r|
	 *|r|       |e|
	 *|e|       |c|
	 *|c|       |t|
	 *|t|       |1|
	 *|1|_______|_|
	 *|_|__rect0__|
	 */
	double rect0, rect1 = 0;
	bool topLeft = intuniform(0, 1);
	if (playgroundSizeX() >= outskirtsWidth && playgroundSizeY() >= outskirtsWidth) {
		rect0 = (playgroundSizeX() - outskirtsWidth) * outskirtsWidth;
		rect1 = (playgroundSizeY() - outskirtsWidth) * outskirtsWidth;

		if (uniform(0, rect0 + rect1) < rect0) {
			debugEV << "Result in the horizontal axis!\n";
			if (topLeft) {
				pos.x = uniform(0, playgroundSizeX() - outskirtsWidth);
				pos.y = uniform(0, outskirtsWidth);
			} else {
				pos.x = uniform(outskirtsWidth, playgroundSizeX());
				pos.y = uniform(playgroundSizeY() - outskirtsWidth, playgroundSizeY());
			}
		} else {
			debugEV << "Result in the vertical axis!\n";
			if (topLeft) {
				pos.x = uniform(0, outskirtsWidth);
				pos.y = uniform(outskirtsWidth, playgroundSizeY());
			} else {
				pos.x = uniform(playgroundSizeX() - outskirtsWidth, playgroundSizeX());
				pos.y = uniform(0, playgroundSizeY() - outskirtsWidth);
			}
		}
		move.setStart(pos);
	} else {
		debugEV << "Playground too small!\n";
		return;
	}
//						pos.x = uniform(constraintAreaMin.x,
//								constraintAreaMin.x + outskirtsWidth)
//						pos.x = constraintAreaMin.x;
//				(constraintAreaMin.y + outskirtsWidth < constraintAreaMax.y) ?
//						pos.y = uniform(constraintAreaMin.y,
//								constraintAreaMin.y + outskirtsWidth) :
//						pos.y = constraintAreaMin.y;
}

/**
 * Calculate a new random position and the number of steps the host
 * needs to reach this position
 */
void AttackerMobility::setTargetPosition() {
	debugEV << "start setTargetPosistion: " << move.info() << endl;

	targetPos = Coord(
			(constraintAreaMin.x < constraintAreaMax.x) ?
					(constraintAreaMax.x - constraintAreaMin.x) / 2 :
					constraintAreaMin.x,
			(constraintAreaMin.y < constraintAreaMax.y) ?
					(constraintAreaMax.y - constraintAreaMin.y) / 2 :
					constraintAreaMin.y,
			(constraintAreaMin.z < constraintAreaMax.z) ?
					(constraintAreaMin.z - constraintAreaMax.z) / 2 :
					constraintAreaMin.z);

	double distance = move.getStartPos().distance(targetPos);
	simtime_t totalTime = distance / move.getSpeed();
	numSteps = FWMath::round(totalTime / updateInterval);

	debugEV << "new targetPos: " << targetPos.info() << " distance=" << distance
			<< " totalTime=" << totalTime << " numSteps=" << numSteps << endl;

	stepSize = targetPos - move.getStartPos();

	stepSize = stepSize / numSteps;

	stepTarget = move.getStartPos() + stepSize;

	debugEV << "stepSize: " << stepSize.info() << " target: "
			<< (stepSize * numSteps).info() << endl;

	step = 0;
	move.setDirectionByTarget(targetPos);

	debugEV << "end setTargetPosistion: " << move.info() << endl;
}

/**
 * Move the host if the destination is not reached yet. Otherwise
 * calculate a new random position
 */
void AttackerMobility::makeMove() {
	// increment number of steps
	step++;

	if (step == numSteps) {
		// last step
		//stepSize.x =
		// step forward
		move.setStart(stepTarget, simTime());

		debugEV << "stepping forward. step #=" << step << " startPos: "
				<< move.getStartPos().info() << endl;

		move.setSpeed(0);
		debugEV << "destination reached.\n" << move.info() << endl;
	} else if (step < numSteps) {
		// step forward
		move.setStart(stepTarget, simTime());
		stepTarget += stepSize;

		debugEV << "stepping forward. step #=" << step << " startPos: "
				<< move.getStartPos().info() << endl;

	} else {
		error("step cannot be bigger than numSteps");
	}

	//    fixIfHostGetsOutside();
}

/*
 void AttackerMobility::fixIfHostGetsOutside()
 {
 double dummy;

 handleIfOutside( PLACERANDOMLY, stepTarget, targetPos, stepSize, dummy );
 }
 */
