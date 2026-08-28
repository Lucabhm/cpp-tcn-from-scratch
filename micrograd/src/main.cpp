#include "value.hpp"

void	print_graph(ValuePtr input);

int	main() {
	ValuePtr	a = Value::create(2.0, "a");
	ValuePtr	b = Value::create(-3.0, "b");
	ValuePtr	c = Value::create(10.0, "c");
	ValuePtr	d = a * b + c;
	ValuePtr	e = d + a;

	d->_label = "d";
	e->_label = "e";

	print_graph(e);

	return 0;
}

void	print_graph(ValuePtr input) {
	if (input->_prev.empty())
		return;

	std::cout << "label = " << input->_label << std::endl;
	std::cout << "data = " << input->_data << std::endl;
	for (int i{0}; i < input->_prev.size(); ++i) {
		std::cout << "Expresion created by " << input->_prev.at(i)->_label << std::endl;
	}
	std::cout << "with operator " << input->_op << std::endl;

	print_graph(input->_prev.at(0));
}
