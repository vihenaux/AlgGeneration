#pragma once

#include <iostream>
#include <string>
#include <cstdint>
#include <vector>

class Test
{
	public:

	Test(std::string const & testName);
	~Test();

	void expectTrue(bool test, std::string const & name = "");
	void expectFalse(bool test, std::string const & name = "");

	template<class T>
	void expectEqual(T a, T b, std::string const & name = "")
	{
		++triedEqual_;
		actualEqual_ += static_cast<bool>(a == b);

		if(a == b)
		{
			if(!name.empty())
			{
				std::cout << "\033[32m" << name << " Passed (" << a << " == " << b << ")\033[0m ";
			}
		}
		else
		{
			if(!name.empty())
			{
				std::cout << "\033[31m" << name << " Failed (" << a << " != " << b << ")\033[0m ";
				testsFailed_.push_back(name);
			}
			else
			{
				testsFailed_.push_back("noname");
			}
		}

		std::cout << actualEqual_ << "/" << triedEqual_ << std::endl;
	}
	template<class T>
	void expectDifferent(T a, T b, std::string const & name = "")
	{
		++triedDifferent_;
		actualDifferent_ += static_cast<bool>(a != b);

		if(a != b)
		{
			if(!name.empty())
			{
				std::cout << "\033[32m" << name << " Passed (" << a << " != " << b << ")\033[0m ";
			}
		}
		else
		{
			if(!name.empty())
			{
				std::cout << "\033[31m" << name << " Failed (" << a << " == " << b << ")\033[0m ";
				testsFailed_.push_back(name);
			}
			else
			{
				testsFailed_.push_back("noname");
			}
		}

		std::cout << triedDifferent_ << "/" << actualDifferent_ << std::endl;
	}

	private:

	std::uint32_t triedTrue_{0};
	std::uint32_t actualTrue_{0};

	std::uint32_t triedFalse_{0};
	std::uint32_t actualFalse_{0};

	std::uint32_t triedEqual_{0};
	std::uint32_t actualEqual_{0};

	std::uint32_t triedDifferent_{0};
	std::uint32_t actualDifferent_{0};

	std::vector<std::string> testsFailed_{};
};
