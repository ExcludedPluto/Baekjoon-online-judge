#include <stdio.h>

int numOfTile;

long long getCircumference(long long ex, long long now, int tile);


int main() {
	scanf_s("%d", &numOfTile);

	printf("%lld", getCircumference(0, 1, 1));

	return 0;
}

long long getCircumference(long long ex, long long now, int tile) {
	if (tile == numOfTile) {
		if (ex == 0)
			return 4;
		return ((now * 2) + ((ex+now) * 2));
	}
	else {
		return getCircumference(now, ex + now, tile + 1);
	}
}