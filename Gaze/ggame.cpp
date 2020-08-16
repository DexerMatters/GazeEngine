#include "gzdk.h"
#include "gzak.h"
int gWindow::width;
int gWindow::height;
int gWindow::x;
int gWindow::y;
size_t gRender::time = -1;
size_t gRender::time_li = 0;
size_t time_abs = 0;
int gRender::turn = 0;
bool created = false;
bool keydown = false;
set<char> keys;
function<void()> on_create;
function<void(int)> on_tick;
function<void(int)> on_;
function<void(std::set<char>)> on_keydown;
function<void(gObject*)> on_create_object;
function<void(gObject*, gObject*, int)> on_object_effect;
function<void(gObject*)> on_object_disappear;
function<void(gObject*)> before_object_destroy;

// output

void cprintf(const char* str, WORD color) {
    WORD colorOld;
    HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(handle, &csbi);
    colorOld = csbi.wAttributes;
    SetConsoleTextAttribute(handle, color);
    
    cout << str;
    SetConsoleTextAttribute(handle, colorOld);
}


//preset functions

void gDebug(string str) {
    time_t time_now;
    struct tm p;
    time(&time_now);
    localtime_s(&p, &time_now);
    stringstream ss;
    ss << "["
        << p.tm_hour << ":"
        << p.tm_min << ":"
        << p.tm_sec << "]"
        << " ";
    cprintf(ss.str().c_str(), 2);
    cprintf((str + "\n").c_str(), 1 | 2 | 4);
}

void gStart(int argc, char* argv[], gGameInfo info, gWindowInfo info_, void(*callback)()) {
    callback();
    gRender::Render(argc, argv, info, info_, callback);

}

gGroup* gFindByTag(string tag) {
    vector<gObject*> objs = gPage::getShowingPage()->getAllObjects();
    gGroup* g = new gGroup();
    for (size_t i = 0; i < objs.size(); i++)
        if (objs[i]->getTag() == tag)
            g->put(objs[i]);
    return g;
}

void gOnCreate(function<void()> const& func) {
    on_create = func;
}
void gOnTick(function<void(int)> const& func) {
    on_tick = func;
}
void gOnKeyDown(function<void(set<char>)> const& func) {
    on_keydown = func;
}

void gOnCreateObject(function<void(gObject*)> const& func) {
    on_create_object = func;
}
void gOnObjectEffect(function<void(gObject*, gObject*, int)> const& func)
{
    on_object_effect = func;
}
void gOnObjectDisappear(function<void(gObject*)> const& func) {
    on_object_disappear = func;
};
void gBeforeObjectDestroy(function<void(gObject*)> const& func) {
    before_object_destroy = func;
}

long gR(string name)
{
    return gLoader::get(name);
}

