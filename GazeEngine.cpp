// GazeEngine.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "Gaze/gzdk.h"


int main(int argc, char* argv[])
{
  
    gStart(argc, 
        argv, 
        gGameInfo{ "DEMO","0.0.1","D" },
        gWindowInfo{ 120, 120, 800, 800 },
        []() {
            gLoader::init();
            gLoader::load("a", "pen.png",LD_IMAGE);
            gObject* obj;
            gObject* obj2;
            
            gOnCreate([&] {
                gTexture text = gTexture::createColorTexture(0xFF00FFFF, 10, 10);
                gTexture text_ = gTexture::createColorTexture(0xFF00FF00, 10, 10);
                obj = new gObject(0, 0, "a");
                obj2 = new gObject(10, 500, "b");
                obj->setTexture(text);
                obj2->setTexture(text_);

                gPage* p = new gPage();
                p->putObject(obj);
                p->putObject(obj2);
                gGroup* g;
                gSession* s = gSession::newSession([&](gAction* a)->gAction*{
                    a->asFor(obj2);
                    a->moveX(100, 200);
                    a->offset(100);
                    a->spawnObjects(g, 5, obj, [](int i, gv2 v)->gv2 {
                        return gv2{ v.x + i * 12,v.y + i * 12 + 20 };
                        });
                    a->asFors(g);
                    a->offset(10);
                    a->speedY(-0.5, 100);
                    return a;
                    });
                
                p->putSession(s);
                p->startSession();
                
                });

            gOnTick([&](int v) {
                
                });

            gOnKeyDown([&](set<char> c) {
                cout << c.size();
                });
            
        });
    
    return 0;
}

