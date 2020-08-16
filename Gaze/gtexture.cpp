#include "gzdk.h"
gTexture::gTexture() {

}
gTexture gTexture::createImageTexture(string res) {
		gTexture t;
		t.value = (gbmp*)gR(res);

		return t;
}

gTexture gTexture::createColorTexture(long color, int w, int h)
{
		
		gTexture t;
		t.value = new gbmp{ w,h,1,NULL,color };
		return t;
}
gTexture gTexture::createTextTexture(string res, int w, int h)
{
		return gTexture();
}

int gTexture::getWidth()
{
		return value->w;
}

int gTexture::getHeight()
{
		return value->h;
}

long gTexture::getColor()
{
		return value->color;
}

unsigned char* gTexture::getValue()
{
		return value->data;
}

int gTexture::getType()
{
		return value->mode;
}
