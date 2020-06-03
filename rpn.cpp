#include <iostream>
#include <cctype>
#include <string>

template<class T>
class Stack
{
	T val[50];
	int size = 0;
public:
	void push(T a)
	{
		val[size++] = a;
	}
	T pop()
	{
		if (size == 0)
			return 'N';
		return val[--size];
	}
	T top()
	{
		return val[size - 1];
	}
	void display()
	{
		std::cout << "Stos:[";
		for (int i = 0; i < size; i++)
			std::cout << val[i] << " ";
		std::cout << "]" << std::endl;
	}
};



int getPriority(char c)
{
	switch (c)
	{
	case '+':
	case '-':
		return 1;
		break;
	case '*':
	case '/':
		return 2;
		break;
	default:
		return 0;
	}
}

std::string ToRPN(std::string input)
{
	std::string output = "";
	Stack<char> st;

	for (int i = 0; i < input.size(); i++)
	{
		//		st.display();
		char c = input[i];
		if (std::isdigit(c))
		{
			output += c;
			continue;
		}
		if (i > 0 && std::isdigit(input[i - 1]))
			output += ' ';

		if (getPriority(c))
		{
			while (getPriority(st.top()) && getPriority(c) <= getPriority(st.top()))
			{
				output += st.pop();
				//output += ' ';
			}
			st.push(c);
		}
		else if (c == '(')
			st.push(c);
		else if (c == ')')
		{
			for (char a = st.pop(); a != '('; a = st.pop())
			{
				output += a;
				//output += ' ';
			}
		}
	}
	output += ' ';
	for (char a = st.pop(); a != 'N'; a = st.pop())
	{
		output += a;
		//	output += ' ';
	}

	return output;
}

int calculateRPN(std::string input)
{
	Stack<int> st;
	int value = 0;
	for (int i = 0; i < input.size(); i++)
	{
		st.display();
		char c = input[i];
		if (std::isdigit(c))
		{
			value *= 10;
			value += c - '0';
		}
		else if (c == ' ')
		{
			st.push(value);
			value = 0;
		}
		else
		{
			if (getPriority(c))
			{
				int x = st.pop();
				int y = st.pop();
				int z = 0;
				switch (c)
				{
				case '+':
					z = y + x;
					break;
				case '-':
					z = y - x;
					break;
				case '*':
					z = y * x;
					break;
				case '/':
					z = y / x;
					break;
				default:
					z = 0;
					break;
				}
				st.push(z);
			}
		}
	}
	return st.pop();
}

int main3 ()
{
	//	std::string in = "(4+6)*(8-3)/2";
	std::string in = "3+4*(2-1)";
	std::cout << "Input: " << in << std::endl;
	std::cout << "Output: " << ToRPN(in);
	std::cout << calculateRPN(ToRPN(in));
	return 0;
}