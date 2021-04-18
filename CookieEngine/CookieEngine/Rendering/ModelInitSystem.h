#pragma once
//#include "ModelData.h"
//#include "../ECS/World.h"
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//
//namespace cookie
//{
//	class ModelInitSystem : public System
//	{
//		
//	public:
//		virtual void Update(World* world) override
//		{
//			auto query { world->QueryEntities<ModelData>() };
//			query->Foreach([](auto& model)
//				{
//					if (!model.loaded)
//					{
//						loadModel(model);
//					}
//					
//				});
//		}
//
//	private:
//		void loadModel(ModelData& model)
//		{
//			Assimp::Importer importer;
//			const aiScene* scene = importer.ReadFile(model.path, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//			{
//				std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << '\n';
//				return;
//			}
//			model.directory = model.path.substr(0, model.path.find_last_of('/'));
//			//processNode(scene->mRootNode, scene);
//
//		}
//	};
//}