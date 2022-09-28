#pragma once
#include "empch.h"
#include "Types.h"
#include "Serialization/JSONSerialization.h"
#include "ExoEngine/Math/Vmath.h"
namespace EM
{
	//RigidBody Component
	class RigidBody : public JSONSerializer
	{
	public:
		RigidBody();
		~RigidBody() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;

		vec2D GetMin() { return min; }
		vec2D GetMax() { return max; }

		void SetMin(vec2D Min) { min = Min; }
		void SetMax(vec2D Max) { max = Max; }

	private:
		vec2D	min;
		vec2D	max;
	};

	//Transform Component
	class Transform : public JSONSerializer
	{
	public:
		Transform();
		~Transform() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;

		vec2D& GetPos() { return position; }
		vec2D GetScale() { return scale; }

		void SetPos(vec2D Pos) { position = Pos; }
		void SetScale(vec2D Scale) { scale = Scale; }


	private:
		vec2D position;
		vec2D scale;
	};

	//Window Component
	class WinData : public JSONSerializer
	{
	public:
		WinData();
		~WinData() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;

		std::string GetTitle() { return title; }
		unsigned int GetWidth() { return width; }
		unsigned int GetHeight() { return height; }
		unsigned int GetCurrWidth() { return currentWidth; }
		unsigned int GetCurrHeight() { return currentHeight; }

		void SetTitle(std::string Title) { title = Title; }
		void SetWidth(unsigned int Width) { width = Width; }
		void SetHeight(unsigned int Height) { height = Height; }
		void SetCurrWidth(unsigned int CurrWidth) { currentWidth = CurrWidth; }
		void SetCurrHeight(unsigned int CurrHeight) { currentHeight = CurrHeight; }


	private:
		std::string title;
		unsigned int width,
			height,
			currentWidth,
			currentHeight;
	};

}