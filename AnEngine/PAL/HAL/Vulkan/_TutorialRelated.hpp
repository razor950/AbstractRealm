#pragma once



// Engine
#include "Vulkan_API.hpp"

// Tutorial
#include "Renderer/Shader/TriangleShader/TriangleShader.hpp"
#include "Renderer/Shader/VKTut/VKTut.hpp"

// Raw Libraries
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <tiny_obj_loader.h>
#include "stb/stb_image.h"


#include "GPUVK_Resources.hpp"



namespace HAL::GPU
{
	namespace Vulkan
	{
		// Usings

		using namespace VT;
		using namespace VT::V4;
		using namespace VT::SPIR_V;

		using namespace LAL ;
		using namespace Meta;



		// Structs

		struct UniformBufferObject
		{
			alignas(16) glm::mat4 ModelSpace;
			alignas(16) glm::mat4 Viewport  ;
			alignas(16) glm::mat4 Projection;
		};

		struct Vertex
		{
			using AttributeDescription = Pipeline::VertexInputState::AttributeDescription;
			using BindingDescription = Pipeline::VertexInputState::BindingDescription;

			using VertexAttributes = StaticArray<AttributeDescription, 3>;


			struct
			{
				float32 X, Y, Z;
			} 
			
			Position;

			struct
			{
				float32 R,G,B;
			}
			
			Color;

			struct 
			{
				float32 X, Y;
			}
			
			TextureCoordinates;


			static constexpr VertexAttributes GetAttributeDescriptions()
			{
				VertexAttributes result{};

				// Position Attributes

				AttributeDescription& posAttrib = result.at(0);

				posAttrib.Binding  = 0;
				posAttrib.Location = 0;
				posAttrib.Format   = EFormat::R32_G32_B32_SFloat;
				posAttrib.Offset   = offsetof(Vertex, Vertex::Position);

				// Color Attributes

				AttributeDescription& colorAttrib = result.at(1);

				colorAttrib.Binding  = 0;
				colorAttrib.Location = 1;
				colorAttrib.Format   = EFormat::R32_G32_B32_SFloat;
				colorAttrib.Offset   = offsetof(Vertex, Vertex::Color);

				// Texture Coordinate Attributes

				AttributeDescription& texCoordAttrib = result.at(2);

				texCoordAttrib.Binding  = 0;
				texCoordAttrib.Location = 2;
				texCoordAttrib.Format   = EFormat::R32_G32_SFloat;
				texCoordAttrib.Offset   = offsetof(Vertex, Vertex::TextureCoordinates);

				return result;
			}

			static constexpr BindingDescription GetBindingDescription()
			{
				BindingDescription result{};

				result.Binding   = 0;
				result.Stride    = sizeof(Vertex);
				result.InputRate = EVertexInputRate::Vertex;

				return result;
			}
		};



		//StaticData
		//(
			multiDefs const DynamicArray<Vertex> TriangleVerticies = 
			{
				{
					{ 0.0f, -0.5f      }, 
					{ 1.0f,  0.0f, 0.0f}
				},
				{
					{ 0.5f, 0.5f      }, 
					{ 0.0f, 1.0f, 0.0f}
				},
				{
					{-0.5f, 0.5f      }, 
					{ 0.0f, 0.0f, 1.0f}
				}
			};

			multiDefs const DynamicArray<Vertex> SquareVerticies =
			{
				{
					{ -0.5f, -0.5f, 0.0f }, 
					{  1.0f,  0.0f, 0.0f }, 
					{  0.0f,  0.0f       }
				},
				{
					{ 0.5f, -0.5f, 0.0f }, 
					{ 0.0f,  1.0f, 0.0f }, 
					{ 1.0f,  0.0f       }
				},
				{
					{ 0.5f, 0.5f, 0.0f }, 
					{ 0.0f, 0.0f, 1.0f }, 
					{ 1.0f, 1.0f       }
				},
				{
					{ -0.5f, 0.5f, 0.0f }, 
					{  1.0f, 1.0f, 1.0f }, 
					{  0.0f, 1.0f       }
				},

				{ 
					{ -0.5f, -0.5f, -0.5f }, 
					{  1.0f,  0.0f,  0.0f }, 
					{  0.0f,  0.0f        }
				},
				{
					{ 0.5f, -0.5f, -0.5f }, 
					{ 0.0f,  1.0f,  0.0f }, 
					{ 1.0f,  0.0f        }
				},
				{
					{ 0.5f, 0.5f, -0.5f }, 
					{ 0.0f, 0.0f,  1.0f }, 
					{ 1.0f, 1.0f        }
				},
				{
					{ -0.5f, 0.5f, -0.5f }, 
					{  1.0f, 1.0f,  1.0f }, 
					{  0.0f, 1.0f        }
				}
			};

			multiDefs const DynamicArray<uInt16> SquareIndices =
			{
				0, 1, 2, 2, 3, 0,
				4, 5, 6, 6, 7, 4
			};

			eGlobal DynamicArray<Vertex> ModelVerticies;
			eGlobal DynamicArray<uint32> ModelIndicies ;

			multiDefs const String VikingRoom_ModelPath   = "Engine/Data/Models/VikingRoom/viking_room.obj";
			multiDefs const String VikingRoom_TexturePath = "Engine/Data/Models/VikingRoom/viking_room.png";

			multiDefs const String EdsCryingCat_ModelPath   = "Engine/Data/Models/EdsCryingCat/EdsCryingCat.obj";
			multiDefs const String EdsCryingCat_TexturePath = "Engine/Data/Models/EdsCryingCat/EdsCryingCat.jpg";

			// TODO: Make the GPU hal agnostic to this.

			eGlobal Buffer VertexBuffer      ;
			eGlobal Memory VertexBufferMemory;

			eGlobal Buffer IndexBuffer      ;
			eGlobal Memory IndexBufferMemory;

			eGlobal DynamicArray<Buffer> UniformBuffers      ;
			eGlobal DynamicArray<Memory> UniformBuffersMemory;

			eGlobal Image     TextureImage      ;
			eGlobal Memory    TextureImageMemory;
			eGlobal ImageView TextureImageView  ;
			eGlobal Sampler   TextureSampler    ;
		//)


			void LoadModel(String _modelPath);
			
	}
}