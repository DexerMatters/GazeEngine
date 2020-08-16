#include "gzdk.h"

map<string, gGroup**> gGroup::targeted_groups = map<string, gGroup**>();

gGroup::gGroup() {
		vector<gObject*>();
};
void gGroup::put(gObject* obj) {
		objs.push_back(obj);
}
void gGroup::concat(gGroup group) {
		for (size_t i = 0; i < group.objs.size(); i++)
				objs.push_back(group.objs[i]);
}
size_t gGroup::size() {
		return objs.size();
}
void gGroup::foreach(function<void(int i, gObject * obj)> const& func) {
		for (size_t i = 0; i < size(); i++)
				if(!objs[i]->isFrozen())
						func(i, objs[i]);
}
void gGroup::setX(double x) {
		this->x = x;
		this->foreach([=](int i, gObject* obj) {
				obj->setX(x);
				});
};
void gGroup::setY(double y) {
		this->y = y;
		this->foreach([=](int i, gObject* obj) {
				obj->setY(y);
				});
};
double gGroup::getX() {
		return x;
};
double gGroup::getY() {
		return y;
};
gBinder gGroup::bind() {
		return *(gBinder*)this;
}
void gGroup::setTargetedGroup(string name, gGroup* gA, gGroup* gB)
{
		targeted_groups[name] = new gGroup * [2]{gA,gB};
}
gGroup** gGroup::getTargetedGroup(string name)
{
		return targeted_groups[name];
}
void gGroup::enumTargetedGroups(function<void(string, gGroup**)> func)
{
		for (auto it : targeted_groups)
				func(it.first, it.second);
}
void gGroup::removeTargetedGroup(string name)
{
		targeted_groups.erase(name);
}
;

