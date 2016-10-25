#pragma once
class Controllable
{
	public:
		virtual void buttonPress(int i) = 0;
		virtual void buttonRelease(int i) = 0;
		virtual void buttonLongPress(int i) = 0;

};