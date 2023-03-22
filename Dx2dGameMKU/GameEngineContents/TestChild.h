#pragma once


class TestChild 
{
public:
	TestChild();
	~TestChild();

	TestChild(const TestChild& _Other) = delete;
	TestChild(TestChild&& _Other) noexcept = delete;
	TestChild& operator=(const TestChild& _Other) = delete;
	TestChild& operator=(const TestChild&& _Other) noexcept = delete;

protected:

private:

};

