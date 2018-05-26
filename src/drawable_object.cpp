#include "drawable_object.h"

void DrawableObject::draw(){
    //função abstrata (virtual)
}

void DrawableObject::translate(GLfloat delX, GLfloat delY){
    tx += delX;
    ty += delY;
}

void DrawableObject::rotate(GLfloat deg){
    rot += deg;
    if(rot >= 360) rot -= 360;
    if(rot < 0) rot += 360;
}

void DrawableObject::scale(GLfloat multX, GLfloat multY){
    sx *= multX;
    sy *= multY;
}
