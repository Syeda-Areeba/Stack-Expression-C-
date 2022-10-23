#include "pch.h"
#include "../Assignment 2/Stack.h"

TEST(TestCaseEvaluateExp, T1) {
	string exp = "18-[6-{4-(8-6+3)}]";
	EXPECT_EQ("11", evaluate(exp));
}
TEST(TestCaseEvaluateExp, T2) {
	string exp = "18-[6-{4-(8-6+3})]";
	EXPECT_EQ("Invalid Expression", evaluate(exp));
}
TEST(TestCaseEvaluateExp, T3) {
	string exp = "18-[6-}{4-(8-6+3)]";
	EXPECT_EQ("Invalid Expression", evaluate(exp));
}
TEST(TestCaseEvaluateExp, T4) {
	string exp = "(3+4)*5+6-2";
	EXPECT_EQ("63", evaluate(exp));
}
TEST(TestCaseEvaluateExp, T5) {
	string exp = "(3+4)5+6-2";
	EXPECT_EQ("Invalid Expression", evaluate(exp));
}
TEST(TestCaseEvaluateExp, T6) {
	string exp = ")3+45+6-2";
	EXPECT_EQ("Invalid Expression", evaluate(exp));
}

TEST(TestCaseEvaluateExp, T7) {
	string exp = "2+1(3*2)";
	EXPECT_EQ("Invalid Expression", evaluate(exp));
}

TEST(TestCaseEvaluateExp, T8) {
	string exp = "8%0";
	EXPECT_EQ("Invalid Expression", evaluate(exp));
}
TEST(TestCaseEvaluateExp, T9) {
	string exp = "8/0";
	EXPECT_EQ("Invalid Expression", evaluate(exp));
}

TEST(TestCaseEvaluateExp, T10)
{
	string exp[21] = { "(7)+", "()", "+(0)", "(+9)", "(9+)", "[()]", "&", "87 = 87", "(5 + 6)(7 - 6)", ")(", ")9^5(",
		"1(2)", "[-]", "9-0w", "*2", "3*", "4-1*{r}", "%", "(7*/8)", "++9", "-7" };

	for (int i = 0; i < 21; i++)
	{
		EXPECT_EQ("Invalid Expression", evaluate(exp[i]));
	}
}

TEST(TestCaseEvaluateExp, T11)
{
	string exp = "(1+2)*3*(4+5)";
	EXPECT_EQ("81", evaluate(exp));
}

TEST(TestCaseEvaluateExp, T12)
{
	string exp = "(23-14/[9-{5+9}]*87%7)";
	EXPECT_EQ("-3", evaluate(exp));
}

TEST(TestCaseEvaluateExp, T13)
{
	string exp = "{4-5%[7-8]-{5}^9*(21-34)+500}-[[4/(5)]]";
	EXPECT_EQ("-1", evaluate(exp));
}

TEST(TestCaseEvaluateExp, T14)
{
	string exp = "78-9-99-92-12-{22/[(1^4)^2]*22}+23";
	EXPECT_EQ("-595", evaluate(exp));
}

TEST(TestCaseEvaluateExp, T15)
{
	string exp = "{{[(5^2)+2]-9%100}+{[(27+2)+1]}}";
	EXPECT_EQ("48", evaluate(exp));
}

TEST(TestCaseEvaluateExp, T16)
{
	string exp = "(11%22+33*([44^0]-{55}))";
	EXPECT_EQ("-2376", evaluate(exp));
}

TEST(TestCaseEvaluateExp, T17)
{
	string exp = "[{2+3+((4*1)/3^2)}+{[1+3/4*(5-9)%31]}]";
	EXPECT_EQ("2", evaluate(exp));
}

TEST(TestCaseEvaluateExp, T18)
{
	string exp[5] = { "(8)", "{{[[((9))]]}}", "78", "0-9", "0" };
	string ans[5] = { "8","9","78","-9","0" };
	for (int i = 0; i < 5; i++)
	{
		EXPECT_EQ(ans[i], evaluate(exp[i]));
	}
}