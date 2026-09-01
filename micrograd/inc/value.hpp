#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <cmath>

class Value : public std::enable_shared_from_this<Value> {
	public:
		double								_data;
		double								_grad{};
		std::function<void()>				_backward = []() {};
		std::vector<std::shared_ptr<Value>>	_prev;
		std::string							_op;
		std::string							_label;

		Value(double data, std::string label = "", std::vector<std::shared_ptr<Value>> children = {}, std::string op = "");

		static std::shared_ptr<Value>	create(double data, std::string label);
		std::shared_ptr<Value>			tanh();
};

using	ValuePtr = std::shared_ptr<Value>;

Value::Value(double data, std::string label, std::vector<std::shared_ptr<Value>> children, std::string op)
	: _data(data), _prev(std::move(children)), _op(std::move(op)), _label(std::move(label)) {}

ValuePtr	Value::create(double data, std::string label) {
	return std::make_shared<Value>(data, label);
}

ValuePtr	operator+(const ValuePtr&a, const ValuePtr &b) {
	auto	out = std::make_shared<Value>(a->_data + b->_data, "", std::vector<ValuePtr>{a, b}, "+");

	out->_backward = [a, b, out]() {
		a->_grad += out->_grad;
		b->_grad += out->_grad;
	};

	return out;
}

ValuePtr	operator*(const ValuePtr &a, const ValuePtr &b) {
	auto	out = std::make_shared<Value>(a->_data * b->_data, "", std::vector<ValuePtr>{a, b}, "*");

	out->_backward = [a, b, out]() {
		a->_grad = b->_data * out->_grad;
		b->_grad = a->_data * out->_grad;
	};

	return out;
}

std::shared_ptr<Value>	Value::tanh() {
	double	x = this->_data;
	double	t = (std::exp(2.0 * x) - 1.0) / (std::exp(2.0 * x) + 1);
	auto	out = std::make_shared<Value>(t, "tanh", std::vector<ValuePtr>{shared_from_this()});

	out->_backward = [this, t, out]() {
		this->_grad = (1.0 - std::pow(t, 2)) * out->_grad;
	};

	return out;
}
