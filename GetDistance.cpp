//������ coordinates ������ �Ÿ� ���ϱ�

#define rad(x) x*3.14159/180.0
#include <math.h>
#include "GetDistance.h"

double GetDistance(tagPT cd1, tagPT cd2)
{
	int radius = 6371; //������� ������ km

	double dLat = rad((cd2.y - cd1.y));
	double dLon = rad((cd2.x - cd1.x));

	cd1.y = rad(cd1.y);
	cd2.y = rad(cd2.y);

	double a = sin(dLat / 2) * sin(dLat / 2) + sin(dLon / 2) * sin(dLon / 2) * cos(cd1.y) * cos(cd2.y);
	double c = 2 * atan2f(sqrtf(a), sqrtf(1 - a));
	double dDistance = radius * c;

	//dDistance *= 1000;  //�ּ�ó���ϸ� km��, �ƴϸ� m��

	return dDistance;
}
