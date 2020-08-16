#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <cstdarg>
#include <string>
#include <thread>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <cmath>
#include <gdi/GdiPlus.h>
#include <GL/glut.h>
#include <soil.h>
#include <functional>
#include <algorithm>
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "SOIL.lib")
using namespace std;
using namespace Gdiplus;
struct gGameInfo {
		string name;
		string version;
		string author;
};
struct gWindowInfo {
		int x, y, width, height;
};
struct gv2 {
		double x, y;
};
struct gvlm {
		int side;
		double** points;
		double** analyzed;
};
struct gbmp {
		int w, h, mode;
		unsigned char* data;
		long color;
};

struct gItem;

class gPage;
class gTexture;
class gObject;
class gRender;
class gWindow;
class gBinder;
class gGroup;
class gAction;
class gLoader;
class gSession;


void gDebug(string str);
void gStart(int argc, char* argv[], gGameInfo info, gWindowInfo info_, void(*callback)());
gGroup* gFindByTag(string tag);
void gOnCreate(function<void()> const& func);
void gOnTick(function<void(int)> const& func);

void gOnKeyDown(function<void(set<char>)> const& func);
void gOnCreateObject(function<void(gObject*)> const &func);
void gOnObjectEffect(function<void(gObject*,gObject*,int)> const& func);
void gOnObjectDisappear(function<void(gObject*)> const& func);
void gBeforeObjectDestroy(function<void(gObject*)> const& func);

long gR(string name);

class gPage {
private:
		vector<gObject*> objs;
		vector<gSession*> sessions;
		static vector<gPage*> pages;
public:
		gPage();
		void putObject(gObject* obj);
		void popSession();
		std::vector<gObject*> getAllObjects();
		std::vector<gSession*> getAllSessions();
		
		static gPage* getShowingPage();
		static bool isAvaliable();
		static void putSession(gSession* session);
		static void startSession();
		
		
};

class gTexture {
private:
		gbmp* value;
public:
		gTexture();
		static gTexture createImageTexture(string res);
		static gTexture createColorTexture(long color, int w, int h);
		static gTexture createTextTexture(string res, int w, int h);
		int getWidth();
		int getHeight();
		long getColor();
		unsigned char* getValue();
		int getType();
};

class gObject {
private:
		gvlm vlm;
		gTexture texture;
		double x, y;
		string tag;
		bool frozen = false;
public:
		gObject();
		gObject(int x, int y);
		gObject(int x, int y, string tag);
		void setX(double x);
		void setY(double y);
		double getX();
		double getY();
		void setVolume(gvlm& vlm);
		gvlm getVolume();
		void setTexture(gTexture texture);
		gTexture getTexture();
		void setTag(string tag);
		string getTag();
		void setFrozen(bool b);
		bool isFrozen();
		
};
class gRender {
public:
		static size_t time;
		static size_t time_li;
		static int turn;
		static void Display();
		static void Tick(int value);
		static void Render(int argc, char* argv[], gGameInfo info, gWindowInfo info_, void(*callback)());
		
};

class gWindow {
public:
		static int width;
		static int height;
		static int x;
		static int y;
		
};

class gGroup {
private:
		static map<string,gGroup**> targeted_groups;
		vector<gObject*> objs;
		double x = 0, y = 0;
public:
		gGroup();
		
		void put(gObject* obj);
		void concat(gGroup group);
		size_t size();
		void foreach(function<void(int i, gObject* obj)> const &func);
		void setX(double x);
		void setY(double y);
		double getX();
		double getY();
		gBinder bind();
		static void setTargetedGroup(string name, gGroup* gA, gGroup* gB);
		static gGroup** getTargetedGroup(string name);
		static void enumTargetedGroups(function<void(string, gGroup**)> func);
		static void removeTargetedGroup(string name);
		
};

class gBinder : gGroup {
private:
		int ox = 0, oy = 0;
public:
		gBinder();
		void moveX(int x);
		void moveY(int y);

};
struct gItem {
		long long goal;
		long long start,end,action,isGroup,val1,val2,val3,val4;
		double db1, db2, db3, db4;
		string str;
};

class gAction {
private:
		long long time_abs = 0;
		vector<gItem> items;
		long long goal;
		int isGroup;
public:
		
		const static int OUTPUT = 0xFF;
		const static int WAIT = 0x00;
		const static int MOVE_X = 0x01;
		const static int MOVE_Y = 0x02;
		const static int SPEED_X = 0x011;
		const static int SPEED_Y = 0x022;
		const static int SCALE_X = 0x03;
		const static int SCALE_Y = 0x04;

		const static int DISAPPEAR = 0x05;
		const static int CLONE_OBJECT = 0x06;
		const static int DESTROY_OBJECT = 0x07;
		const static int DESTROY_GROUP = 0x08;
		const static int MOVE_AS_FUNCTION = 0x09;
		const static int CUSTOM = 0x10;
		const static int GET_POS = 0x0A;
		const static int GET_TIME = 0x0B;
		const static int SPAWN_OBJECT = 0x0C;

		gAction();
		
		void offset(size_t duration);
		void asFor(gObject* obj);
		void asFors(gGroup* group);
		void output(string str);
		void speedX(double speed, int duration);
		void speedY(double speed, int duration);
		void scaleX(int speed, int duration);
		void scaleY(int speed, int duration);
		void moveX(int dx, int duration);
		void moveY(int dy, int duration);
		void moveAsFunc(function<gv2(size_t, gv2)> func, int duration);
		void spawnObjects(gGroup* group, int count, gObject* temp, function<gv2(int, gv2)>);
		void destroyObject(gObject* obj);
		void destroyGroup(gGroup* group);
		void cloneObject(gObject* obj, int x, int y);
		std::vector<gItem> getItems();
};
class gLoader {
private:
		static std::map<std::string, long> stuff;
public:
		const static int IMAGE = 0x00;
		const static int SOUND = 0x01;
		const static int TEXT = 0x02;
		const static int VIDEO = 0x03;
		static void init();
		static void load(string name, string path, int type);
		static long get(string name);
};

class gSession {
private:
		size_t time_total;
		gAction* action;
		gSession();
public:
		static gSession* newSession(function<gAction*(gAction*)> func);
		gAction* getAction();
		size_t getTotalTime();
};
