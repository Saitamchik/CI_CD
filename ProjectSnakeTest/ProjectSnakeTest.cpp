#include "pch.h"
#include "CppUnitTest.h"
#include "../ProjectSnake/game.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjectSnakeTest
{
	TEST_CLASS(TestFruct)
	{
	public:
		TEST_METHOD(TestPositionSelectWithParam)
		{
			Fruct fruct;
			fruct.positionSelect(1, 1);
			Assert::AreEqual(fruct.getX(), 1);
			Assert::AreEqual(fruct.getY(), 1);
		}
		TEST_METHOD(TestPositionSelectNonParam)
		{
			Fruct fruct;
			fruct.positionSelect();
			Assert::IsTrue(fruct.getX() > 0 && fruct.getX() <= 30);
			Assert::IsTrue(fruct.getY() > 0 && fruct.getY() <= 200);
		}
	};

	TEST_CLASS(TestSnake)
	{
	public:
		TEST_METHOD(TestCreate)
		{
			Snake snake;
			Assert::AreEqual(snake.getDirection(), 2);
			Assert::AreEqual(snake.getSize(), 4);
		}
		TEST_METHOD(TestMove)
		{
			SnakeFirst snake;

			int x = snake.getX(0);
			int y = snake.getY(0);

			snake.move();

			Assert::AreEqual(snake.getX(0), x + 1);
			Assert::AreEqual(snake.getY(0), y);
		}
		TEST_METHOD(TestCollisionSnake)
		{
			SnakeFirst snakeFirst;
			SnakeSecond snakeSecond;

			snakeFirst.setX(0, 1);
			snakeFirst.setY(0, 20);

			Assert::IsTrue(snakeFirst.collision(snakeSecond));
			Assert::IsTrue(snakeSecond.collision(snakeFirst));
		}
		TEST_METHOD(TestOversteppingBoundaries)
		{
			SnakeFirst snake;

			snake.setX(0, 30);
			snake.oversteppingBoundaries();

			Assert::IsTrue(snake.getX(0) == 0);
		}
		TEST_METHOD(testeatFruct)
		{
			SnakeFirst snake;
			Fruct fruct;

			fruct.positionSelect(15, 10);
			snake.setX(0, 15);
			snake.setY(0, 10);
			snake.eatFruct(fruct);
			Assert::AreEqual(snake.getSize(), 5);
			Assert::IsFalse(fruct.getX() == 15);
			Assert::IsFalse(fruct.getY() == 10);
		}
	};
}
