#include "value.hpp"

void	print_graph(std::shared_ptr<Value> &input);

int	main() {
	ValuePtr	x1 = Value::create(2.0, "x1");
	ValuePtr	x2 = Value::create(0.0, "x1");
	ValuePtr	w1 = Value::create(-3.0, "w1");
	ValuePtr	w2 = Value::create(1.0, "w2");
	ValuePtr	b = Value::create(6.88, "b");
	ValuePtr	x1w1 = x1 * w1; x1w1->_label = "x1w1";
	ValuePtr	x2w2 = x2 * w2; x2w2->_label = "x2w2";
	ValuePtr	x1w1x2w2 = x1w1 + x2w2; x1w1x2w2->_label = "x1w1x2w2";
	ValuePtr	n = x1w1x2w2 + b; n->_label = "n";
	ValuePtr	o = n->tanh(); o->_label = "o";

	o->_grad = 1.0;
	o->_backward();
	n->_backward();
	print_graph(o);
}

void	print_graph(std::shared_ptr<Value> &input) {
	if (input->_prev.empty())
		return;

	std::cout << "label = " << input->_label << std::endl;
	std::cout << "data = " << input->_data << std::endl;
	std::cout << "grad = " << input->_grad << std::endl;
	for (int i{0}; i < input->_prev.size(); ++i) {
		std::cout << "Expresion created by " << input->_prev.at(i)->_label << std::endl;
	}
	std::cout << "with operator " << input->_op << std::endl;

	print_graph(input->_prev.at(0));
}
