#include "CheckpointTimer.h"


CheckpointTimer::~CheckpointTimer(void)
{
}

CheckpointTimer::CheckpointTimer(Racer* _racer)
{
	racer = _racer;
	
	resetTime = 10;			// The time that is reset when the timer reaches zero
	currentCheckpoint = 0;	// The current checkpoint that racer is trying to get to
	checkPointTime = 10;	// The time the racer has at start, and keeps track over the course of the race.
	newTime = NULL;
	oldTime = time(NULL);

}


int CheckpointTimer::update(Waypoint* checkpoints[])//, D3DXVECTOR3 cameraPosition)
{
	newTime = time(NULL);
		
	checkPointTime = checkPointTime - difftime(newTime, oldTime);

	int prevCheckpoint;
	if(currentCheckpoint - 1 == -1){
		prevCheckpoint = 6;
	}
	else{
		prevCheckpoint = currentCheckpoint - 1;
	}
	D3DXVECTOR3 current = checkpoints[currentCheckpoint]->drawable->getPosition();
	hkVector4* currentPos = new hkVector4(current.x, current.y, current.z);
	D3DXVECTOR3 prev = checkpoints[prevCheckpoint]->drawable->getPosition();
	hkVector4* prevPos = new hkVector4(prev.x, prev.y, prev.z);
	if(checkpoints[currentCheckpoint]->passedWaypoint(currentPos, prevPos, &racer->body->getPosition())){
		checkPointTime += checkpoints[currentCheckpoint]->getCheckPointTime();
		if(currentCheckpoint == 6){ // NEEDS TO BE UPDATED BASED ON NUMBER OF CHECKPOINTS
			currentCheckpoint = 0;
		}
		else{
			currentCheckpoint += 1;
		}
	}

	oldTime = newTime;
	if(checkPointTime < 0){
		checkPointTime = resetTime;
	}

	return (int)checkPointTime;
}
