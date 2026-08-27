#pragma once

#include <iostream>

class Value {
	private:
		double	data;
	public:
		Value(double data);
		void	print_value();
};

Value::Value(double data) {
	this->data = data;
}

void	Value::print_value() {
	std::cout << this->data << std::endl;
}