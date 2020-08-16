#include "gzdk.h"

gAction::gAction() {}
void gAction::offset(size_t duration) {
		time_abs += duration;
}
void gAction::asFor(gObject* obj) {
		goal = (long) obj;
		isGroup = 0;
}

void gAction::asFors(gGroup* group)
{
		goal = (long)group;
		isGroup = 1;
}

void gAction::output(string str)
{
		
		gItem it = { NULL,time_abs,time_abs,OUTPUT };
		it.str = str;
		items.push_back(it);
}
;
void gAction::speedX(double speed, int duration) {
		items.push_back(gItem{ goal, time_abs, time_abs + duration,SPEED_X,isGroup,0,0,0,0,speed });
}
void gAction::speedY(double speed, int duration) {
		items.push_back(gItem{ goal, time_abs, time_abs + duration,SPEED_Y,isGroup,0,0,0,0,speed });
};
void gAction::scaleX(int speed, int duration) {
		items.push_back(gItem{ goal, time_abs, time_abs + duration,SCALE_X,isGroup,speed });
};
void gAction::scaleY(int speed, int duration) {
		items.push_back(gItem{ goal, time_abs, time_abs + duration,SCALE_Y,isGroup,speed });
};
void gAction::moveX(int dx, int duration) {
		items.push_back(gItem{ goal, time_abs, time_abs + duration,MOVE_X,isGroup,dx});
}
void gAction::moveY(int dy, int duration) {
		items.push_back(gItem{ goal, time_abs, time_abs + duration,MOVE_Y,isGroup,dy});
};
void gAction::moveAsFunc(function<gv2(size_t, gv2)> func, int duration) {
		function<gv2(size_t, gv2)>* func_ = new function<gv2(size_t, gv2)>(func);
		items.push_back(gItem{ goal, time_abs, time_abs,GET_POS,isGroup });
		items.push_back(gItem{ goal, time_abs, time_abs,GET_TIME,isGroup });
		items.push_back(gItem{ goal, time_abs, time_abs + duration,MOVE_AS_FUNCTION,isGroup,(long long)func_});
}
void gAction::spawnObjects(gGroup* group, int count, gObject* temp, function<gv2(int, gv2)>)
{
		
}
void gAction::destroyObject(gObject* obj) {
		items.push_back(gItem{ goal, time_abs, time_abs,DESTROY_OBJECT,isGroup,(long long)obj });
};
void gAction::destroyGroup(gGroup* group) {
		items.push_back(gItem{ goal, time_abs, time_abs ,DESTROY_GROUP,isGroup,(long long)group });
};
void gAction::cloneObject(gObject* obj, int x, int y) {
		items.push_back(gItem{ goal, time_abs, time_abs ,CLONE_OBJECT,isGroup,(long long)obj,x,y });
};
std::vector<gItem> gAction::getItems() {
		return items;
};