#pragma once

namespace BHive
{	
	#define ColorToImCol32(color) IM_COL32(color.r, color.g, color.b, color.a)
	#define LColorToImCol32(color) IM_COL32((uint8)(color.r * 255.0f), (uint8)(color.g * 255.0f), \
		(uint8)(color.b * 255.0f), (uint8)(color.a * 255.0f))

	class Color
	{
		#define MAX_COLOR 255

	public:
		Color();
		Color(uint8 color, uint8 A = MAX_COLOR);
		Color(uint8 R, uint8 G, uint8 B, uint8 A = MAX_COLOR);
		void Clamp();

		BString ToString() const;

	public:
		Color operator=(const Color& other) const;
		bool operator==(const Color& col);
		void operator+=(const Color& col);
		const uint8* operator*() const;
		uint8* operator*();
		operator ImVec4() const
		{
			return ImVec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a /255.0f);
		}

	public:
		uint8 r;
		uint8 g;
		uint8 b;
		uint8 a;
	};

	inline std::ostream& operator<<(std::ostream& os, const Color& color)
	{
		return os << color.ToString();
	}

	class LinearColor3
	{
#define MAX_LINEARCOLOR 1.0f

	public:
		LinearColor3();
		LinearColor3(float color);
		LinearColor3(float R, float G, float B);

		void Clamp();
		BString ToString() const;

	public:
		LinearColor3 operator=(const LinearColor3& other);
		bool operator==(const LinearColor3& col);
		void operator+=(const LinearColor3& col);
		const float* operator*() const;
		float* operator*();
		operator FVector3 () const;
	public:
		float r;
		float g;
		float b;
	};

	inline std::ostream& operator<<(std::ostream& os, const LinearColor3& color)
	{
		return os << color.ToString();
	}


	class LinearColor4
	{
		#define MAX_LINEARCOLOR 1.0f

	public:
		LinearColor4();
		LinearColor4(float color, float A = MAX_LINEARCOLOR);
		LinearColor4(float R, float G, float B, float A = MAX_LINEARCOLOR);

		void Clamp();
		BString ToString() const;

	public:
		LinearColor4 operator=(const LinearColor4& other);
		bool operator==(const LinearColor4& col);
		void operator+=(const LinearColor4& col);
		const float* operator*() const;
		float* operator*();
		operator FVector4 () const;
	public:
		float r;	
		float g;
		float b;
		float a;
	};

	inline std::ostream& operator<<(std::ostream& os, const LinearColor4& color)
	{
		return os << color.ToString();
	}
}
