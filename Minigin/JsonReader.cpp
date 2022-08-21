#include "MiniginPCH.h"
#include "JsonReader.h"
#include <fstream>

#include "BoxCollider.h"
#include "GameObject.h"
#include "document.h"
#include <istreamwrapper.h>


void JsonReader::ReadFile(dae::Scene& scene,const std::string& path) const
{
	if (std::ifstream is{"../Data/" + path})
	{
		rapidjson::IStreamWrapper isw{ is };

		rapidjson::Document jsonDoc;
		jsonDoc.ParseStream(isw);

		const rapidjson::Value& valName = jsonDoc["Colliders"];
		for (const auto& p : valName.GetArray())
		{
			const auto tag = p["Object"].GetString();
			const auto dimensions = p["Dimensions"].GetArray();
			int arr[4]{};
			for (int i = 0; i < static_cast<int>(dimensions.Size()); ++i)
			{
				arr[i] = dimensions[i].GetInt();
			}
			SDL_Rect col{ arr[0] ,arr[1] ,arr[2] ,arr[3] };

			const auto fillcolor{ p["FillColor"].GetObj() };
			const SDL_Color color{ static_cast<Uint8>(fillcolor["r"].GetInt()),static_cast<Uint8>(fillcolor["g"].GetInt()),static_cast<Uint8>(fillcolor["b"].GetInt()) };
			
			const auto obj = std::make_shared<dae::GameObject>(tag);
			obj->AddComponent(new BoxCollider(obj.get(), col, color,true));
			scene.Add(obj);
		}
	}
}
