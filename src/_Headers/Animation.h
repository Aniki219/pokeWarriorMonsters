#pragma once

struct Animation {
	int numFrames;
	int frame;
	int rowNum;
	std::string name;
	Animation(std::string animName, int rowNumber_, int numberOfFrames_, int startFrame = 0) : 
		name(animName),
		numFrames(numberOfFrames_), 
		rowNum(rowNumber_),
		frame(startFrame)
	{}
};