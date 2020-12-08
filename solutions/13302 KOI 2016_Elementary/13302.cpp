#include <stdio.h>
#define MAX_VACATION_DATES 100
#define ONEDAY_PASS 10000
#define THREEDAY_PASS 25000
#define FIVEDAY_PASS 37000
#define MAX_COUPON 18

bool vacation[MAX_VACATION_DATES] = { 0, };
int vacationDates;
int numOfDatesCanNotGo;

void getProperties();
int getMinExpense(int date = 0, int expense = 0, int coupon = 0);
int min(int a, int b);

int main() {
	getProperties();
	printf("%d", getMinExpense());

	return 0;
}

void getProperties() {
	scanf_s("%d %d", &vacationDates, &numOfDatesCanNotGo);

	for (int i = 0; i < vacationDates; i++)
		vacation[i] = true;

	for (int i = 0; i < numOfDatesCanNotGo; i++) {
		int temp;
		scanf_s("%d", &temp);
		vacation[temp - 1] = false;
	}
}
//printf("%d %d %d\n", date, expense, coupon);
/*
10 3
2 5 6
*/

//자명한 사실 
//1. 쿠폰을 사용할 수 있는 일수가 남은 일수랑 같거나 작으면 쿠폰을 사용하는 것이 가장 최소비용이다.
//2. 쿠폰이 18개 이상 있으면 한장 써버리는 게 최소비용
//3. 
int getMinExpense(int date, int expense, int coupon) {
	static int smallestExpenseByDate[MAX_VACATION_DATES+1][2];
	
	if (date >= vacationDates)
		return expense;


	while (!vacation[date]) {
		date++;
		if (date >= vacationDates)
			return expense;
	}

	if (coupon <= smallestExpenseByDate[date][0] && smallestExpenseByDate[date][1] != 0)
		return smallestExpenseByDate[date][1] + expense;
	else
		smallestExpenseByDate[date][0] = coupon;

	
	int couponDay = 1000000;/*
	if (vacationDates - date <= coupon / 3) {
		smallestExpenseByDate[date][coupon] = 0;
		return expense;
	}
	else if (coupon >= 18) {
		couponDay = getMinExpense(date + 1, expense, coupon - 3);
		smallestExpenseByDate[date][1] = couponDay - expense;
		return couponDay;
	}
	else */if (coupon >= 3)
		couponDay = getMinExpense(date + 1, expense, coupon - 3);
	


	int minExpense = min(min(getMinExpense(date + 5, expense + FIVEDAY_PASS, coupon + 2), getMinExpense(date + 3, expense + THREEDAY_PASS, coupon + 1)),
						min(getMinExpense(date + 1, expense + ONEDAY_PASS, coupon), couponDay));
	
	smallestExpenseByDate[date][1] = minExpense - expense;

	return minExpense;
}

int min(int a, int b) {
	return a < b ? a : b;
}