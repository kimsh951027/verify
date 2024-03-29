//db에 쿼리넣기
#include "db.h"

int db(int a, char *b, char *c, double d, char *e)
{
	MYSQL *connection = NULL, conn;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	int query_stat;
	int i;
	int m = 1;
	char query[255];

	//인자정의
	// DB 연결
	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);
	if (connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return 1;
	}

	sprintf(query, SQL_INSERT_RECORD, a, b, c, d, e);
	cout << query << endl;
	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		cout << "여기" << endl;
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	// DB 연결닫기
	mysql_close(connection);
	return 0;
}