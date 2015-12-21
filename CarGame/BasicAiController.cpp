#include "stdafx.h"
#include "BasicAIController.h"
#include <iostream>
#include <iomanip>
#include "Car.h"
#include "fann.h"



#define MAX_NUMBER_OF_TRAINING_DATA (4096 * 4096)

BasicAIController::BasicAIController()
{
	allTrainingData.reserve(MAX_NUMBER_OF_TRAINING_DATA);
	m_startRecord = false;

}

void BasicAIController::initController(TopdownCar * car)
{
	IController::initController(car);

	std::cout << std::endl
		<< "User controlled simulation:" << std::endl
		<< " [ ESC ] - return to choice menu" << std::endl
		<< " [ W ] - move forward" << std::endl
		<< " [ S ] - move backward" << std::endl
		<< " [ A ] - turn left" << std::endl
		<< " [ D ] - turn right" << std::endl
		<< std::endl;

	for (unsigned int i = 0; i < OA_NUM; i++)
		currentAction[i] = -1.0f;
}

void BasicAIController::keyDown(unsigned char c)
{
	m_car->keyboard(c);

	switch (c)
	{
	case 'a':
		currentAction[OA_LEFT] = 1.0f;
		break;
	case 'd':
		currentAction[OA_RIGHT] = 1.0f;
		break;
	case 'w':
		currentAction[OA_UP] = 1.0f;
		break;
	case 's':
		currentAction[OA_DOWN] = 1.0f;
		break;

	}
	m_startRecord = true;


}

void BasicAIController::keyUp(unsigned char c)
{
	m_car->keyboardUp(c);
	switch (c)
	{
	case 'a':
		currentAction[OA_LEFT] = -1.0f;
		break;
	case 'd':
		currentAction[OA_RIGHT] = -1.0f;
		break;
	case 'w':
		currentAction[OA_UP] = -1.0f;
		break;
	case 's':
		currentAction[OA_DOWN] = -1.0f;
		break;

	}
	
}

void BasicAIController::trainNN()
{
	FILE * dataFile = fopen("traindata.txt", "w");
	fprintf(dataFile, "%d %d %d \n", allTrainingData.size(), IS_NUM, OA_NUM);

	
	for (unsigned int i = 0; i < allTrainingData.size(); i++)
	{
		fprinfvector(dataFile, allTrainingData[i].input, IS_NUM);
		fprinfvector(dataFile, allTrainingData[i].output, OA_NUM);
	
	}
	fclose(dataFile);
}

BasicAIController::~BasicAIController()
{

	trainNN();
}
/*
enum INPUT_SENSOR_TYPE
{
	IS_VELOCITY,
	IS_LEFTDISTANCE,
	IS_TRACKANGLE,
	IS_RAYCAST90,
	IS_RAYCAST45,
	IS_RAYCAST0,
	IS_RAYCASTM45,
	IS_RAYCASTM90,

	IS_NUM
};
*/
void BasicAIController::fixedStepUpdate()
{
	if (m_startRecord == false)
		return;
	float *sensorData = m_car->getSensorData().data;
	if (sensorData[IS_RAYCAST45] < 5)
	{
		keyDown('d');
	}
	else
	{
		keyUp('d');
	}

	if (sensorData[IS_RAYCASTM45] < 5)
	{
		keyDown('a');
	}
	else
	{
		keyUp('a');
	}
	keyDown('w');

	trainData newdata;
	memcpy(newdata.input, m_car->getSensorData().data, sizeof(newdata.input));
	memcpy(newdata.output, currentAction, sizeof(currentAction));
	allTrainingData.push_back(newdata);

	prinfvector(newdata.input, IS_NUM);
	prinfvector(newdata.output, OA_NUM);


	
}