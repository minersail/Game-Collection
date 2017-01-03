#include "stdafx.h"
#include "Keypad.h"

Keypad::Keypad()
	: button1("1", 25, 25), button2("2", 25, 25), button3("3", 25, 25), button4("4", 25, 25),
	button5("5", 25, 25), button6("6", 25, 25), button7("7", 25, 25), button8("8", 25, 25),
	button9("9", 25, 25), button0("0", 25, 25), buttonX("x", 25, 25), buttonVend("v", 75, 50)
{
	center.x = 517;
	center.y = 133;

	button5.SetPosition(center.x, center.y);
	button2.SetPosition(center.x, center.y - 25);
	button8.SetPosition(center.x, center.y + 25);

	button0.SetPosition(center.x, center.y + 50);
	buttonX.SetPosition(center.x - 25, center.y + 50);

	button1.SetPosition(center.x - 25, center.y - 25);
	button4.SetPosition(center.x - 25, center.y);
	button7.SetPosition(center.x - 25, center.y + 25);

	button3.SetPosition(center.x + 25, center.y - 25);
	button6.SetPosition(center.x + 25, center.y);
	button9.SetPosition(center.x + 25, center.y + 25);

	buttonVend.SetPosition(center.x, center.y + 100);
}

void Keypad::Update(float deltaTime, sf::Event ev)
{
	button0.Update(deltaTime, ev);
	button1.Update(deltaTime, ev);
	button2.Update(deltaTime, ev);
	button3.Update(deltaTime, ev);
	button4.Update(deltaTime, ev);
	button5.Update(deltaTime, ev);
	button6.Update(deltaTime, ev);
	button7.Update(deltaTime, ev);
	button8.Update(deltaTime, ev);
	button9.Update(deltaTime, ev);
	buttonX.Update(deltaTime, ev);
	buttonVend.Update(deltaTime, ev);
}

void Keypad::Draw(sf::RenderWindow& rw)
{
	button0.Draw(rw);
	button1.Draw(rw);
	button2.Draw(rw);
	button3.Draw(rw);
	button4.Draw(rw);
	button5.Draw(rw);
	button6.Draw(rw);
	button7.Draw(rw);
	button8.Draw(rw);
	button9.Draw(rw);
	buttonX.Draw(rw);
	buttonVend.Draw(rw);
}

//520 px, 133 px