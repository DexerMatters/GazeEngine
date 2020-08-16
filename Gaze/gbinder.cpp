#include "gzdk.h"


gBinder::gBinder() {
		gGroup();
}
void gBinder::moveX(int x) {
		ox = x;
		foreach([=](int i, gObject* obj) {
				obj->setX(obj->getX()+ox);
				});
}
void gBinder::moveY(int y) {
		oy = y;
		foreach([=](int i, gObject* obj) {
				obj->setY(obj->getY() + oy);
				});
}
