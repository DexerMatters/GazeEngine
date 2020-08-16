#include "gzdk.h"
#include "gzak.h"
map<string, long> gLoader::stuff = map<string, long>();
thread thr_pool[2048];

void gLoader::init() {
		stuff = map<string, long>();
};
void gLoader::load(string name, string path, int type) {
		switch (type) {
		case IMAGE: {
				
				GdiplusStartupInput gdiplusstartupinput;
				ULONG_PTR gdiplustoken;
				GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, NULL);

				wstring path_=s2w(path);
				Bitmap* bmp = new Bitmap(path_.c_str());
				int w = bmp->GetWidth(),
						h = bmp->GetHeight();
				UCHAR* datac;
				BitmapData data;
				bmp->LockBits(Gdiplus::Rect(0, 0, w, h), ImageLockModeRead, PixelFormat32bppARGB, &data);
				datac = (UCHAR*)data.Scan0;
				stuff[name] = (long) new gbmp{ w,h,0,datac };
				delete bmp;
				GdiplusShutdown(gdiplustoken);

				break;
		}
		case TEXT: {

		}
		default:
				break;
		}
}
long gLoader::get(string name)
{
		return stuff[name];
}
;
