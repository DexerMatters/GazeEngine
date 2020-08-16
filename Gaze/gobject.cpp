#include "gzdk.h"
#include "gzak.h"
gObject::gObject() {
		x = 0; y = 0;
}
gObject::gObject(int x, int y) {
		this->x = x;
		this->y = y;
}
gObject::gObject(int x, int y, string tag) {
		this->x = x;
		this->y = y;
		this->tag = tag;
}
void gObject::setX(double x) {
		this->x = x;
};
void gObject::setY(double y) {
		this->y = y;
};
double gObject::getX() {
		return x;
};
double gObject::getY() {
		return y;
}
void gObject::setVolume(gvlm& vlm)
{
		
		gvlm g = vlm;
		analyze(g.analyzed, g.points, g.side);
		this->vlm = vlm = g;
}

gvlm gObject::getVolume()
{
		return vlm;
}

void gObject::setTexture(gTexture texture)
{
		this->texture = texture;
}

gTexture gObject::getTexture()
{
		return texture;
}

void gObject::setTag(string tag) {
		this->tag = tag;
}

string gObject::getTag() {
		return tag;
}

void gObject::setFrozen(bool b) {
		frozen = b;
};
bool gObject::isFrozen() {
		return frozen;
};

