// GazeEngine.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "Gaze/gzdk.h"


int main(int argc, char* argv[])
{
  
    gStart(argc, 
        argv, 
        gGameInfo{ "DEMO","0.0.1","D" },
        gWindowInfo{ 120, 120, 600, 600 },
        []() {
            gLoader::init();
            gLoader::load("a", "pen.png",gLoader::IMAGE);
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

                gSession* s = gSession::newSession([=](gAction* a)->gAction*{
                    a->asFor(obj2);
                    a->moveAsFunc([](size_t t, gv2 p)->gv2 {
                        return { p.x + t*0.3,p.y+ t*0.5 };
                        }, 500);
                    return a;
                    });
                
                p->putSession(s);
                p->startSession();
                double** d = new double*[4];
                double d0[4][2] = { {0,0},{0,60},{60,60},{60,0} };
                for (int i = 0; i < 4; i++) {
                    d[i] = new double[2];
                    d[i][0] = d0[i][0];
                    d[i][1] = d0[i][1];
                }
                gvlm v = {4,d};
                obj->setVolume(v);
                obj2->setVolume(v);
                });

            gOnTick([&](int v) {
                
                });

            gOnKeyDown([&](set<char> c) {
                cout << c.size();
                });
            
        });
    
    return 0;
}

