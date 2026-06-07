#include "dbMySQL.h"

char HOST[64] = "localhost";
char USER[64] = "root";
char PASS[64] = "123456";
int PORT_MYSQL = 3306;
char DB[64] = "banco_wyd1";

HANDLE hThread;

unsigned long iID;
int contador = 0;

char xQuery[1000];
char mQuery[1000];
char hQuery[1000];
char xMsg[1000];
char xRow[400];
char xMAC[400];
char xIP[400];
char *xPass;

MYSQL* cSQL::wStart()
{

	MYSQL* wSQL = mysql_init(NULL);

	try
	{
		my_bool reconnect = 1;
		mysql_options(wSQL, MYSQL_OPT_RECONNECT, &reconnect);
		mysql_options(wSQL, MYSQL_OPT_COMPRESS, 0);
		mysql_options(wSQL, MYSQL_OPT_CONNECT_TIMEOUT, "300");

		if (!mysql_real_connect(wSQL, HOST, USER, PASS, DB, PORT_MYSQL, NULL, 0))
		{
			printf("[wMySQL][TMSVR] Ocorreu um erro na conexão.\n\t\tErro: %s\n", mysql_error(wSQL));
			return wSQL;
		}

		return wSQL;
	}
	catch (...)
	{
		return wSQL;
	}
}

MYSQL_RES* cSQL::wRes(MYSQL* sql, char* query)
{

	try {
		if (mysql_query(sql, query))
		{
			printf("[dbMySQL][wRes] Erro na execução da wRes.\n\t\tErro: %s\n", mysql_error(sql));
			mysql_close(sql);
			return NULL;
		}

		MYSQL_RES* result = mysql_store_result(sql);

		mysql_close(sql);

		if (result)
			return result;

		return NULL;
	}
	catch (...)
	{
		return NULL;
	}
}



void cSQL::wLog(char* acc, char* pers, char* mensagem, char* type)
{

	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	sprintf(xQuery, "INSERT INTO `log` (`ID`, `Conta`, `Char`, `Mensagem`, `Data`, `Tipo`) VALUES(NULL, '%s', '%s', '%s', '%d/%d/%d %d:%d:%d', '%s')", acc, pers, mensagem, timeinfo->tm_mday, (timeinfo->tm_mon + 1), (timeinfo->tm_year + 1900), timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, type);
	////ThreadLog = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)wQuery, (void*)logQuery, 0, &lID);
	//cSQL::wQuery(xQuery);

	auto& pc = cSQL::instance();

	MYSQL* wSQL = pc.wStart();

	if (mysql_query(wSQL, xQuery))
	{
		printf("[dbMySQL][Log] Erro na execução da wQuery.\n\t\tErro: %s\n", mysql_error(wSQL));
		mysql_close(wSQL);
		//ExitThread(0);
		return;
	}

	mysql_close(wSQL);

	printf("[%02d/%02d/%d][%02d:%02d:%02d][%s - %s] %s\n", timeinfo->tm_mday, (timeinfo->tm_mon + 1), (timeinfo->tm_year + 1900), timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, acc, pers, mensagem);
	return;
}

/// Executes a query.
bool cSQL::wQuery(char* query)
{
	try
	{
		auto& pc = cSQL::instance();

		MYSQL* wSQL = pc.wStart();

		if (mysql_query(wSQL, query))
		{
			printf("[dbMySQL][wQuery] Erro na execução da wQuery.\n\t\tErro: %s\n", mysql_error(wSQL));
			mysql_close(wSQL);
			//ExitThread(0);
			return FALSE;
		}

		mysql_close(wSQL);
		//ExitThread(0);
		return TRUE;
	}
	catch (...)
	{
		return FALSE;
	}
}


int cSQL::Cont(char* query)
{
	int res = 0;
	auto& cnt = cSQL::instance();

	MYSQL* wSQL = cnt.wStart();
	MYSQL_RES* result = cnt.wRes(wSQL, query);

	if (result == NULL)
	{
		printf("[dbMySQL][wInfo]: Ocorreu um erro ao retornar Dados.\n");
		//mysql_free_result(sq.result);
		//mysql_close(sq.wSQL);
		return res;
	}


	res = (int)mysql_num_rows(result);

	mysql_free_result(result);
	mysql_close(wSQL);
	return res;
}

