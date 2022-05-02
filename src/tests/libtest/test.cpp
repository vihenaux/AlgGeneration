#include "test.hpp"

Test::Test(std::string const & testName)
{
	std::cout	<< '\n';
	std::cout	<< std::string(testName.size()+4, '#')	<<   '\n'
		<< '#'	<< std::string(testName.size()+2, ' ')	<<  "#\n"
		<< "# "	<< testName								<< " #\n"
		<< '#'	<< std::string(testName.size()+2, ' ')	<<  "#\n"
				<< std::string(testName.size()+4, '#')	<<   '\n' << std::endl;
}

Test::~Test()
{
	bool testPassed = static_cast<bool>(triedTrue_ == actualTrue_)
					&&static_cast<bool>(triedFalse_ == actualFalse_)
					&&static_cast<bool>(triedEqual_ == actualEqual_)
					&&static_cast<bool>(triedDifferent_ == actualDifferent_);

	std::cout << '\n';
	if(testPassed)
	{
		// PRint success
		std::cout << "\033[32m"	<< std::string(11, '#') << "\n"
								<< "# SUCCESS #\n"
								<< std::string(11, '#') << "\033[0m"
								<< '\n';
	}
	else
	{
		// Test summary fail
		std::cout << "Test summary :\n" << std::endl;

		std::cout	<< "\033[" << 31+static_cast<bool>(triedTrue_ == actualTrue_)
					<< "mExpected True : " << actualTrue_ << "/" << triedTrue_ << "\n"
					<< "\033[" << 31+static_cast<bool>(triedFalse_ == actualFalse_)
					<< "mExpected False : " << actualFalse_ << "/" << triedFalse_ << "\n"
					<< "\033[" << 31+static_cast<bool>(triedEqual_ == actualEqual_)
					<< "mExpected Equal : " << actualEqual_ << "/" << triedEqual_ << "\n"
					<< "\033[" << 31+static_cast<bool>(triedDifferent_ == actualDifferent_)
					<< "mExpected Different : " << actualDifferent_ << "/" << triedDifferent_  << "\033[0m\n" << std::endl;

		// List of the failed tests
		std::cout << "Tests failed :";
		for(auto& f : testsFailed_)
		{
			std::cout << " " << f;
		}
		std::cout << std::endl;

		// Print failed
		std::cout << "\n\033[31m"	<< std::string(10, '#') << "\n"
									<< "# FAILED #\n"
									<< std::string(10, '#') << "\033[0m"
									<< '\n';
	}
	std::cout << std::endl;
}

void Test::expectTrue(bool test, std::string const & name)
{
	++triedTrue_;
	actualTrue_ += static_cast<bool>(test);

	if(test)
	{
		if(!name.empty())
		{
			std::cout << "\033[32m" << name << " Passed (was True)\033[0m ";
		}
	}
	else
	{
		if(!name.empty())
		{
			std::cout << "\033[31m" << name << " Failed (was False)\033[0m ";
			testsFailed_.push_back(name);
		}
		else
		{
			testsFailed_.push_back("noname");
		}
	}

	std::cout << actualTrue_ << "/" << triedTrue_ << std::endl;
}

void Test::expectFalse(bool test, std::string const & name)
{
	++triedFalse_;
	actualFalse_ += static_cast<bool>(!test);

	if(!test)
	{
		if(!name.empty())
		{
			std::cout << "\033[32m" << name << " Passed (was False)\033[0m ";
		}
	}
	else
	{
		if(!name.empty())
		{
			std::cout << "\033[31m" << name << " Failed (was True)\033[0m ";
			testsFailed_.push_back(name);
		}
		else
		{
			testsFailed_.push_back("noname");
		}
	}

	std::cout << actualFalse_ << "/" << triedFalse_ << std::endl;
}
