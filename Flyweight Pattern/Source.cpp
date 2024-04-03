#include <iostream>
#include <map>
#include <string>
using namespace std;

/*
������� ������������ ��� ���������� ������ ��� ������ � ������� ����������� ������ ��������.
������� ��������� ���� �������, ����� ��������� ��� ����������������� �������:
- � ���������� ������������ ������� ����� ��������;
- ��-�� ����� ��������� ������� �� �������� ������;
- ������� ����� ��������� �������� ����� ������� �����;
- ������ ������ �������� ����� �������� ������������ ��������� ����������� ����������� ��������, ��������� ������� ��������� ��������.
*/

// Flyweight (House) - ��������� ���������, � ������� �������� �������������� ����� �������� ������� ���������.

class Base abstract
{
protected:
	int travelSpeed; 
	int power;

public:
	virtual void Show(double x, double y) abstract;//���������� ��� ��������� ������� ������
};

/*
ConcreteFlyweight (PanelHouse) - ���������� ��������������.
��������� ��������� ������ Flyweight � ��������� ��� ������������� ���������� ���������.
������ ������ ConcreteFlyweight ������ ���� �����������.
����� ����������� �� ��������� ������ ���� ����������, �� ���� �� ��������� �� ���������.
*/
class lightInfantry : public Base
{
public:
	lightInfantry()
	{
		travelSpeed = 20;
		power = 10;
	}
	void Show(double x, double y) override
	{
		char buffer[256];
		sprintf_s(buffer, "Light infantry with travel speed-20 and power-10 ; \ncoordinates: %f - latitude   %f - longitude", y, x);//�������� ����������
		cout << buffer << endl;
	}
};

/*
ConcreteFlyweight (BrickHouse) - ���������� ��������������.
��������� ��������� ������ Flyweight � ��������� ��� ������������� ���������� ���������.
������ ������ ConcreteFlyweight ������ ���� �����������.
����� ����������� �� ��������� ������ ���� ����������, �� ���� �� ��������� �� ���������.
*/
class transportVehicles : public Base
{
public:
	transportVehicles()
	{
		travelSpeed = 70;
		power = 0;
	}
	void Show(double x, double y) override
	{
		char buffer[256];
		sprintf_s(buffer, "Transport vehicles with travel speed-70 and power-0 ; \ncoordinates: %f - latitude   %f - longitude", y, x);//�������� ����������
		cout << buffer << endl;
	}
};


class heavyEquipment : public Base
{
public:
	heavyEquipment()
	{
		travelSpeed = 15;
		power = 150;
	}
	void Show(double x, double y) override
	{
		char buffer[256];
		sprintf_s(buffer, "Heavy equipment  with travel speed-15 and power-150 ; \ncoordinates: %f - latitude   %f - longitude", y, x);//�������� ����������
		cout << buffer << endl;
	}
};


class lightEquipment : public Base
{
public:
	lightEquipment()
	{
		travelSpeed = 50;
		power = 30;
	}
	void Show(double x, double y) override
	{
		char buffer[256];
		sprintf_s(buffer, "Light equipment  with travel speed-50 and power-30 ; \ncoordinates: %f - latitude   %f - longitude", y, x);//�������� ����������
		cout << buffer << endl;
	}
};


class aviationEquipment : public Base
{
public:
	aviationEquipment()
	{
		travelSpeed = 300;
		power = 100;
	}
	void Show(double x, double y) override
	{
		char buffer[256];
		sprintf_s(buffer, "Aviation equipment  with travel speed-300 and power-100 ; \ncoordinates: %f - latitude   %f - longitude", y, x);//�������� ����������
		cout << buffer << endl;
	}
};

/*
FlyweightFactory - ������� ���������������:
- ������� �������-�������������� � ��������� ���;
- ������������ ������� ���������� ���������������. ����� ������ ����������� ��������������,
������ FlyweightFactory ������������� ������������ ���������.
*/
class Factory//������ ��������� ���� ����� ����������� � ������ ����� ���� ���. ����� �����, ����������� ���������� � ���� ������
{
	map<string, Base*> militaryFacilities;//������ ����� ��� ������� � �� ����������� � ������ ������
public:
	Factory()
	{
		militaryFacilities["light infantry"] = new lightInfantry();//�������� ������ ������ ��� ������ ���� ������
		militaryFacilities["transport vehicles"] = new transportVehicles();//�������� ������ ������ ��� ������ ���� ������
		militaryFacilities["heavy equipment"] = new heavyEquipment();//�������� ������ ������ ��� ������ ���� ������
		militaryFacilities["light equipment"] = new lightEquipment();//�������� ������ ������ ��� ������ ���� ������
		militaryFacilities["aviation equipment"] = new aviationEquipment();//�������� ������ ������ ��� ������ ���� ������

	}
	~Factory()
	{
		delete militaryFacilities["light infantry"];
		delete militaryFacilities["transport vehicles"];
		delete militaryFacilities["heavy equipment"];
		delete militaryFacilities["light equipment"];
		delete militaryFacilities["aviation equipment"];

		militaryFacilities.clear();
	}
	Base* GetObj(string key)
	{
		if (militaryFacilities[key]!= nullptr)
			return militaryFacilities[key];//���������� ���
		else
			return nullptr;
	}
};

int main()
{
	/*
	 Client - ������:
		- ������ ������ �� ������ ��� ���������� ���������������;
		- ��������� ��� ������ ������� ��������� ���������������.
	 */

	double longitude = 37.61;
	double latitude = 55.74;

	Factory*factory = new Factory();



	for (int i = 0; i < 2; i++)
	{
		Base * lightInfantry = factory->GetObj("light infantry");//�� ������� � ���������� ������ ��������� ���
		if (lightInfantry != nullptr)
			lightInfantry->Show(longitude, latitude);
		longitude += 0.5;
		latitude += 0.1;
	}

	for (int i = 0; i < 2; i++)
	{
		Base * transportVehicles = factory->GetObj("transport vehicles");
		if (transportVehicles != nullptr)
			transportVehicles->Show(longitude, latitude);
		longitude += 0.4;
		latitude += 0.2;
	}

	for (int i = 0; i < 2; i++)
	{
		Base* heavyEquipment = factory->GetObj("heavy equipment");
		if (heavyEquipment != nullptr)
			heavyEquipment->Show(longitude, latitude);
		longitude += 0.3;
		latitude += 0.3;
	}

	for (int i = 0; i < 2; i++)
	{
		Base* lightEquipment = factory->GetObj("light equipment");
		if (lightEquipment != nullptr)
			lightEquipment->Show(longitude, latitude);
		longitude += 0.2;
		latitude += 0.4;
	}

	for (int i = 0; i < 2; i++)
	{
		Base* aviationEquipment = factory->GetObj("aviation equipment");
		if (aviationEquipment != nullptr)
			aviationEquipment->Show(longitude, latitude);
		longitude += 0.1;
		latitude += 0.5;
	}



	delete factory;
	system("pause");
}