#include <iostream>
#include <vector>
#include <fstream>

class Observer {
public:
	virtual void onWarning(const std::string& message) {}
	virtual void onError(const std::string& message) {}
	virtual void onFatalError(const std::string& message) {}
};

class Warning : public Observer
{
	void onWarning(const std::string& message) override
	{
		std::cout << message << std::endl;
	}
};

class Error : public Observer
{
	void onError(const std::string& message) override
	{
		std::ofstream write;
		write.open("File.txt");
		if (write.is_open())
		{
			write << message << std::endl;
		}
		write.close();
	}
};

class FatalError : public Observer
{
	void onError(const std::string& message) override
	{
		std::ofstream write;
		write.open("File.txt");
		if (write.is_open())
		{
			write << message << std::endl;
		}
		write.close();
		std::cout << message << std::endl;
	}
};

class Observed
{
	std::vector<Observer*> observers;
public:
	void AddObserver(Observer* obs)
	{
		observers.push_back(obs);
	}
	void RemoveObserver(Observer* obs)
	{
		observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
	}
	void warning(const std::string& message) const
	{
		for (auto obs : observers)
		{
			obs->onWarning(message);
		}
	}
	void error(const std::string& message) const
	{
		for (auto obs : observers)
		{
			obs->onError(message);
		}
	}
	void fatalError(const std::string& message) const
	{
		for (auto obs : observers)
		{
			obs->onFatalError(message);
		}
	}
};

int main()
{
	Observer* obs = new Warning();
	Observed obsd;
	obsd.AddObserver(obs);
	std::string str = "Hello world!";
	obs->onWarning(str);
	obsd.RemoveObserver(obs);
	return 0;
}