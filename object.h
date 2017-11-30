#pragma once

class object {
public:
	virtual void draw() const = 0;
	virtual void update(double dt) = 0;
	virtual void setx(double newx) = 0;
	virtual void sety(double newy) = 0;

private:
	double y;
	double x;
};
