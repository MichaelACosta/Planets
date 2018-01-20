#include "model.hpp"

Model::Model(){}

Model::Model(char* vertex, char* fragment, char* textura){
    
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders(vertex, fragment);
    
    // Get a handle for our "MVP" uniform
    MatrixID      = glGetUniformLocation(programID, "MVP");
    ViewMatrixID  = glGetUniformLocation(programID, "V");
    ModelMatrixID = glGetUniformLocation(programID, "M");
    
    
    // Load the texture
    Texture = loadDDS(textura);
    //Texture = loadBMP_custom(textura);
    
    // Get a handle for our "myTextureSampler" uniform
    TextureID = glGetUniformLocation(programID, "myTextureSampler");
    
    
    
}

Model::~Model(){}

void Model::SetLight(){
    // Get a handle for our "LightPosition" uniform
    glUseProgram(programID);
    LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
}

void Model::ShaderModel(){
    glUseProgram(programID);
}

void Model::SetDraw(glm::mat4 MVP, glm::mat4 ViewMatrix ){
    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
}

void Model::DrawModel(std::vector<unsigned short> inde){
    // Draw the triangles !
    glDrawElements(
                   GL_TRIANGLES,        // mode
                   inde.size(),      // count
                   GL_UNSIGNED_SHORT,   // type
                   (void*)0             // element array buffer offset
                   );
}

void Model::Light(){
    lightPos = glm::vec3(4, 4, 4);
    glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
}

void Model::TextureM(){
    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    // Set our "myTextureSampler" sampler to user Texture Unit 0
    glUniform1i(TextureID, 0);
}

void Model::CleanPtv(){
    glDeleteProgram(programID);
    glDeleteTextures(1, &Texture);
    glDeleteVertexArrays(1, &VertexArrayID);
}


void Model::SetPvm(){
    //ProjectionMatrix = getProjectionMatrix();
    //ViewMatrix       = getViewMatrix();
    ModelMatrix      = glm::mat4(1.0);
}


/*glm::mat4 Model::GetProjectionMat(){
 //return ProjectionMatrix;
 }
 
 glm::mat4 Model::GetViewMatrix(){
 //return ViewMatrix;
 }*/

glm::mat4 Model::GetModelMatrix(){
    return ModelMatrix;
}

/*void Model::SetProjectionMat(glm::mat4 PM){
 //ProjectionMatrix = PM;
 }
 void Model::SetViewMatrix(glm::mat4 VM){
 //ViewMatrix = VM;
 }*/
void Model::SetModelMatrix(glm::mat4 MM){
    ModelMatrix = MM;
}
