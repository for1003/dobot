#include <stdio.h>
#include "include/DobotDll.h"

int main(void)
{
	int re = ConnectDobot(NULL, 115200, NULL, NULL, 0);
	if (re == 0)
		printf("device is connected\n");
	else if (re == 1)
		printf("device is not found\n");
	else if (re == 2)
		printf("device is busy\n");
	
	char buf[1024];
	GetDeviceName(buf, 1024);
	printf("devicename: %s\n", buf);	
	
	Pose pose;
	GetPose(&pose);
	printf("x: %f y: %f z: %f\n", pose.x, pose.y, pose.z);
	printf("1st joint: %f 2nd joint: %f 3rd joint: %f 4rd joint: %f\n",
			pose.jointAngle[0], pose.jointAngle[1], pose.jointAngle[2], pose.jointAngle[3]); 
	
	printf("R: %f\n", pose.r);

	// point to point
	PTPCmd command;
	command.ptpMode = 0;	// ??
	command.x = 200;
	command.y = 0;
	command.z = 0;
	command.r = 0;
	SetQueuedCmdStartExec();
	SetPTPCmd(&command, false, 0);
	SetQueuedCmdStopExec();

	DisconnectDobot();
	return 0;
}
