#pragma once
#include <string>
#include <vector>
#include "Mesh.h"
#include <ASSIMP\Exporter.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

class Model
{
public:
	Model() {};
	Model(string filepath);


	void render(const unsigned int shaderProgram);

	void Export();
	

	static unsigned int TextureFromFile(const char* filepath, const string& directory, bool gamma = false);
	static unsigned int TextureFromFile(const char* filepath, bool gamma = false);
	std::vector<Mesh> &getMesh() { return v_meshes; }
	size_t getMeshCount() { return v_meshes.size(); }
private:
	std::vector<Mesh> v_meshes;
	string directory;
	vector<Texture> v_textures;
	const aiScene *scene;
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
	                                     std::string typeName);
};
