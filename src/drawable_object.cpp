#include "drawable_object.h"

void DrawableObject::draw(){
    //função abstrata (virtual)
}

void DrawableObject::translate(GLfloat delX, GLfloat delY, GLfloat delZ){
    tx += delX;
    ty += delY;
    tz += delZ;
}

void DrawableObject::rotate(GLfloat deg){
    rot_y += deg;
    if(rot_y >= 360) rot_y -= 360;
    if(rot_y < 0) rot_y += 360;
}

void DrawableObject::scale(GLfloat multX, GLfloat multY, GLfloat multZ){
    sx *= multX;
    sy *= multY;
    sz *= multZ;
}