int cSQL::iInfo(char* query)
{
	int res = 0;
	MYSQL_ROW row;

	auto& cnt = cSQL::instance();

	MYSQL* wSQL = cnt.wStart();
	MYSQL_RES* result = cnt.wRes(wSQL, query);

	if (result == NULL)
	{
		printf("[dbMySQL][wInfo]: Ocorreu um erro ao retornar Dados.\n");
		//mysql_free_result(sq.result);
		//mysql_close(sq.wSQL);
		return res;
	}


	while ((row = mysql_fetch_row(result)) != NULL)
		res = atoi(row[0]);

	mysql_free_result(result);
	mysql_close(wSQL);
	return res;
}

char* cSQL::wInfo(char* query)
{
	static char res[1000];
	memset(res, 0, sizeof(res));

	MYSQL_ROW row;

	auto& cnt = cSQL::instance();

	MYSQL* wSQL = cnt.wStart();
	MYSQL_RES* result = cnt.wRes(wSQL, query);

	if (result == NULL)
	{
		printf("[dbMySQL][wInfo]: Ocorreu um erro ao retornar Dados.\n");
		return "0";
	}

	while ((row = mysql_fetch_row(result)) != NULL)
	{
		if (row[0])
			strncpy(res, row[0], sizeof(res) - 1);
	}

	mysql_free_result(result);
	mysql_close(wSQL);
	return res;
}

char* rcIP(unsigned int mIP)
{
	unsigned char* cIP = (unsigned char*)&mIP;
	sprintf(xIP, "%d.%d.%d.%d", cIP[0], cIP[1], cIP[2], cIP[3]);

	return xIP;
}

uint32_t convert(const char* name)
{
	uint32_t val = uint32_t(name[3])
		+ (uint32_t(name[2]) << 8)
		+ (uint32_t(name[1]) << 16)
		+ (uint32_t(name[0]) << 24);
	return val;
}

