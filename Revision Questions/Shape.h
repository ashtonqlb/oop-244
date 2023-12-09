#ifndef SDDS_SHAPE_H
#define SDDS_SHAPE_H

namespace sdds  {
	class Shape {
	public:
		virtual double area() const = 0;
		virtual double perimeter() const = 0;

		Shape (const Shape& other) = delete;
		Shape& operator=(const Shape& other) = delete;
		bool operator==(const Shape& other) const = delete;

		Shape() = default;
		virtual ~Shape() = default;

	};

	class Circle : public Shape {
	double m_radius;
	public:
		Circle(double r) : m_radius(r) {};

		double area() const override;
		double perimeter() const override;
	};

	class Rectangle : public Shape {
		double m_length;
		double m_width;
	public:
		Rectangle(double l, double w) : m_length(l), m_width(w) {};

		double area() const override;
		double perimeter() const override;
	};
}

#endif
