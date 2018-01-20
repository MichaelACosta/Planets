#ifndef MESH_HPP
#define MESH_HPP

#include <stdio.h>
#include <stdlib.h>
#include <vector>




// Include GLEW
#include <GL/glew.h>



// Include GLM
#include <glm/glm.hpp>

#include <vboindexer.hpp>
#include <objloader.hpp>


using namespace glm;


class Mesh{
public:
    
    Mesh();
    ~Mesh();
    
    void SetMesh(char* obj);
    
    std::vector<glm::vec3> GetVertices();
    std::vector<glm::vec2> GetUvs();
    std::vector<glm::vec3> GetNormals();
    
    std::vector<unsigned short> GetIndices();
    std::vector<glm::vec3> GetIndexed_vertices();
    std::vector<glm::vec2> GetIndexed_uvs();
    std::vector<glm::vec3> GetIndexed_normals();
    
    void LoadVbo();
    void SetBuffer();
    void CleanVbo();
    
private:
    
    bool res;
    
    // Read our .obj file
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    
    std::vector<unsigned short> indices;
    std::vector<glm::vec3> indexed_vertices;
    std::vector<glm::vec2> indexed_uvs;
    std::vector<glm::vec3> indexed_normals;
    
    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint normalbuffer;
    GLuint elementbuffer;
    
};



#endif
