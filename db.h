
#define _CRT_SECURE_NO_WARNINGS
#include <mysql.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "tjsgud9248"
#define DB_NAME "devices"
#define SQL_INSERT_RECORD "INSERT INTO cam_info VALUES \ (%d, '%s' , %s, '%lf', '%s' );" 
#define SQL_SELECT_RECORD "SELECT cam_id,time FROM cam_info WHERE cam_dis <= %d AND pic_link = 'Z:/HDD1/Data/img_00000%d.jpg';"
using namespace cv;
using namespace std;
