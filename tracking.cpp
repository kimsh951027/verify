//��ķ���� ���� ������ ������ �����ϰ�, db�� �Է¿ϼ�, ���ǿ� �´� �ʵ尪 ����ϰ� ����ð����

#include "GetTimeT.h" // �ð� �����ͼ� ����ð��� ���ϰ� �ð��� �󸶳� �������� ���, ������ �̵��Ÿ� ���
#include "GetDistance.h"////������ coordinates ������ �Ÿ� ���ϱ�
#include "db.h" //db�� �����ֱ�
#include "dbinsert.h"
#include "select.h"


int main(int, char**)
{
	int index = 0;
	char buf[256];
	char buff[256];
	int a = 1;  //1��ī�޶�
	int a2 = 2; //2��ī�޶�
	char *b; //��¥ �ð�
	char c[256] = "'web_cam1'";
	char c2[256] = "'web_cam2'";

	tagPT first_loc; // ó�� ������ �߰ߵ� ��ġA
	tagPT cam1_loc;
	tagPT cam2_loc;
	//��ġA
	first_loc.y = 36.364808;
	first_loc.x = 127.379525;
	//ī�޶�1�� ��ġ
	cam1_loc.y = 36.364772;
	cam1_loc.x = 127.390275;
	//ī�޶�2�� ��ġ
	cam2_loc.y = 36.363972;
	cam2_loc.x = 127.410275;

	double Dis1 = GetDistance(first_loc, cam1_loc);
	double Dis2 = GetDistance(first_loc, cam2_loc);
	Mat frameMat;
	Mat frameMat2;

	VideoCapture videoCapture(0);
	VideoCapture videoCapture2(1);
	if (!videoCapture.isOpened())
	{
		printf("ù��° ī�޶� ���� �����ϴ�. \n");
	}
	if (!videoCapture2.isOpened())
	{
		printf("�ι�° ī�޶� ���� �����ϴ�. \n");
	}

	namedWindow("ī�޶�1", WINDOW_AUTOSIZE);
	namedWindow("ī�޶�2", WINDOW_AUTOSIZE);


	while (1)
	{
		//�ð��޾ƿ���
		struct tm *t;
		time_t timer;

		timer = time(NULL);    // ���� �ð��� �� ������ ���
		t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�
		b = timeToString(t);

		//��ĸ���κ��� �� �������� �о��  
		videoCapture.read(frameMat);
		videoCapture2.read(frameMat2);

		//ȭ�鿡 ������
		imshow("ī�޶�1", frameMat);
		imshow("ī�޶�2", frameMat2);

		//�̹����� ����  
		sprintf(buf, "Z:/HDD1/Data/img_%06d.jpg", index);
		sprintf(buff, "Z:/HDD1/Media/img_%06d.jpg", index);
		cout << buf << endl;

		imwrite(buf, frameMat);
		imwrite(buff, frameMat2);

		db(a, b, c, Dis1, buf);          //insert �Լ�
		db(a2, b, c2, Dis2, buff);

		index++;

		if (index == 999999) index = 0;

		if (waitKey(25) == 27) break; //ESCŰ ������ ����  
	}
	select(1, 4);

	/* ����ð� ��� �ʿ� X
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // ���� �ð��� �� ������ ���
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�
	b = timeToString(t);

	printf("����ð��� : ");
	printf(b);
	printf("\n");
	*/
	return 0;
}
