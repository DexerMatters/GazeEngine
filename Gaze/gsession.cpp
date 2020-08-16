#include "gzdk.h"
gSession::gSession() {};
gSession* gSession::newSession(function<gAction * (gAction*)> func) {
		gSession* s = new gSession();
		s->action = func(new gAction());
		vector<gItem> items = s->action->getItems();
		size_t time = 0;
		for (size_t i = 0; i < items.size(); i++)
				if (items[i].end > 0)
						time = items[i].end;
		s->time_total = time;
		return s;
}
gAction* gSession::getAction() {
		return action;
};
size_t gSession::getTotalTime() {
		return time_total;
}