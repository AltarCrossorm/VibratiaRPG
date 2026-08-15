#pragma once
/**
 * @file ennemiespool.hpp
 * @date 2026/08/12
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */
#include "_base.hpp"
#include <tuple>

struct EnnemyPool final : public ORM_BASE
{
	long ennemy_id;
	long position;

	DECLARE_ORM_METADATA(EnnemyPool,id,ennemy_id,position)
};

class EnnemiesPoolRepository final : public Repository<EnnemyPool>
{
public:
	virtual std::string getTableName(void) override {
		return "ennemy_pool";
	}

	virtual EnnemyPool buildObject(std::vector<RowValue> val) override {
		BUILD_OBJECT_START(EnnemyPool,val)
		BUILD_OBJECT_ADD_FIELD(ennemy_id,long)
		BUILD_OBJECT_ADD_FIELD(position,long)
		BUILD_OBJECT_END
	}

	std::optional<EnnemyPool> getEnnemyFromPosition(long position) {
		std::string ennemiesQuery = R"(
		select
			ep.id, ep.ennemy_id, ep.position
		from
			ennemies_pool ep join ennemies e on e.id = ep.ennemy_id
		where
			ep.position = ?
		;)";

		auto pool = SQLite3::Connection::inst()->cursor().execute(ennemiesQuery,position)->fetchone();
		if(pool.empty())
			return std::nullopt;
		else
			return std::make_optional<EnnemyPool>(this->buildObject(pool));
	}
};
