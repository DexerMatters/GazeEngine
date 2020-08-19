#include "gzdk.h"


gAction::gAction() {}

gAction::~gAction(){

}

void gAction::putItems(gItem item) {
		if (isGroup && goal != NULL)
				((gGroup*)goal)->foreach([&](int i, gObject* obj) {
				item.goal = (long long)obj;
				items.push_back(item);
						});
		else
				items.push_back(item);
}
gAction* gAction::then()
{
		offset(dur);
		return this;
}
gAction* gAction::offset(size_t duration) {
		time_abs += (dur = duration);
		return this;
}
gAction* gAction::asFor(gObject* obj) {
		goal = (long) obj;
		isGroup = 0;
		return this;
}

gAction* gAction::asFors(gGroup* group)
{
		goal = (long)group;
		isGroup = 1;
		return this;
}

gAction* gAction::output(string str)
{
		
		gItem it = { NULL,time_abs,time_abs + 1,AC_OUTPUT };
		it.str = str;
		putItems(it);
		return this;
}
;
gAction* gAction::speedX(double speed, int duration) {
		putItems(gItem{ goal, time_abs, time_abs + (dur = duration),AC_SPEED_X,0,0,0,0,speed });
		return this;
}
gAction* gAction::speedY(double speed, int duration) {
		putItems(gItem{ goal, time_abs, time_abs + (dur = duration),AC_SPEED_Y,0,0,0,0,speed });
		return this;
};
gAction* gAction::scaleX(int speed, int duration) {
		putItems(gItem{ goal, time_abs, time_abs + (dur = duration),AC_SCALE_X,speed });
		return this;
};
gAction* gAction::scaleY(int speed, int duration) {
		putItems(gItem{ goal, time_abs, time_abs + (dur = duration),AC_SCALE_Y,speed });
		return this;
};
gAction* gAction::moveX(int dx, int duration) {
		putItems(gItem{ goal, time_abs, time_abs + (dur = duration),AC_MOVE_X,dx});
		return this;
}
gAction* gAction::moveY(int dy, int duration) {
		putItems(gItem{ goal, time_abs, time_abs + (dur = duration),AC_MOVE_Y,dy});
		return this;
};
gAction* gAction::moveAsFunc(function<gv2(size_t, gv2)> func, int duration) {
		function<gv2(size_t, gv2)>* func_ = new function<gv2(size_t, gv2)>(func);
		putItems(gItem{ goal, time_abs, time_abs,AC_GET_POS });
		putItems(gItem{ goal, time_abs, time_abs,AC_GET_TIME });
		putItems(gItem{ goal, time_abs, time_abs + (dur = duration),AC_MOVE_AS_FUNCTION,(long long)func_});
		return this;
}
gAction* gAction::spawnObjects(gGroup*& group, int count, gObject* temp, function<gv2(int, gv2)> func)
{
		group = new gGroup();
		function<gv2(int, gv2)>* func_ = new function<gv2(int, gv2)>(func);
		for (int i = 0; i < count; i++)
				group->put(new gObject(*temp));
		putItems(gItem{ goal, time_abs, time_abs+1,AC_GET_POS});
		putItems(gItem{ goal, time_abs, time_abs+1,AC_SPAWN_OBJECT, (long long)group,(long long)func_ });
		return this;
}
gAction* gAction::spawnObjects(gGroup*& group, int count, gObject* temp)
{
		group = new gGroup();
		function<gv2(int, gv2)>* func_ = new function<gv2(int, gv2)>([&](int i, gv2 p)->gv2{
				return p;
				});
		for (int i = 0; i < count; i++)
				group->put(new gObject(*temp));
		putItems(gItem{ goal, time_abs, time_abs,AC_GET_POS });
		putItems(gItem{ goal, time_abs, time_abs+1,AC_SPAWN_OBJECT, (long long)group,(long long)func_ });
		return this;
}
gAction* gAction::destroyObject(gObject* obj) {
		putItems(gItem{ goal, time_abs, time_abs,AC_DESTROY_OBJECT,(long long)obj });
		return this;
};
gAction* gAction::destroyGroup(gGroup* group) {
		putItems(gItem{ goal, time_abs, time_abs ,AC_DESTROY_GROUP,(long long)group });
		return this;
};
gAction* gAction::cloneObject(gObject* obj, int x, int y) {
		putItems(gItem{ goal, time_abs, time_abs ,AC_CLONE_OBJECT,(long long)obj,x,y });
		return this;
};
std::vector<gItem> gAction::getItems() {
		return items;
};