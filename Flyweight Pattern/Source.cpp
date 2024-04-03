#include <iostream>
#include <map>
#include <string>
using namespace std;

/*
Паттерн используется для уменьшения затрат при работе с большим количеством мелких объектов.
Следует применять этот паттерн, когда выполнены все нижеперечисленные условия:
- в приложении используется большое число объектов;
- из-за этого накладные расходы на хранение высоки;
- большую часть состояния объектов можно вынести вовне;
- многие группы объектов можно заменить относительно небольшим количеством разделяемых объектов, поскольку внешнее состояние вынесено.
*/

// Flyweight (House) - объявляет интерфейс, с помощью которого приспособленцы могут получать внешнее состояние.

class Base abstract
{
protected:
	int travelSpeed; 
	int power;

public:
	virtual void Show(double x, double y) abstract;//координаты для получения внешних данных
};

/*
ConcreteFlyweight (PanelHouse) - конкретный приспособленец.
Реализует интерфейс класса Flyweight и добавляет при необходимости внутреннее состояние.
Объект класса ConcreteFlyweight должен быть разделяемым.
Любое сохраняемое им состояние должно быть внутренним, то есть не зависящим от контекста.
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
		sprintf_s(buffer, "Light infantry with travel speed-20 and power-10 ; \ncoordinates: %f - latitude   %f - longitude", y, x);//получает координаты
		cout << buffer << endl;
	}
};

/*
ConcreteFlyweight (BrickHouse) - конкретный приспособленец.
Реализует интерфейс класса Flyweight и добавляет при необходимости внутреннее состояние.
Объект класса ConcreteFlyweight должен быть разделяемым.
Любое сохраняемое им состояние должно быть внутренним, то есть не зависящим от контекста.
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
		sprintf_s(buffer, "Transport vehicles with travel speed-70 and power-0 ; \ncoordinates: %f - latitude   %f - longitude", y, x);//получает координаты
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
		sprintf_s(buffer, "Heavy equipment  with travel speed-15 and power-150 ; \ncoordinates: %f - latitude   %f - longitude", y, x);//получает координаты
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
		sprintf_s(buffer, "Light equipment  with travel speed-50 and power-30 ; \ncoordinates: %f - latitude   %f - longitude", y, x);//получает координаты
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
		sprintf_s(buffer, "Aviation equipment  with travel speed-300 and power-100 ; \ncoordinates: %f - latitude   %f - longitude", y, x);//получает координаты
		cout << buffer << endl;
	}
};

/*
FlyweightFactory - фабрика приспособленцев:
- создает объекты-приспособленцы и управляет ими;
- обеспечивает должное разделение приспособленцев. Когда клиент запрашивает приспособленца,
объект FlyweightFactory предоставляет существующий экземпляр.
*/
class Factory//каждый экзампляр дома будет создаваться в памяти ровно один раз. Берем макет, подставляем координаты в него просто
{
	map<string, Base*> militaryFacilities;//макеты домов уже созданы и не дублируются в памяти больше
public:
	Factory()
	{
		militaryFacilities["light infantry"] = new lightInfantry();//выделили память только для одного дома макета
		militaryFacilities["transport vehicles"] = new transportVehicles();//выделили память только для одного дома макета
		militaryFacilities["heavy equipment"] = new heavyEquipment();//выделили память только для одного дома макета
		militaryFacilities["light equipment"] = new lightEquipment();//выделили память только для одного дома макета
		militaryFacilities["aviation equipment"] = new aviationEquipment();//выделили память только для одного дома макета

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
			return militaryFacilities[key];//возвращает дом
		else
			return nullptr;
	}
};

int main()
{
	/*
	 Client - клиент:
		- хранит ссылки на одного или нескольких приспособленцев;
		- вычисляет или хранит внешнее состояние приспособленцев.
	 */

	double longitude = 37.61;
	double latitude = 55.74;

	Factory*factory = new Factory();



	for (int i = 0; i < 2; i++)
	{
		Base * lightInfantry = factory->GetObj("light infantry");//не создаем а возвращаем просто созданный дом
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