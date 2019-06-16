//웹캠으로 찍은 사진을 서버에 저장하고, db값 입력완성, 조건에 맞는 필드값 출력하고 현재시간출력

#include "GetTimeT.h" // 시간 가져와서 현재시간과 비교하고 시간이 얼마나 지났는지 출력, 차량의 이동거리 출력
#include "GetDistance.h"////경위도 coordinates 값으로 거리 구하기
#include "db.h" //db에 쿼리넣기
#include "dbinsert.h"
#include "select.h"


int main(int, char**)
{
	int index = 0;
	char buf[256];
	char buff[256];
	int a = 1;  //1번카메라
	int a2 = 2; //2번카메라
	char *b; //날짜 시간
	char c[256] = "'web_cam1'";
	char c2[256] = "'web_cam2'";

	tagPT first_loc; // 처음 차량이 발견된 위치A
	tagPT cam1_loc;
	tagPT cam2_loc;
	//위치A
	first_loc.y = 36.364808;
	first_loc.x = 127.379525;
	//카메라1의 위치
	cam1_loc.y = 36.364772;
	cam1_loc.x = 127.390275;
	//카메라2의 위치
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
		printf("첫번째 카메라를 열수 없습니다. \n");
	}
	if (!videoCapture2.isOpened())
	{
		printf("두번째 카메라를 열수 없습니다. \n");
	}

	namedWindow("카메라1", WINDOW_AUTOSIZE);
	namedWindow("카메라2", WINDOW_AUTOSIZE);


	while (1)
	{
		//시간받아오기
		struct tm *t;
		time_t timer;

		timer = time(NULL);    // 현재 시각을 초 단위로 얻기
		t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기
		b = timeToString(t);

		//웹캡으로부터 한 프레임을 읽어옴  
		videoCapture.read(frameMat);
		videoCapture2.read(frameMat2);

		//화면에 보여줌
		imshow("카메라1", frameMat);
		imshow("카메라2", frameMat2);

		//이미지로 저장  
		sprintf(buf, "Z:/HDD1/Data/img_%06d.jpg", index);
		sprintf(buff, "Z:/HDD1/Media/img_%06d.jpg", index);
		cout << buf << endl;

		imwrite(buf, frameMat);
		imwrite(buff, frameMat2);

		db(a, b, c, Dis1, buf);          //insert 함수
		db(a2, b, c2, Dis2, buff);

		index++;

		if (index == 999999) index = 0;

		if (waitKey(25) == 27) break; //ESC키 누르면 종료  
	}
	select(1, 4);

	/* 현재시간 출력 필요 X
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // 현재 시각을 초 단위로 얻기
	t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기
	b = timeToString(t);

	printf("현재시간은 : ");
	printf(b);
	printf("\n");
	*/
	return 0;
}
