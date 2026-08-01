#include <gtest/gtest.h>
#include "sqlite3.hpp"

class SQLite3Test : public ::testing::Test {
protected:
	inline static std::streambuf *ogBuf = nullptr;
	inline static SQLite3::Connection *con = nullptr;

	static void SetUpTestSuite() {
		// Arrange : Setup global de l'environnement de test
		ogBuf = std::cout.rdbuf();
		std::cout.rdbuf(nullptr);
		con = new SQLite3::Connection(":memory:");
	}

	static void TearDownTestSuite() {
		delete con;
		// Restore cout
		std::cout.rdbuf(ogBuf);
	}
};

TEST_F(SQLite3Test, InMemoryDatabase) {
	// Arrange
	auto cur = con->cursor();
	cur.execute("CREATE TABLE test_table (id INTEGER PRIMARY KEY, name TEXT);");
	cur.execute("INSERT INTO test_table (name) VALUES (?);", "Heimdall");
	cur.execute("INSERT INTO test_table (name) VALUES (?);", "Odin");

	// Act
	auto res = cur.execute("SELECT * FROM test_table ORDER BY id ASC;")->fetchall();
	
	// Assert
	EXPECT_EQ(res.size(), 2);
	
		// First row validation
	EXPECT_EQ(std::get<int>(res[0][0]), 1);
	EXPECT_EQ(std::get<std::string>(res[0][1]), "Heimdall");

		// Second row validation
	EXPECT_EQ(std::get<int>(res[1][0]), 2);
	EXPECT_EQ(std::get<std::string>(res[1][1]), "Odin");
}

TEST_F(SQLite3Test, FetchOneAndNullHandling) {
	// Arrange
	auto cur = con->cursor();
	cur.execute("CREATE TABLE null_table (id INTEGER, val TEXT);");
		// Note: we bind monostate or native NULL depending on SQLite3 wrapper capabilities
	cur.execute("INSERT INTO null_table (id, val) VALUES (?, ?);", 1, std::monostate{}); 
	cur.execute("INSERT INTO null_table (id, val) VALUES (2, NULL);");

	// Act
	auto res = cur.execute("SELECT * FROM null_table ORDER BY id ASC LIMIT 1;")->fetchone();
	
	// Assert
	EXPECT_EQ(res.size(), 2);
	EXPECT_EQ(std::get<int>(res[0]), 1);
	EXPECT_TRUE(std::holds_alternative<std::monostate>(res[1])); // Check if value is NULL
}

TEST_F(SQLite3Test, SQLtoJSONlistTest) {
	// Arrange
	auto cur = con->cursor();
	cur.execute("CREATE TABLE test_json (id INTEGER PRIMARY KEY, name TEXT);");
	cur.execute("INSERT INTO test_json (name) VALUES (?);", "Heimdall");

	// Act
	auto res = cur.execute("SELECT * FROM test_json;")->fetchall();
	auto cols = cur.getColumns();
	nlohmann::json jsonBody;
	jsonBody << SQLtoJSONlist{cols, res};

	// Assert
	EXPECT_TRUE(jsonBody.is_array());
	EXPECT_EQ(jsonBody.size(), 1);
	EXPECT_EQ(jsonBody[0]["id"], 1);
	EXPECT_EQ(jsonBody[0]["name"], "Heimdall");
}
