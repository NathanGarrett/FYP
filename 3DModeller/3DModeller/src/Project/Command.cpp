#include <Project\Command.h>

void Command::MirrorGeometryXY(Model * model, float zOffset)
{
		//std::cout <<"size of v_meshes before: "<< model->getMeshCount() << std::endl;
		//create data buffers
		std::vector<Vertex> newVerts;
		std::vector<unsigned int> newIndices;
		std::vector<Texture> newTextures;
		size_t NewVertsSize = 0;
		size_t NewIndicesSize = 0;
		size_t NewTexturesSize = 0;
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
				//std::cout << "finPos: " << newVerts[i].position.x << " " << newVerts[i].position.y << " " << newVerts[i].position.z << "\n" << std::endl;

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

void Command::ExtrudeFace(Model * model, int v1, int v2, int v3, glm::vec3 mag)
{

	//glm::mat4 Extrude =
	//{	1+mag.x,       0,        0,		    0,
	//	   0,		1+mag.y,     0,			0,
	//	   0,		   0,	   1+mag.z,		0,
	//	   0,		   0,        0,			1 };
	glm::mat4 Extrude =
	{	   1,   0,    0,   mag.x,
		   0,	1,    0,   mag.y,
		   0,	0,    1,   mag.z,
		   0,	0,    0,	1 };

	//Mesh newMesh(model->getMesh()[0]);
	glm::vec3 posA = model->getMesh()[0].vertices[v1].position;
	glm::vec3 posB = model->getMesh()[0].vertices[v2].position;
	glm::vec3 posC = model->getMesh()[0].vertices[v3].position;
	//glm::vec3 norm = glm::cross((posA-posB), (posA - posC));
	
	posA = handler.MAT_VEC_MULT(posA, Extrude);
	posB = handler.MAT_VEC_MULT(posB, Extrude);
	posC = handler.MAT_VEC_MULT(posC, Extrude);

	model->getMesh()[0].vertices[8].position = posA;
	//model->getMesh()[0].vertices[v2].position = posB;
	//model->getMesh()[0].vertices[v3].position = posC;
	model->getMesh()[0].setupMesh();
	
	std::cout << "Extrude face Done" <<std::endl;

}

void Command::BevelObject(Model * model, float offset)
{
	/*
	steps:
	1. Duplicate the verts
	2. 
	3.
	4.
	5.
	*/
}
void Command::CommitTransform(Model * model, glm::mat4 modmat)
{
	for (int i = 0; i < model->getMeshCount(); i++)
	{
		for (int j = 0; j < model->getMesh()[i].vertices.size(); j++)
		{
			glm::vec3 pos = model->getMesh()[i].vertices[j].position;
			model->getMesh()[i].vertices[j].position = handler.MAT_VEC_MULT(pos, modmat);
		}
	}
}
////////////////////////////////////////////////////////////
//NB:On save, multiply model matrix per vertex then export//
////////////////////////////////////////////////////////////