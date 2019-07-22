#pragma once


class Data {
public:
	virtual ~Data() {};
};

class Loader
{
public:
	Loader();
	virtual ~Loader();
	virtual bool Load(const char* path, Data& data) = 0;
};
