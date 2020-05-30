#pragma once
#include <GL/freeglut.h>
#include <glm.hpp>

class Light { // Abstract class
protected:
    static GLuint cont; // Atributo para poder generar un nuevo id cada vez
    GLuint id = GL_LIGHT0 + GL_MAX_LIGHTS; // Primer id no v�lido
    // Atributos lum�nicos y geom�trico de la fuente de luz
    glm::fvec4 ambient = { 0.1, 0.1, 0.1, 1 };
    glm::fvec4 diffuse = { 0.5, 0.5, 0.5, 1 };
    glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
    glm::fvec4 posDir = { 0, 0, 1, 0 };
   
public:
    Light();
    virtual ~Light() { disable(); cont--; }
    void uploadL()const;
    // M�todo abstracto
    virtual void upload(glm::dmat4 const& modelViewMat) const = 0;
    // A�ade setter�s para cambiar el valor de los atributos lum�nicos
    void disable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glDisable(id); };
    void enable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glEnable(id); };
    void setAmb(glm::fvec4 amb) { ambient = amb; uploadL(); };
    void setDiff(glm::fvec4 diff) { diffuse = diff; uploadL(); };
    void setSpec(glm::fvec4 spec) { specular = spec; uploadL(); };
    
};
class DirLight : public Light {
public:
    virtual void upload(glm::dmat4 const& modelViewMat) const;
    void setPosDir(glm::fvec3 dir);
};
class PosLight : public Light {
protected:
    // Factores de atenuaci�n
    GLfloat kc = 1, kl = 0, kq = 0;
public:
    virtual void upload(glm::dmat4 const& modelViewMat) const;
    void setPosDir(glm::fvec3 dir);
    void setAtte(GLfloat kc, GLfloat kl, GLfloat kq);
};
class SpotLight : public PosLight {
protected:
    // Atributos del foco
    glm::fvec4 direction = { 0, 0, -1, 0 };
    GLfloat cutoff = 180;
    GLfloat exp = 0;
public:
    SpotLight(glm::fvec3 pos = { 0, 0, 0 })
        : PosLight() {
        posDir = glm::fvec4(pos, 1.0);
    };
    virtual void upload(glm::dmat4 const& modelViewMat) const;
    void setSpot(glm::fvec3 dir, GLfloat cf, GLfloat e);
    void setCutoff(GLfloat cf) { cutoff = cf; };
    void setExp(GLfloat e) { exp = e; };
    void setDir(glm::fvec3 dir) { direction = glm::fvec4(dir, 0.0);  };
};




