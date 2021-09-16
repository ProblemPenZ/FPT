#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>

class Object {
private:
SDL_Rect dest;
SDL_Rect src;
SDL_Texture* tex;
bool sTop;
bool sSide;
int id;
public:
Object() {sTop=1; sSide=1;}
SDL_Rect getDest() const {return dest;}
SDL_Rect getSource() const {return src;}
void setDest(int x, int y, int w, int h);
void setDest(int x, int y);
void setSource(int x, int y, int w, int h);
void setImage(string filename, SDL_Renderer* ren);
SDL_Texture* getTex() const {return tex;}
void setsTop(bool s) {sTop=s;}
void setsSide(bool s) {sSide=s;}
bool getsTop()const {return sTop;}
bool getsSide()const {return sSide;}
int getDX() const {return dest.x;}
int getDY() const {return dest.y;}
int getDW() const {return dest.w;}
int getDH() const {return dest.h;}
void setId(int i) {id=i;}
int getId() const {return id;}
};


#endif //OBJECT_H
