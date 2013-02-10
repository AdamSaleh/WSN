
#include "PolicemanMobility.h"

#include <FWMath.h>


Define_Module(PolicemanMobility);

void PolicemanMobility::initialize(int stage)
{
    ConstSpeedMobility::initialize(stage);

    if(stage == 0) {
    	bool use2D = world->use2D();
    	outskirtsWidth = par("outskirtsWidth");
    } else if( stage == 1 ){
    	stepTarget = move.getStartPos();
    }
}

/**
 * Calculate a new random position and the number of steps the host
 * needs to reach this position
 */
void PolicemanMobility::setTargetPosition()
{
	debugEV << "start setTargetPosistion: " << move.info() << endl;

    do{
		targetPos = Coord(uniform(outskirtsWidth, playgroundSizeX() - outskirtsWidth),
                uniform(outskirtsWidth, playgroundSizeY() - outskirtsWidth),
                use2D ? 0. : uniform(outskirtsWidth, playgroundSizeZ()) - outskirtsWidth);

		double distance = move.getStartPos().distance(targetPos);
		simtime_t totalTime = distance / move.getSpeed();
		numSteps = FWMath::round(totalTime / updateInterval);

		debugEV << "new targetPos: " << targetPos.info() << " distance=" << distance
		   << " totalTime=" << totalTime << " numSteps=" << numSteps << endl;
    }
    while( numSteps == 0 );

    stepSize = targetPos - move.getStartPos();

    stepSize = stepSize / numSteps;

    stepTarget = move.getStartPos() + stepSize;

    debugEV << "stepSize: " << stepSize.info() << " target: " << (stepSize*numSteps).info() << endl;

    step = 0;
    move.setDirectionByTarget(targetPos);

    debugEV << "end setTargetPosistion: " << move.info() << endl;
}
