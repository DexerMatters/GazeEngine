#include "gzdk.h"
vector<gPage*> gPage::pages=vector<gPage*>();
gPage::gPage() {
		gPage::pages.push_back(this);
}
void gPage::putObject(gObject* obj) {
		objs.push_back(obj);
}
std::vector<gObject*> gPage::getAllObjects() {
		return objs;
}
gPage* gPage::getShowingPage() {
		return gPage::pages[pages.size() - 1];
};
bool gPage::isAvaliable() {
		return pages.size() != 0;
};
void gPage::putSession(gSession* session) {
		getShowingPage()->sessions.push_back(session);
};
void gPage::startSession() {
		gRender::time = 0;
};
std::vector<gSession*> gPage::getAllSessions() {
		return sessions;
}
void gPage::popSession() {
		sessions.erase(sessions.begin());
}