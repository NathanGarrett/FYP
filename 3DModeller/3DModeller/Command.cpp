#include <Project\Command.h>

void Command::MirrorGeometryXY(Model * model, float zOffset)
{
		std::cout <<"size of v_meshes before: "<< model->getMeshCount() << std::endl;
		//create data buffers
		std::vector<Vertex> newVerts;
		std::vector<unsigned int> newIndices;
		std::vector<Texture> newTextures;
		float NewVertsSize = 0;
		float NewIndicesSize = 0;
		float NewTexturesSize = 0;
		//find total number of verts on the model
		for (int i = 0; i < model->getMeshCount(); i++)
		{
			NewVertsSize += model->getMesh()[i].vertices.size();
			NewIndicesSize += model->getMesh()[i].indices.size();
			NewTexturesSize += model->getMesh()[i].textures.size();
		}
		newVerts.resize(NewVertsSize);
		newIndices.reserve(NewIndicesSize);
		newTextures.reserve(NewTexturesSize);
		//assign new vertices
		for (int j = 0; j < model->getMeshCount(); j++)
		{
			for (int i = 0; i < model->getMesh()[j].vertices.size(); i++)
			{

				glm::vec3 newPos = handler.MAT_VEC_MULT(model->getMesh()[j].vertices[i].position, reflectXY);
				newVerts[i].position.x = newPos.x;
				newVerts[i].position.y = newPos.y;
				//when j is even its fine when j is odd it is not fine
				if (j % 2 == 1) 
				{
					newVerts[i].position.z = newPos.z + zOffset + (zOffset *(j + 1) );
				}
				else
				{ 
					newVerts[i].position.z = newPos.z + zOffset + (zOffset *j); 
				}	
				newVerts[i].normal = model->getMesh()[j].vertices[i].normal;
				newVerts[i].textureCoords = model->getMesh()[j].vertices[i].textureCoords;
				//print out new vert pos
				std::cout << "finPos: " << newVerts[i].position.x << " " << newVerts[i].position.y << " " << newVerts[i].position.z << "\n" << std::endl;

			}
			//assign new indices
			for (int i = 0; i < model->getMesh()[j].indices.size(); i++)
			{
				newIndices.push_back(model->getMesh()[j].indices[i]);
			}
			//assign new textures
			for (int i = 0; i < model->getMesh()[j].textures.size(); i++)
			{
				newTextures.push_back(model->getMesh()[j].textures[i]);
			}
		}
		//create new mesh
		Mesh newMesh(newVerts, newIndices, newTextures);
		model->getMesh().push_back(newMesh); //push new mesh onto the model
		
		std::cout << "Mirror-XY Done, v_meshes size: "<< model->getMeshCount()<< std::endl;
}

void Command::MirrorGeometryYZ(Model * model, float xOffset)
{
	std::cout << "size of v_meshes before: " << model->getMeshCount() << std::endl;
	std::vector<Vertex> newVerts;
	newVerts.resize(model->getMesh()[0].vertices.size());
	for (int i = 0; i < model->getMesh()[0].vertices.size(); i++)
	{

		glm::vec3 newPos = handler.MAT_VEC_MULT(model->getMesh()[0].vertices[i].position, reflectYZ);
		newVerts[i].position.x = newPos.x + xOffset;
		newVerts[i].position.y = newPos.y;
		newVerts[i].position.z = newPos.z;
		newVerts[i].normal = model->getMesh()[0].vertices[i].normal;
		newVerts[i].textureCoords = model->getMesh()[0].vertices[i].textureCoords;
		//print out new vert pos
		std::cout << "finPos: " << newVerts[i].position.x << " " << newVerts[i].position.y << " " << newVerts[i].position.z << "\n" << std::endl;

	}
	Mesh newMesh(newVerts, model->getMesh()[0].indices, model->getMesh()[0].textures);
	model->getMesh().push_back(newMesh); //copy the values from the zero'th mesh vector to the first mesh vector, except verts which we're gonna change

	std::cout << "Mirror-YZ Done, v_meshes size: " << model->getMeshCount() << std::endl;
}

void Command::MirrorGeometryZX(Model * model, float yOffset)
{
	std::cout << "size of v_meshes before: " << model->getMeshCount() << std::endl;
	std::vector<Vertex> newVerts;
	newVerts.resize(model->getMesh()[0].vertices.size());
	for (int i = 0; i < model->getMesh()[0].vertices.size(); i++)
	{

		glm::vec3 newPos = handler.MAT_VEC_MULT(model->getMesh()[0].vertices[i].position, reflectZX);
		newVerts[i].position.x = newPos.x;
		newVerts[i].position.y = newPos.y + yOffset;
		newVerts[i].position.z = newPos.z;
		newVerts[i].normal = model->getMesh()[0].vertices[i].normal;
		newVerts[i].textureCoords = model->getMesh()[0].vertices[i].textureCoords;
		//print out new vert pos
		std::cout << "finPos: " << newVerts[i].position.x << " " << newVerts[i].position.y << " " << newVerts[i].position.z << "\n" << std::endl;

	}
	Mesh newMesh(newVerts, model->getMesh()[0].indices, model->getMesh()[0].textures);
	model->getMesh().push_back(newMesh); //copy the values from the zero'th mesh vector to the first mesh vector, except verts which we're gonna change

	std::cout << "Mirror-XY Done, v_meshes size: " << model->getMeshCount() << std::endl;
}