bool cSQL::ExecuteSafeQuery(const std::string& query, const std::vector<std::string>& params)
{
    auto& pc = cSQL::instance();
    MYSQL* wSQL = pc.wStart();
    if (!wSQL) return false;

    MYSQL_STMT* stmt = mysql_stmt_init(wSQL);
    if (!stmt) {
        mysql_close(wSQL);
        return false;
    }

    if (mysql_stmt_prepare(stmt, query.c_str(), (unsigned long)query.length())) {
        printf("[dbMySQL][SafeQuery] Prepare failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(wSQL);
        return false;
    }

    std::vector<MYSQL_BIND> binds(params.size());
    std::vector<unsigned long> lengths(params.size());
    for (size_t i = 0; i < params.size(); ++i) {
        binds[i].buffer_type = MYSQL_TYPE_STRING;
        binds[i].buffer = (void*)params[i].c_str();
        binds[i].buffer_length = (unsigned long)params[i].length();
        lengths[i] = (unsigned long)params[i].length();
        binds[i].length = &lengths[i];
        binds[i].is_null = 0;
    }

    if (params.size() > 0 && mysql_stmt_bind_param(stmt, binds.data())) {
        printf("[dbMySQL][SafeQuery] Bind failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(wSQL);
        return false;
    }

    if (mysql_stmt_execute(stmt)) {
        printf("[dbMySQL][SafeQuery] Execute failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(wSQL);
        return false;
    }

    mysql_stmt_close(stmt);
    mysql_close(wSQL);
    return true;
}

std::string cSQL::GetSafeInfo(const std::string& query, const std::vector<std::string>& params)
{
    auto& pc = cSQL::instance();
    MYSQL* wSQL = pc.wStart();
    if (!wSQL) return "0";

    MYSQL_STMT* stmt = mysql_stmt_init(wSQL);
    if (!stmt) {
        mysql_close(wSQL);
        return "0";
    }

    if (mysql_stmt_prepare(stmt, query.c_str(), (unsigned long)query.length())) {
        mysql_stmt_close(stmt);
        mysql_close(wSQL);
        return "0";
    }

    std::vector<MYSQL_BIND> binds(params.size());
    std::vector<unsigned long> lengths(params.size());
    for (size_t i = 0; i < params.size(); ++i) {
        binds[i].buffer_type = MYSQL_TYPE_STRING;
        binds[i].buffer = (void*)params[i].c_str();
        binds[i].buffer_length = (unsigned long)params[i].length();
        lengths[i] = (unsigned long)params[i].length();
        binds[i].length = &lengths[i];
    }

    if (params.size() > 0 && mysql_stmt_bind_param(stmt, binds.data())) {
        mysql_stmt_close(stmt);
        mysql_close(wSQL);
        return "0";
    }

    if (mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        mysql_close(wSQL);
        return "0";
    }

    char result_buf[1024] = {0};
    unsigned long result_len = 0;
    my_bool is_null = 0;
    
    MYSQL_BIND result_bind;
    memset(&result_bind, 0, sizeof(result_bind));
    result_bind.buffer_type = MYSQL_TYPE_STRING;
    result_bind.buffer = result_buf;
    result_bind.buffer_length = sizeof(result_buf);
    result_bind.length = &result_len;
    result_bind.is_null = &is_null;

    if (mysql_stmt_bind_result(stmt, &result_bind)) {
        mysql_stmt_close(stmt);
        mysql_close(wSQL);
        return "0";
    }

    std::string final_res = "0";
    if (mysql_stmt_fetch(stmt) == 0) {
        if (!is_null) final_res = std::string(result_buf, result_len);
    }

    mysql_stmt_close(stmt);
    mysql_close(wSQL);
    return final_res;
}

int cSQL::GetSafeInt(const std::string& query, const std::vector<std::string>& params)
{
    std::string res = GetSafeInfo(query, params);
    return atoi(res.c_str());
}

bool cSQL::AddAuctionItem(const char* seller, int itemIdx, int eff1, int val1, int eff2, int val2, int eff3, int val3, long long price)
{
    char query[512];
    sprintf(query, "INSERT INTO auction_items (seller_name, item_index, item_effect1, item_value1, item_effect2, item_value2, item_effect3, item_value3, price, expires_at) VALUES ('%s', %d, %d, %d, %d, %d, %d, %d, %lld, DATE_ADD(NOW(), INTERVAL 3 DAY))",
        seller, itemIdx, eff1, val1, eff2, val2, eff3, val3, price);
    return wQuery(query);
}

bool cSQL::RemoveAuctionItem(int auctionID)
{
    char query[256];
    sprintf(query, "UPDATE auction_items SET status = 1 WHERE id = %d", auctionID);
    return wQuery(query);
}

void cSQL::GetAuctionList(int page, void* outList)
{
    MSG_AuctionList* list = (MSG_AuctionList*)outList;
    list->TotalItems = 0;
    
    char query[256];
    sprintf(query, "SELECT id, seller_name, item_index, item_effect1, item_value1, item_effect2, item_value2, item_effect3, item_value3, price FROM auction_items WHERE status = 0 LIMIT %d, 10", page * 10);
    
    MYSQL* sql = wStart();
    if (sql) {
        MYSQL_RES* res = wRes(sql, query);
        if (res) {
            MYSQL_ROW row;
            int i = 0;
            while ((row = mysql_fetch_row(res)) && i < 10) {
                list->Items[i].AuctionID = atoi(row[0]);
                strncpy(list->Items[i].Seller, row[1], 16);
                list->Items[i].Item.sIndex = atoi(row[2]);
                list->Items[i].Item.stEffect[0].cEffect = atoi(row[3]);
                list->Items[i].Item.stEffect[0].cValue = atoi(row[4]);
                list->Items[i].Item.stEffect[1].cEffect = atoi(row[5]);
                list->Items[i].Item.stEffect[1].cValue = atoi(row[6]);
                list->Items[i].Item.stEffect[2].cEffect = atoi(row[7]);
                list->Items[i].Item.stEffect[2].cValue = atoi(row[8]);
                list->Items[i].Price = atoll(row[9]);
                i++;
            }
            list->TotalItems = i;
            mysql_free_result(res);
        }
        mysql_close(sql);
    }
}
