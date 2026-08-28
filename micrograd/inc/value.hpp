#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Value {
	public:
		double								_data;
		std::vector<std::shared_ptr<Value>>	_prev;
		std::string							_op;
		std::string							_label;

		Value(double data, std::string label = "", std::vector<std::shared_ptr<Value>> children = {}, std::string op = "");

		static std::shared_ptr<Value>	create(double data, std::string label);
};

using	ValuePtr = std::shared_ptr<Value>;

Value::Value(double data, std::string label, std::vector<std::shared_ptr<Value>> children, std::string op)
	: _data(data), _prev(std::move(children)), _op(std::move(op)), _label(std::move(label)) {}

ValuePtr	Value::create(double data, std::string label) {
	return std::make_shared<Value>(data, label);
}

ValuePtr	operator+(const ValuePtr&a, const ValuePtr &b) {
	auto	out = std::make_shared<Value>(a->_data + b->_data, "", std::vector<ValuePtr>{a, b}, "+");

	return out;
}

ValuePtr	operator*(const ValuePtr &a, const ValuePtr &b) {
	auto	out = std::make_shared<Value>(a->_data * b->_data, "", std::vector<ValuePtr>{a, b}, "*");

	return out;
}