float cx(double x) {
    float ww = gWindow::width;
    return x / (ww - ww / 2.0) < 1 ? x / (ww - ww / 2.0) : (x / (ww - ww / 2.0) - 1) * -1;
}
float cy(double y) {
    float wh = gWindow::height;
    return y / (wh - wh / 2.0) < 1 ? y / (wh - wh / 2.0) : (y / (wh - wh / 2.0) - 1) * -1;
}
void gRender::Tick(int i) {
    glutPostRedisplay();
    if (keydown)
        on_keydown(keys);
    if (created) {
        gGroup::enumTargetedGroups([&](string key, gGroup** v) {
            v[0]->foreach([=](int i, gObject* obj1) {
                v[1]->foreach([=](int j, gObject* obj2) {
                    gvlm v1 = obj1->getVolume(),
                        v2 = obj2->getVolume();
                    
                    if (getRelation(
                        moveLine(v1.analyzed, v1.side, obj1->getX(), obj1->getY()), 
                        v1.side, 
                        moveLine(v2.analyzed, v2.side, obj2->getX(), obj2->getY()), v2.side))
                        on_object_effect(obj1, obj2, 0);
                    });
                });
            });
    }
    glutTimerFunc(10, gRender::Tick, 1);
}
void gRender::Display() {
		glClear(GL_COLOR_BUFFER_BIT);

    if (!created) return;
    if (!gPage::isAvaliable()) return;

    time_abs++;
    on_tick(time_abs);

    gPage* p = gPage::getShowingPage();

    if (gRender::time != (size_t)-1) {
        size_t time_needed = p->getAllSessions()[0]->getTotalTime();

        if (gRender::time == time_needed) {
            gRender::time = 0;

            p->popSession();
            if (p->getAllSessions().size() == 0) {
                gRender::time = -1;
            }
        }
    }

    vector<gObject*> objs = p->getAllObjects();
    double ox = 0, oy = 0;
    size_t time_rel = 0;
    if (gRender::time != (size_t)-1) {
        vector<gItem> its = p->getAllSessions()[0]->getAction()->getItems();

        for (size_t i = 0; i < its.size(); i++) {
            gObject* o = nullptr;
            gGroup* g = nullptr;
            if (its[i].isGroup)
                g = (gGroup*)its[i].goal;
            o = (gObject*) its[i].goal;

            if (gRender::time >= its[i].start && gRender::time <= its[i].end) {
                switch (its[i].action) {
                case gAction::OUTPUT:
                    gDebug(its[i].str);
                    break;
                case gAction::GET_POS:
                    if (its[i].isGroup) {
                        ox = g->getX();
                        oy = g->getY();
                    }
                    else {
                        ox = o->getX();
                        oy = o->getY();
                    }
                    break;
                case gAction::GET_TIME:
                    time_rel = gRender::time;
                    break;
                case gAction::SPEED_X:
                    if (its[i].isGroup)
                        g->setX(g->getX() + its[i].db1);
                    else
                        o->setX(o->getX() + its[i].db1);
                    break;
                case gAction::SPEED_Y:
                    if (its[i].isGroup)
                        g->setY(g->getY() + its[i].db1);
                    else
                        o->setY(o->getY() + its[i].db1);
                    break;
                case gAction::MOVE_X:
                    o->setX(o->getX() + its[i].val1/(double)(its[i].end- its[i].start));
                    break;
                case gAction::MOVE_Y:
                    o->setY(o->getY() + its[i].val1 / (double)(its[i].end - its[i].start));
                    break;
                case gAction::MOVE_AS_FUNCTION: {
                    function<gv2(size_t, gv2)>* func =(function<gv2(size_t, gv2)>*) its[i].val1;
                    gv2 point = (*func)(gRender::time - time_rel, gv2{ ox,oy });
                    o->setX(point.x);
                    o->setY(point.y);
                    break;
                };
                default:
                    break;
                }
            }
        }
        gRender::time++;
    }

    

    for (register size_t i = 0; i < objs.size(); i++) {
        register gObject* o = objs[i];

        register float ox = o->getX();
        register float oy = o->getY();
        register gTexture tex = o->getTexture();
        if (tex.getType()) {
            Color color = Color(tex.getColor());
            glColor4ub(color.GetR(), color.GetG(), color.GetB(), color.GetA());
            glRectf(cx(ox), cy(oy), cx(ox + tex.getWidth()), cy(oy + tex.getHeight()));
        }
        else {
            glBindTexture(GL_TEXTURE_2D, (GLuint) tex.getValue());
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex2f(0, 0);
            glTexCoord2f(1.0f, 0.0f);
            glVertex2f(tex.getWidth(), 0);
            glTexCoord2f(1.0f, 1.0f);
            glVertex2f(tex.getWidth(), tex.getHeight());
            glTexCoord2f(0.0f, 1.0f);
            glVertex2f(0.0f, tex.getHeight());
            glEnd();
        }
    };
    
    

		glFlush();
}

void KeyUp(unsigned char c, int x, int y) {
    keys.erase(c);
    keydown = false;
}
void Key(unsigned char c, int x, int y) {
    if (!keydown) {
        keys.insert(c);
        keydown = true;
    }
}
void gRender::Render(int argc, char* argv[], gGameInfo info, gWindowInfo info_, void(*callback)()) {

		glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(info_.x, info_.y);
    glutInitWindowSize(info_.width, info_.height);
    glutCreateWindow(info.name.c_str());
    gWindow::x = info_.x;
    gWindow::y = info_.y;
    gWindow::width = info_.width;
    gWindow::height = info_.height;
    on_create();
    created = true;
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(gRender::Display);
    glutKeyboardUpFunc(KeyUp);
    glutKeyboardFunc(Key);
    glutTimerFunc(10, gRender::Tick, 1);
    glutMainLoop();
}