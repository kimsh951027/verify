//db�� ���� select ������
#include "select.h"
#include "db.h"
#include "GetTimeT.h"

int select(int a, int b)
{
	int query_stat;
	char query[255];

	MYSQL *connection = NULL, conn;
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);
	if (connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return 1;
	}
	sprintf(query, SQL_SELECT_RECORD, a, b);
	cout << query << endl;
	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		cout << "����" << endl;
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}
	if (mysql_query(&conn, SQL_SELECT_RECORD))
	{
		mysql_error(&conn);
	}
	MYSQL_RES *sql_result = mysql_store_result(&conn);
	int num_fields = mysql_num_fields(sql_result);

	MYSQL_ROW row;

	while ((row = mysql_fetch_row(sql_result)))
	{
		for (int i = 0; i < num_fields; i++) //num_fields �� ����ϰ��� �ϴ� �ʵ尳��
		{
			printf("%s   ", row[i] ? row[i] : "NULL");
		}
		printf("\n");

		//printf("%s\n", row[1]);//�ð����� ���

		break;  //while�� �ѹ������� �ϳ��� ����Ϸ��� break��
	}

	if (query_stat != 0)
	{
		cout << "����" << endl;
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}
	//

	char *sArr[10] = { NULL, };
	char *date[10] = { NULL, };
	char *time[10] = { NULL, };
	int s = 0, d = 0, f = 0;
	//" "������� ������
	char *ptr = strtok(row[1], " ");
	while (ptr != NULL) {
		sArr[s] = ptr;
		s++;
		ptr = strtok(NULL, " ");
	}
	/*
	for (int i = 0; i < 10; i++) {
	if (sArr[i] != NULL)
	printf("%s\n", sArr[i]);
	}
	*/
	//"-" ���� ������
	char *ptr1 = strtok(sArr[0], "-");
	while (ptr1 != NULL)
	{
		date[d] = ptr1;
		d++;
		ptr1 = strtok(NULL, "-");
	}
	/*
	for (int i = 0; i < 10; i++) {
	if (date[i] != NULL)
	printf("%s\n", date[i]);
	}
	*/
	int year = atoi(date[0]);
	int month = atoi(date[1]);
	int day = atoi(date[2]);
	//printf("%s hellllllo \n", date[0]);
	//":" ���� ������
	char *ptr2 = strtok(sArr[1], ":");
	while (ptr2 != NULL) {
		time[d] = ptr2;
		d++;
		ptr2 = strtok(NULL, ":");
	}
	/*
	for (int i = 0; i < 10; i++) {
	if (time[i] != NULL)
	printf("%s\n", time[i]);
	}
	*/
	int hour = atoi(time[3]);
	int minute = atoi(time[4]);
	int second = atoi(time[5]);
	//
	GetTimeT(year, month, day, hour, minute, second);
	// DB ����ݱ�
	mysql_close(connection);
	return 0;

}