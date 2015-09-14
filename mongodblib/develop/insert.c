#include <stdio.h>
#include <mongo.h>

int main() {
	mongo conn[1];
	bson b[1];
	bson_init(b);
	bson_append_new_oid(b, "_id");
	bson_append_string(b, "name", "joe");
	bson_append_int(b, "age", 33);
	bson_finish(b);
	int status = mongo_connect (conn, "127.0.0.1", 27017);
	
	
	if (status != MONGO_OK ){
			switch (conn->err){
				case MONGO_CONN_SUCCESS: printf("connection succeeded\n"); break;
				case MONGO_CONN_NO_SOCKET: printf("no socket\n"); return 1;
				case MONGO_CONN_FAIL: printf("connection failed\n"); return 1;
				case MONGO_CONN_NOT_MASTER: printf("not master\n"); return 1;
			}
		}

	mongo_insert(conn,"test.people",b);
	bson_destroy(b);

	mongo_destroy(conn);
	return 0;
}

